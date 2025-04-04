#include "save_manager.hpp"
#include <fstream>
#include <functional>
#include <optional>

std::optional<std::reference_wrapper<const SaveReccord>>
SaveManager::get_reccord(const char *category_name, const char *id) {
  ReccordCategory *category =
      SaveManager::save_data.get_category(category_name);
  if (category == nullptr)
    return std::optional<std::reference_wrapper<const SaveReccord>>();
  SaveReccord *rc_ptr = category->get_reccord_with_id(id);
  if (rc_ptr == nullptr) {
    return std::optional<std::reference_wrapper<const SaveReccord>>();
  }
  return std::make_optional<std::reference_wrapper<const SaveReccord>>(
      std::cref(*rc_ptr));
}

void SaveManager::set_reccord(const char *category_name, const char *id,
                              SaveReccord save_reccord) {
  ReccordCategory *category =
      SaveManager::save_data.get_category(category_name);
  if (category == nullptr) {
    ReccordCategory new_category(1);
    new_category.set_reccord(id, std::move(save_reccord));
    SaveManager::save_data.set_category(category_name, std::move(new_category));
    return;
  }
  category->set_reccord(id, std::move(save_reccord));
}

bool SaveManager::save_to_file(const char *file_path) {
  std::ofstream file(file_path);
  file << SaveManager::save_data;
  return true;
}

bool SaveManager::load_from_file(const char *file_path) {
  std::ifstream file(file_path);
  std::string category, id, entry, value;
  while (!file.eof()) {
    file >> category >> id;
    SaveReccord new_reccord;
    while (true) {
      entry.clear();
      value.clear();
      file >> entry;
      if (entry == "END")
        break;
      file >> value;
      new_reccord.init_key_value(std::move(entry), std::move(value));
    }
    ReccordCategory *rc = SaveManager::save_data.get_category(category.c_str());
    if (rc == nullptr) {
      ReccordCategory new_rc(1);
      new_rc.set_reccord(id.c_str(), std::move(new_reccord));
      SaveManager::save_data.set_category(category.c_str(), std::move(new_rc));
    } else {
      rc->set_reccord(id.c_str(), std::move(new_reccord));
    }
  }
  return true;
}
