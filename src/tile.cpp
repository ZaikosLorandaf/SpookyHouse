#include "tile.hpp"
#include "tile_map_entrance.hpp"
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
    return {};
  const std::string &ref = this->from.value();
  return std::cref(ref);
}

OPTIONAL_STRING_REF TileMapEntrace::to_map() const {
  if (!this->to.has_value())
    return {};
  const std::string &ref = this->to.value();
  return std::cref(ref);
}

std::optional<Map>
TileMapEntrace::move_to_new_map(const Map &current_map) const {
  if (!this->to.has_value())
    return {};
  auto &new_map_path = this->to.value();
  auto &old_map_path = current_map.get_file_name();
  return Map(new_map_path.c_str(), old_map_path.c_str());
}
