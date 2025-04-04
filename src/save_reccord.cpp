#include "save_record.hpp"
#include <cstddef>
#include <optional>
#include <sstream>
#include <string>

SaveReccord::SaveReccord(std::size_t capacity) : key_val_vector(capacity) {}

std::optional<const char *> SaveReccord::retrieve_value(const char *key) const {
  for (auto i = this->key_val_vector.begin(); i != this->key_val_vector.end();
       i++) {
    if (key == i->first)
      return std::make_optional(i->second.c_str());
  }
  return std::optional<const char *>();
}

std::string SaveReccord::set_key_value(const char *key, const char *val) {
  for (auto i = this->key_val_vector.begin(); i != this->key_val_vector.end();
       i++) {
    if (key == i->first) {
      std::string old(std::move(i->second));
      i->second = std::string(val);
      return old;
    }
  }
  this->key_val_vector.emplace_back(std::string(key), std::string(val));
  return std::string();
}

std::string SaveReccord::to_string() const {
  std::stringstream ss;
  ss << *this;
  return ss.str();
}

SaveReccord::operator std::string() const { return this->to_string(); }

std::ostream &operator<<(std::ostream &stream, const SaveReccord &sr) {
  for (auto i = sr.key_val_vector.begin(); i != sr.key_val_vector.end(); i++) {
    stream << i->first << ' ' << i->second << '\n';
  }
  return stream;
}

void SaveReccord::init_key_value(std::string key, std::string value) {
  this->key_val_vector.emplace_back(std::move(key), std::move(value));
}
