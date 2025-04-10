#include "tile.hpp"
#include <string>

class TileHint : public Tile {
private:
  std::string hint;

public:
  TileHint(std::string);

  static std::string read_hint_from_file(const char *);
};
