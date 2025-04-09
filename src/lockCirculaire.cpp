#include <cstring>
#include "loclCirculaire.h"
#include <assert.h>

lockCirculaire::lockCirculaire(const uint8_t comb[3], std::string id){
    int size = 3;
    for (int i=0; i<size; i++){
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
    char buff[5] = {0};
    for (size_t i = 0; i < 3; i++)
        buff[i] = ((char)this->current_input[i]) + '0';
    sr.init_key_value("CURRENT_INPUT", buff);
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
    for (size_t i = 0; i < 3; i++)
        this->current_input[i] = (uint8_t)(input[i] - '0');
}
