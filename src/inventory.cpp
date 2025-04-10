#include "inventory.hpp"
#include "save_manager.hpp"
#include <cstddef>
#include <cstring>
#include <string>
#include <vector>

std::vector<std::string> Inventory::retrieve_key_vector() {
  auto sro = SaveManager::get_reccord(Inventory::type, Inventory::key_id);
  if (!sro)
    return std::vector<std::string>();
  const SaveReccord &sr = sro.value();
  auto maybe_key_list = sr.retrieve_value("KEY_LIST");
  if (!maybe_key_list)
    return std::vector<std::string>();
  const char *const key_list = maybe_key_list.value();
  std::string buff;
  std::vector<std::string> result;
  for (size_t i = 0; key_list[i] != '\0'; i++) {
    if (key_list[i] == ';') {
      if (!buff.empty()) {
        // copied, not moved, to avoid reallocating for the buffer with each
        // char added
        result.emplace_back(buff);
        buff.clear();
      }
    } else {
      buff += key_list[i];
    }
  }
  return std::move(result);
}

void Inventory::store_key_vector(std::vector<std::string> &&key_vec) {
  std::string buff;
  for (auto e = key_vec.cbegin(); e != key_vec.cend(); e++) {
    buff += *e;
    buff += ';';
  }
  SaveReccord sr(1);
  sr.init_key_value(std::string("KEY_LIST"), std::move(buff));
  SaveManager::set_reccord(Inventory::type, Inventory::key_id, std::move(sr));
}

void Inventory::pickup_key(const char *key_name) {
  auto kv = retrieve_key_vector();
  for (const auto &key : kv) {
    if (key == key_name)
      return;
  }
  kv.emplace_back(key_name);
  store_key_vector(std::move(kv));
}

bool Inventory::has_key(const char *key_name) {
  auto kv = retrieve_key_vector();
  for (const auto &key : kv) {
    if (key == key_name)
      return true;
  }
  return false;
}

void Inventory::drop_key(const char *key_name) {
  auto kv = retrieve_key_vector();
  std::size_t index = 0;
  bool found;
  for (auto it = kv.cbegin(); it != kv.cend(); it++) {
    if (*it == key_name) {
      kv.erase(it);
      store_key_vector(std::move(kv));
      return;
    }
  }
}

void Inventory::drop_all_key() {
  std::vector<std::string> empty_vec;
  store_key_vector(std::move(empty_vec));
}
