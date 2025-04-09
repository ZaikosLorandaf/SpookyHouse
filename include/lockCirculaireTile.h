#ifndef LOCKCIRCULAIRETILE_H
#define LOCKCIRCULAIRETILE_H

#pragma once
#include "lockCirculaire.h"
#include "tile.hpp"

class TileLockCirculaire : public Tile {
private:
  lockCirculaire lock_game;

public:
  TileLockCirculaire(lockCirculaire &&);
  ~TileLockCirculaire() override = default;

  TileLockCirculaire(TileLockCirculaire &&) = default;

  lockCirculaire &get_lock();
};

#endif // LOCKCIRCULAIRETILE_H
