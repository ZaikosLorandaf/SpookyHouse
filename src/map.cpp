#include "map.hpp"
#include "tile.hpp"
#include "tile_coord.hpp"
#include "tile_map_entrance.hpp"
#include "vec2.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <optional>
#include <string>
#include <utility>
#include <vector>

Map::Map(const char *file_path, std::optional<const char *> from) {
  std::pair<Vec2, std::vector<TileCoord>> data_pair =
      Map::parse_file(file_path);
  std::sort(data_pair.second.begin(), data_pair.second.end());
  data_pair.second.shrink_to_fit();
  this->map_tiles = std::move(data_pair.second);
  this->map_size = std::move(data_pair.first);
  bool found = false;
  for (auto &el : this->map_tiles) {
    auto maybe_tile = el.get_tile();
    if (maybe_tile) {
      auto &tile = maybe_tile->get();
      TileMapEntrace *tile_ptr = dynamic_cast<TileMapEntrace *>(&tile);
      if (tile_ptr) {
        auto maybe_map_from = tile_ptr->from_map();
        if (maybe_map_from.has_value() && from.has_value()) {
          if (maybe_map_from->get() == *from) {
            this->entrance = el.get_coord();
            found = true;
            break;
          }
        } else if (!maybe_map_from.has_value() && !from.has_value()) {
          this->entrance = el.get_coord();
          found = true;
          break;
        }
      }
    }
  }
  assert(found);
}

Map::Map(const std::string &str) : Map(str.c_str()) {}

// Map::Map(const Map &other_map)
//     : map_tiles(other_map.map_tiles), map_size(other_map.map_size) {}

/*
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
*/

std::optional<std::reference_wrapper<Tile>> Map::get_tile(Vec2 coord) {
  if (coord.x >= this->map_size.x || coord.y >= this->map_size.y)
    return {};
  for (const auto &it : this->map_tiles) {
    if (it.get_coord() == coord) {
      auto maybe_tile = it.get_tile();
      if (maybe_tile) {
        return maybe_tile;
      }
      return std::ref(Map::wall_tile);
    }
  }
  return std::ref(Map::empty_tile);
}

std::optional<std::reference_wrapper<Tile>> Map::get_tile(vec_comp x,
                                                          vec_comp y) {
  Vec2 v(std::move(x), std::move(y));
  return this->get_tile(v);
}

Vec2 Map::get_size() { return this->map_size; }

Vec2 Map::get_entrance() { return this->entrance; }

TileEmpty Map::empty_tile;
TileWall Map::wall_tile;

const std::string &Map::get_file_name() const { return this->file_origin; }
