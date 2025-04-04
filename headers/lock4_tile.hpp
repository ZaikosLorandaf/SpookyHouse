#pragma once
#include "lock4.hpp"
#include "tile.hpp"

class TileLock4 : public Tile {
private:
  Lock4Game lock_game;

public:
  TileLock4(Lock4Game &&);
  ~TileLock4() override = default;

  TileLock4(TileLock4 &&) = default;

  Lock4Game &get_lock();
};
