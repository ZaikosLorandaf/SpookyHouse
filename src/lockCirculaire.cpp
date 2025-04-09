#include "loclCirculaire.h"
#include <array>
#include <assert.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <sstream>
#include <sys/types.h>

lockCirculaire::lockCirculaire(const uint8_t comb[3], std::string id) {
  int size = 3;
  for (int i = 0; i < size; i++) {
    this->combination[i] = comb[i];
  }
}

void lockCirculaire::update_lock_state() {
  for (size_t i = 0; i < 3; i++) {
    if (this->current_input[i] != this->combination[i]) {
      this->locked = true;
      return;
    }
  }
  this->locked = false;
}

bool lockCirculaire::is_locked() const { return this->locked; }

void lockCirculaire::set_current_input(const uint8_t new_input[3]) {
  std::memcpy(this->current_input, new_input, 3 * sizeof(uint8_t));
  this->update_lock_state();
}

lockCirculaire::~lockCirculaire() {
  if (this->active_object)
    this->save_lock();
}

lockCirculaire::lockCirculaire(lockCirculaire &&rval)
    : active_object(true), locked(rval.locked) {
  rval.active_object = false;
  std::memcpy(this->combination, rval.combination, 3 * sizeof(uint8_t));
  std::memcpy(this->current_input, rval.current_input, 3 * sizeof(uint8_t));
}

const char *lockCirculaire::get_id() const { return this->id.c_str(); }

const char *lockCirculaire::get_type() const { return "LOCKCIRCULAIRE"; }

void lockCirculaire::save_lock() const {
  SaveReccord sr(1);
  std::string lock_encoded =
      lockCirculaire::serialize_lock_digits(this->current_input);
  sr.init_key_value("CURRENT_INPUT", std::move(lock_encoded));
  this->save_record(std::move(sr));
}

void lockCirculaire::retrieve_lock_save() {
  auto maybe_reccord = this->get_save_reccord();
  if (!maybe_reccord.has_value())
    return;
  const SaveReccord &record = maybe_reccord.value();
  auto maybe_input = record.retrieve_value("CURRENT_INPUT");
  assert(maybe_input.has_value());
  const char *input = maybe_input.value();
  assert(input != nullptr);
  auto input_parsed = lockCirculaire::parse_lock_digits(input);
  for (size_t i = 0; i < 3; i++)
    this->current_input[i] = input_parsed[i];
}

std::array<uint8_t, 3> lockCirculaire::parse_lock_digits(const char *str) {
  assert(str != nullptr);
  uint8_t buff[2];
  size_t buff_index = 0;
  size_t result_count = 0;
  std::array<uint8_t, 3> result;
  for (size_t i = 0; str[i] != '\0'; i++) {
    if (str[i] == ';') {
      assert(buff_index > 0);
      uint8_t factor = 1;
      uint8_t new_digit = 0;
      for (int j = buff_index - 1; j >= 0; j--) {
        new_digit += factor * buff[j];
        factor *= 10;
      }
      result[result_count] = new_digit;
      result_count++;
      buff_index = 0;
    } else {
      assert(result_count < 3);
      assert(buff_index < 2);
      buff[buff_index] = (uint8_t)(str[i] - 0);
      buff_index++;
    }
  }
  if (buff_index > 0) {
    uint8_t factor = 1;
    uint8_t new_digit = 0;
    for (int j = buff_index - 1; j >= 0; j--) {
      new_digit += factor * buff[j];
      factor *= 10;
    }
    result[result_count] = new_digit;
    result_count++;
  }
  assert(result_count == 3);

  return std::move(result);
}

std::string lockCirculaire::serialize_lock_digits(const uint8_t *combination) {
  assert(combination != nullptr);
  std::string result;
  std::stringstream ss;
  ss << combination[0] << ';' << combination[1] << ';' << combination[2];
  assert(!result.empty());
  return std::move(result);
}
