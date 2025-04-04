#pragma once
#include "category_collection.hpp"
#include <functional>
#include <optional>

class SaveManager {
private:
  static CategoryCollection save_data;

public:
  SaveManager() = delete;

  static bool load_from_file(const char *file_path);
  static bool save_to_file(const char *file_path);

  static std::optional<std::reference_wrapper<const SaveReccord>>
  get_reccord(const char *category, const char *id);
  static void set_reccord(const char *category, const char *id,
                          SaveReccord save_reccord);
};
