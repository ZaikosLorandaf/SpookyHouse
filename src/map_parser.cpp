#include "map.hpp"
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::pair<Vec2, std::vector<TileCoord>> Map::parse_file(const char *file_path) {
  assert(file_path != nullptr);
  std::ifstream file(file_path);
  std::string line;
  for (; !file.eof(); std::getline(file, line)) {
    if (line == "***")
      break;
  }
  line.clear();
  assert(!file.eof());
  std::getline(file, line);
  std::stringstream size_stream(line);
  Vec2 size(size_stream);
  // std::vector<TileCoord> tiles(size.x * size.y);
  std::vector<TileCoord> tiles;
  vec_comp x = 0, y = 0;
  for (line.clear(); !file.eof(); std::getline(file, line)) {
    x = 0;
    auto end = line.end();
    for (auto i = line.begin(); i != end; i++) {
      const char c = *i;
      if (c == ' ') {
      } else if (c == '#') {
        tiles.emplace_back(x, y, nullptr);
      } else {
      }
      x++;
    }
    y++;
  }

  return std::make_pair(std::move(size), std::move(tiles));
}
