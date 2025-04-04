#pragma once
#include "../headers/tile_coord.hpp"
#include <functional>
#include <memory>
#include <optional>

TileCoord::TileCoord(Vec2 coord_in, Tile *tile_ptr)
    : tile(tile_ptr), coord(std::move(coord_in)) {}

TileCoord::TileCoord(vec_comp x, vec_comp y, Tile *tile_ptr)
    : tile(tile_ptr), coord(x, y) {}

std::optional<std::reference_wrapper<Tile>> TileCoord::get_tile() const {
  Tile *tile_ptr = this->tile.get();
  if (tile_ptr == nullptr)
    return std::optional<std::reference_wrapper<Tile>>();
  return std::make_optional(std::ref(*tile_ptr));
}

Vec2 TileCoord::get_coord() const { return this->coord; }

// returns:
// -1 if v1 < v2
// 0 if v1 == v2
// 1 if v1 > v2
static int compare(Vec2 v1, Vec2 v2) {
  if (v1.x > v2.x)
    return -1;
  if (v1.x < v2.x)
    return +1;
  if (v1.y > v2.y)
    return -1;
  if (v1.y < v2.y)
    return 1;
  return 0;
}

bool TileCoord::operator<(Vec2 v) const { return compare(this->coord, v) < 0; }
bool TileCoord::operator<=(Vec2 v) const {
  return compare(this->coord, v) <= 0;
}
bool TileCoord::operator==(Vec2 v) const {
  return compare(this->coord, v) == 0;
}
bool TileCoord::operator>=(Vec2 v) const {
  return compare(this->coord, v) >= 0;
}
bool TileCoord::operator>(Vec2 v) const { return compare(this->coord, v) > 0; }

bool TileCoord::operator<(const TileCoord &tc) const {
  return *this < tc.coord;
}
bool TileCoord::operator<=(const TileCoord &tc) const {
  return *this <= tc.coord;
}
bool TileCoord::operator==(const TileCoord &tc) const {
  return *this == tc.coord;
}
bool TileCoord::operator>(const TileCoord &tc) const {
  return *this > tc.coord;
}
bool TileCoord::operator>=(const TileCoord &tc) const {
  return *this >= tc.coord;
}

bool operator>(Vec2 v2, const TileCoord &tc) { return tc <= v2; }
bool operator>=(Vec2 v2, const TileCoord &tc) { return tc < v2; }
bool operator==(Vec2 v2, const TileCoord &tc) { return tc == v2; }
bool operator<=(Vec2 v2, const TileCoord &tc) { return tc > v2; }
bool operator<(Vec2 v2, const TileCoord &tc) { return tc >= v2; }

TileCoord::TileCoord(const TileCoord &tc)
    : tile(tc.tile->copy_ptr()), coord(tc.coord) {}

TileCoord::TileCoord(TileCoord &&tc)
    : tile(std::move(tc.tile)), coord(std::move(tc.coord)) {}
