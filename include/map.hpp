#pragma once
#include "tile.hpp"
#include "tile_coord.hpp"
#include "vec2.hpp"
#include <functional>
#include <optional>
#include <vector>

class Map {
private:
  std::vector<TileCoord> map_tiles;
  Vec2 map_size;
  std::string file_origin;
  static std::pair<Vec2, std::vector<TileCoord>>
  parse_file(const char *file_path);

  Vec2 entrance;

  static TileEmpty empty_tile;
  static TileWall wall_tile;

public:
  Map(const char *file_path, std::optional<const char *> from = {});
  Map(const std::string &file_path);
  // Map(const Map &);
  Map(Map &&) = default;
  Map() = delete;
  ~Map() = default;

  std::optional<std::reference_wrapper<Tile>> get_tile(vec_comp x, vec_comp y);
  std::optional<std::reference_wrapper<Tile>> get_tile(Vec2 coord);

  Vec2 get_size();

  // Map &operator=(const Map &);
  Map &operator=(Map &&) = default;

  Vec2 get_entrance();

  const std::string &get_file_name() const;
};
