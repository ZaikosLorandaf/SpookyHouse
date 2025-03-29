#include "../headers/tile.hpp"

TileEmpty::TileEmpty(const TileEmpty &) {}

TileWall::TileWall(const TileWall &) {}

TileEmpty *TileEmpty::copy_ptr() const { return new TileEmpty(*this); }

TileWall *TileWall::copy_ptr() const { return new TileWall(*this); }
