#include "tile.hpp"
#include <optional>

TileEmpty::TileEmpty(const TileEmpty &) {}

TileWall::TileWall(const TileWall &) {}

#define OPTIONAL_STRING std::optional<std::string>
#define OPTIONAL_STRING_REF                                                    \
  std::optional<std::reference_wrapper<const std::string>>

TileMapEntrace::TileMapEntrace(OPTIONAL_STRING from_map, OPTIONAL_STRING to_map)
    : from(from_map), to(to_map) {}

OPTIONAL_STRING_REF TileMapEntrace::from_map() const {
  if (!this->from.has_value())
    return OPTIONAL_STRING_REF();
  const std::string &ref = this->from.value();
  return std::make_optional(std::ref(ref));
}

OPTIONAL_STRING_REF TileMapEntrace::to_map() const {
  if (!this->to.has_value())
    return OPTIONAL_STRING_REF();
  const std::string &ref = this->to.value();
  return std::make_optional(std::ref(ref));
}
