#include "object_category.hpp"
#include <cstddef>

ReccordCategory::ReccordCategory(std::size_t capacity)
    : id_reccord_pairs(capacity) {}

SaveReccord *ReccordCategory::get_reccord_with_id(const char *id) {
  for (auto i = this->id_reccord_pairs.begin();
       i != this->id_reccord_pairs.end(); i++) {
    if (i->first == id)
      return &(i->second);
  }
  return nullptr;
}

void ReccordCategory::set_reccord(const char *id, SaveReccord sr) {
  for (auto i = this->id_reccord_pairs.begin();
       i != this->id_reccord_pairs.end(); i++) {
    if (i->first == id) {
      i->second = std::move(sr);
      return;
    }
  }
  this->id_reccord_pairs.emplace_back(std::string(id), std::move(sr));
}

std::pair<std::vector<std::pair<std::string, SaveReccord>>::const_iterator,
          std::vector<std::pair<std::string, SaveReccord>>::const_iterator>
ReccordCategory::get_iter() const {
  return std::pair(this->id_reccord_pairs.cbegin(),
                   this->id_reccord_pairs.cend());
}
