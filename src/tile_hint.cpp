#include "tile_hint.hpp"
#include <cassert>
#include <fstream>
#include <string>

std::string TileHint::read_hint_from_file(const char *path) {
  std::ifstream file(path);
  assert(!file.fail());
  std::string line, result;
  while (!file.eof()) {
    std::getline(file, line);
    result += line;
    result += '\n';
  }
  return result;
}

TileHint::TileHint(std::string hint_arg) : hint(std::move(hint_arg)) {}
