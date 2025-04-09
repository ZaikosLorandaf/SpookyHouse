#include "lock4.hpp"
#include "lock4_tile.hpp"
#include "lockCirculaire.h"
#include "lockCirculaireTile.h"
#include "map.hpp"
#include "tile.hpp"
#include "tile_map_entrance.hpp"
#include <cassert>
#include <fstream>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::pair<Vec2, std::vector<TileCoord>> Map::parse_file(const char *file_path) {
  assert(file_path != nullptr);
  std::ifstream file(file_path);
  assert(!file.fail());
  std::string line;
  std::string token;
  std::vector<std::pair<char, std::unique_ptr<Tile>>> v;
  for (; !file.eof(); std::getline(file, line)) {
    if (line == "***")
      break;
    std::stringstream ss(line);
    ss >> token;
    if (token.empty())
      continue;
    if (token == "LOCK4") {
      std::string symbol;
      std::string id;
      std::string combination;
      ss >> symbol >> id >> combination;
      const char symbol_char = symbol.c_str()[0];
      uint8_t combination_parsed[4] = {0};
      size_t i = 0;
      for (const char c : combination) {
        if (i >= 4)
          break;
        combination_parsed[i] = (uint8_t)(c) - '0';
      }
      Lock4Game game(combination_parsed, id.c_str());
      auto ptr = std::make_unique<TileLock4>(std::move(game));
      v.emplace_back(std::make_pair(symbol_char, std::move(ptr)));
    } else if (token == "MAP") {
      std::string symbol;
      std::string from_path;
      std::string to_path;
      ss >> symbol >> from_path >> to_path;
      const char symbol_char = symbol.c_str()[0];
      std::optional<std::string> to, from;
      if (from_path == "NULL")
        from = {};
      else
        from = std::move(from_path);
      if (to_path == "NULL")
        to = {};
      else
        to = std::move(to_path);
      auto ptr =
          std::make_unique<TileMapEntrace>(std::move(from), std::move(to));
      v.emplace_back(symbol_char, std::move(ptr));
    } else if (token == "LOCKTOUR") {
      std::string symbol, id, combination;
      ss >> symbol >> id >> combination;
      const char symbol_char = symbol.c_str()[0];
      auto parsed_combination =
          lockCirculaire::parse_lock_digits(combination.c_str());
      lockCirculaire lc(parsed_combination.data(), std::move(id));
      auto ptr = std::make_unique<TileLockCirculaire>(std::move(lc));
      v.emplace_back(std::make_pair(symbol_char, std::move(ptr)));
    } else {
      assert(false);
    }
    token.clear();
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
#ifndef NDEBUG
        bool found = false;
#endif
        for (auto &el : v) {
          if (el.first == c) {
            assert(el.second.get() != nullptr);
            tiles.emplace_back(x, y, std::move(el.second));
#ifndef NDEBUG
            found = true;
#endif
            break;
          }
        }
        assert(found);
      }
      x++;
    }
    y++;
  }

  return std::make_pair(std::move(size), std::move(tiles));
}
