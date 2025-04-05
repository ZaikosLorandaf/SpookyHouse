#include "category_collection.hpp"
#include <cassert>
#include <ostream>

CategoryCollection::CategoryCollection(std::size_t capacity)
    : category_name_to_content(capacity) {}

ReccordCategory *CategoryCollection::get_category(const char *ct) {
  assert(ct != nullptr);
  for (auto i = this->category_name_to_content.begin();
       i != this->category_name_to_content.end(); i++) {
    if (i->first == ct)
      return &(i->second);
  }
  return nullptr;
}

void CategoryCollection::set_category(const char *ct, ReccordCategory cv) {
  assert(ct != nullptr);
  for (auto i = this->category_name_to_content.begin();
       i != this->category_name_to_content.end(); i++) {
    if (i->first == ct) {
      i->second = std::move(cv);
      return;
    }
  }

  this->category_name_to_content.emplace_back(std::string(ct), std::move(cv));
}

std::ostream &operator<<(std::ostream &stream, const CategoryCollection &cc) {
  auto category = cc.category_name_to_content.cbegin();
  auto category_end = cc.category_name_to_content.cend();
  for (; category != category_end; category++) {
    auto reccord_iter = category->second.get_iter();
    for (auto record = reccord_iter.first; record != reccord_iter.second;
         record++) {
      stream << category->first      // category name
             << ' ' << record->first // record id
             << '\n'
             << record->second // content of the reccord
             << "END\n";
    }
  }
  return stream;
}
