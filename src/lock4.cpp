#include "lock4.hpp"
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <optional>

void Lock4Game::update_lock_state() {
  for (size_t i = 0; i < 4; i++) {
    if (this->current_input[i] != this->combination[i]) {
      this->locked = true;
      return;
    }
  }
  this->locked = false;
}

bool Lock4Game::is_locked() const { return this->locked; }

void Lock4Game::set_current_input(const uint8_t new_input[4]) {
  std::memcpy(this->current_input, new_input, 4 * sizeof(uint8_t));
  this->update_lock_state();
}

Lock4Game::Lock4Game(Lock4Game &&rval)
    : active_object(true), locked(rval.locked) {
  rval.active_object = false;
  std::memcpy(this->combination, rval.combination, 4 * sizeof(uint8_t));
  std::memcpy(this->current_input, rval.current_input, 4 * sizeof(uint8_t));
}

Lock4Game::~Lock4Game() {
  if (this->active_object)
    this->save_lock();
}

const char *Lock4Game::get_id() const { return this->id.c_str(); }

const char *Lock4Game::get_type() const { return "LOCK4GAME"; }

void Lock4Game::save_lock() const {
  SaveReccord sr(1);
  char buff[5] = {0};
  for (size_t i = 0; i < 4; i++)
    buff[i] = ((char)this->current_input[i]) + '0';
  sr.init_key_value("CURRENT_INPUT", buff);
  this->save_record(std::move(sr));
}

void Lock4Game::retrieve_lock_save() {
  auto maybe_reccord = this->get_save_reccord();
  if (!maybe_reccord.has_value())
    return;
  const SaveReccord &record = maybe_reccord.value();
  auto maybe_input = record.retrieve_value("CURRENT_INPUT");
  assert(maybe_input.has_value());
  const char *input = maybe_input.value();
  assert(input != nullptr);
  for (size_t i = 0; i < 4; i++)
    this->current_input[i] = (uint8_t)(input[i] - '0');
}

Lock4Game::Lock4Game(const uint8_t *init_combi, std::string init_id,
                     std::optional<const uint8_t *> init_input)
    : id(init_id), active_object(true) {
  std::memcpy(this->combination, init_combi, 4 * sizeof(uint8_t));
  if (init_input.has_value()) {
    const uint8_t *const init_input_defined = init_input.value();
    assert(init_input != nullptr);
    std::memcpy(this->current_input, init_input_defined, 4 * sizeof(uint8_t));
  } else {
    for (size_t i = 0; i < 4; i++) {
      this->current_input[i] = 0;
    }
  }
  this->retrieve_lock_save();
  this->update_lock_state();
}
