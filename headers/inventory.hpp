#pragma once
#include <string>
#include <vector>

class Inventory {
  static std::vector<std::string> retrieve_key_vector();
  static void store_key_vector(std::vector<std::string> &&key_vec);
  constexpr static const char *const type = "INVENTORY";
  constexpr static const char *const key_id = "KEYS";
  Inventory() = delete;

public:
  static std::vector<std::string> get_player_key_list();
  static bool has_key(const char *key_name);
  static void pickup_key(const char *key_name);
  static void drop_key(const char *key_name);
  static void drop_all_key();
};
