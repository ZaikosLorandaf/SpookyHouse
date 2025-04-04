#include "../headers/savable.h"
#include <cstdint>
#include <optional>

class Lock4Game : public Savable {
private:
  bool active_object; // do not use. it is a flag for the move semantic
  bool locked;
  uint8_t combination[4];
  uint8_t current_input[4];
  std::string id;

  const static uint8_t default_input[4];

  void update_lock_state();

  void save_lock() const;

  void retrieve_lock_save();

public:
  Lock4Game(
      const uint8_t *combinaison, std::string id,
      std::optional<const uint8_t *> input = std::optional<const uint8_t *>());
  ~Lock4Game();

  // No default constructor
  Lock4Game() = delete;

  // Move semantics
  Lock4Game(Lock4Game &&);
  // Lock4Game &operator=(Lock4Game &&);

  // No copy
  Lock4Game(const Lock4Game &) = delete;
  Lock4Game &operator=(const Lock4Game &) = delete;

  bool is_locked() const;
  const uint8_t *get_current_input() const;
  void set_current_input(const uint8_t new_combinaison[4]);

  const char *get_type() const override;
  const char *get_id() const override;
};
