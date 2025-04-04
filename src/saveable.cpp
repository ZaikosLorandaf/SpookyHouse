#include "saveable.hpp"
#include "save_manager.hpp"
#include <functional>
#include <optional>

void Savable::save_record(SaveReccord sr) const {
  const char *const type = this->get_type();
  const char *const id = this->get_id();
  SaveManager::set_reccord(type, id, std::move(sr));
}

std::optional<std::reference_wrapper<const SaveReccord>>
Savable::get_save_reccord() const {
  const char *const type = this->get_type();
  const char *const id = this->get_id();
  return SaveManager::get_reccord(type, id);
}
