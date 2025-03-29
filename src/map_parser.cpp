#include "../headers/map.hpp"
#include <fstream>
#include <ios>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::pair<Vec2, std::vector<TileCoord>> Map::parse_file(const char *file_path) {
  std::ifstream file(file_path);
  std::string line;
  for (; !file.eof(); std::getline(file, line)) {
    if (line == "***")
      break;
  }
  line.clear();
  if (file.eof())
    throw std::ios_base::failure("wrong format");
  std::getline(file, line);
  std::stringstream size_stream(line);
  Vec2 size(size_stream);
  std::vector<TileCoord> tiles(size.x * size.y);
  vec_comp x = 0, y = 0;
  for (line.clear(); !file.eof(); std::getline(file, line)) {
    x = 0;
    auto end = line.end();
    for (auto i = line.begin(); i != end; i++) {
      const char c = *i;
      if (c == ' ') {
      } else if (c == '#') {
        Tile *tile = new TileWall();
        tiles.emplace_back(x, y, tile);
      } else {
      }
      x++;
    }
    y++;
  }

  return std::make_pair(size, tiles);
}
