#include "map.hpp"
#include "tile.hpp"
#include "tile_coord.hpp"
#include <algorithm>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>

Map::Map(const char *file_path) {
  std::pair<Vec2, std::vector<TileCoord>> data_pair =
      Map::parse_file(file_path);
  std::sort(data_pair.second.begin(), data_pair.second.end());
  data_pair.second.shrink_to_fit();
  this->map_tiles = std::move(data_pair.second);
  this->map_size = std::move(data_pair.first);
}

Map::Map(const std::string &str) : Map(str.c_str()) {}

// Map::Map(const Map &other_map)
//     : map_tiles(other_map.map_tiles), map_size(other_map.map_size) {}

Map::Map(Map &&rval)
    : map_tiles(std::move(rval.map_tiles)), map_size(std::move(rval.map_size)) {
}

// Map &Map::operator=(const Map &rhs) {
//   this->map_tiles = rhs.map_tiles;
//   this->map_size = rhs.map_size;
//   return *this;
// }

Map &Map::operator=(Map &&rval) {
  this->map_tiles = std::move(rval.map_tiles);
  this->map_size = std::move(rval.map_size);
  return *this;
}

std::optional<std::reference_wrapper<Tile>> Map::get_tile(Vec2 coord) const {
  if (coord.x >= this->map_size.x || coord.y >= this->map_size.y)
    return {};
  auto iter_pair =
      std::equal_range(this->map_tiles.cbegin(), this->map_tiles.cend(), coord);
  if (iter_pair.first == iter_pair.second)
    return std::ref(Map::empty_tile);

  auto maybe_tile = iter_pair.first->get_tile();
  if (maybe_tile)
    return maybe_tile;
  return std::ref(Map::wall_tile);
}

std::optional<std::reference_wrapper<Tile>> Map::get_tile(vec_comp x,
                                                          vec_comp y) const {
  Vec2 v(std::move(x), std::move(y));
  return this->get_tile(v);
}

TileEmpty Map::empty_tile;
TileWall Map::wall_tile;
