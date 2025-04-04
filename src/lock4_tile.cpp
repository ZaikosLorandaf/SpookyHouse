#include "../headers/lock4_tile.hpp"

TileLock4::TileLock4(Lock4Game &&init_lock) : lock_game(std::move(init_lock)) {}

Lock4Game &TileLock4::get_lock() { return this->lock_game; }
