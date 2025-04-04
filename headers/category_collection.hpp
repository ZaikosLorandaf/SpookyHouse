#include "object_category.hpp"
#include <cstddef>
#include <ostream>

class CategoryCollection {
private:
  std::vector<std::pair<std::string, ReccordCategory>> category_name_to_content;

public:
  CategoryCollection() = default;
  CategoryCollection(std::size_t);

  CategoryCollection(CategoryCollection &&) = default;
  CategoryCollection &operator=(CategoryCollection &&) = default;

  ReccordCategory *get_category(const char *category_type);
  void set_category(const char *category_type, ReccordCategory category_value);

  friend std::ostream &operator<<(std::ostream &, const CategoryCollection &);
};

std::ostream &operator<<(std::ostream &, const CategoryCollection &);
