#pragma once
#include "tile.hpp"
#include "tile_coord.hpp"
#include "vec2.hpp"
#include <memory>
#include <vector>

class Map {
private:
  std::vector<TileCoord> map_tiles;
  Vec2 map_size;
  static std::pair<Vec2, std::vector<TileCoord>>
  parse_file(const char *file_path);

  static const std::unique_ptr<TileEmpty> empty_tile;
  static const std::unique_ptr<TileWall> wall_tile;

public:
  Map(const char *file_path);
  Map(const std::string &file_path);
  Map(const Map &);
  Map(Map &&);
  Map() = delete;
  ~Map() = default;

  Tile *get_tile(vec_comp x, vec_comp y) const;
  Tile *get_tile(Vec2 coord) const;

  Map &operator=(const Map &);
  Map &operator=(Map &&);
};
