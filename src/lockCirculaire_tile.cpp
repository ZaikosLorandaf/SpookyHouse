#include "lockCirculaireTile.h"
TileLockCirculaire::TileLockCirculaire(lockCirculaire &&init_lock) : lock_game(std::move(init_lock)) {}

lockCirculaire &TileLockCirculaire::get_lock() { return this->lock_game; }
