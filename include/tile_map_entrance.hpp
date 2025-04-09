#include "map.hpp"
#include "tile.hpp"

class TileMapEntrace : public Tile {
private:
  OPTIONAL_STRING from, to;

public:
  TileMapEntrace(OPTIONAL_STRING from_map_path = OPTIONAL_STRING(),
                 OPTIONAL_STRING to_map_path = OPTIONAL_STRING());
  ~TileMapEntrace() = default;

  TileMapEntrace(const TileMapEntrace &) = default;
  TileMapEntrace(TileMapEntrace &&) = default;

  OPTIONAL_STRING_REF from_map() const;
  OPTIONAL_STRING_REF to_map() const;
  // TileMapEntrace *copy_ptr() const override;

  std::optional<Map> move_to_new_map(const Map &current_map) const;

  TileMapEntrace &operator=(const TileMapEntrace &) = default;
  TileMapEntrace &operator=(TileMapEntrace &&) = default;
};

#undef OPTIONAL_STRING
#undef OPTIONAL_STRING_REF
