#pragma once
#include "tile.hpp"
#include "vec2.hpp"
#include <memory>

class TileCoord {
private:
  std::unique_ptr<Tile> tile;
  Vec2 coord;

public:
  TileCoord() = delete;   // no default constructor
  ~TileCoord() = default; // default destructor is fine
  TileCoord(Vec2 coord, Tile *tile);
  TileCoord(vec_comp x, vec_comp y, Tile *tile);

  TileCoord(const TileCoord &);
  TileCoord(TileCoord &&);

  Tile *get_tile() const;
  Vec2 get_coord() const;

  // for sorting
  bool operator>(Vec2) const;
  bool operator>=(Vec2) const;
  bool operator==(Vec2) const;
  bool operator<=(Vec2) const;
  bool operator<(Vec2) const;

  bool operator>(const TileCoord &) const;
  bool operator>=(const TileCoord &) const;
  bool operator==(const TileCoord &) const;
  bool operator<=(const TileCoord &) const;
  bool operator<(const TileCoord &) const;

  TileCoord &operator=(const TileCoord &);
  TileCoord &operator=(TileCoord &&);
};

bool operator>(Vec2, const TileCoord &);
bool operator>=(Vec2, const TileCoord &);
bool operator==(Vec2, const TileCoord &);
bool operator<=(Vec2, const TileCoord &);
bool operator<(Vec2, const TileCoord &);
