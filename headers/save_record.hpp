#pragma once
#include <optional>
#include <ostream>
#include <string>
#include <vector>

class SaveReccord {
private:
  std::vector<std::pair<std::string, std::string>> key_val_vector;

public:
  SaveReccord() = default;
  SaveReccord(std::size_t capacity);
  SaveReccord(const SaveReccord &) = default;
  SaveReccord(SaveReccord &&) = default;

  std::string set_key_value(const char *, const char *);
  void init_key_value(std::string, std::string);
  std::optional<const char *> retrieve_value(const char *key) const;

  std::string to_string() const;

  explicit operator std::string() const;

  SaveReccord &operator=(const SaveReccord &) = default;
  SaveReccord &operator=(SaveReccord &&) = default;

  friend std::ostream &operator<<(std::ostream &, const SaveReccord &);
};

std::ostream &operator<<(std::ostream &, const SaveReccord &);
