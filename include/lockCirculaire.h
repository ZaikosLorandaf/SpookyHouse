#ifndef LOCLCIRCULAIRE_H
#define LOCLCIRCULAIRE_H

#include "saveable.hpp"
#include <array>
#include <cstdint>

class lockCirculaire : public Savable {
private:
  bool active_object; // do not use. it is a flag for the move semantic
  bool locked;
  uint8_t combination[3];
  uint8_t current_input[3];
  std::string id;

  void update_lock_state();

  void save_lock() const;

  void retrieve_lock_save();

public:
  lockCirculaire(const uint8_t combinaison[3], std::string id);
  ~lockCirculaire();

  // No default constructor
  lockCirculaire() = delete;

  // Move semantics
  lockCirculaire(lockCirculaire &&);
  // Lock4Game &operator=(Lock4Game &&);

  // No copy
  lockCirculaire(const lockCirculaire &) = delete;
  lockCirculaire &operator=(const lockCirculaire &) = delete;

  bool is_locked() const;
  const uint8_t *get_current_input() const;
  void set_current_input(const uint8_t new_combinaison[3]);

  const char *get_type() const override;
  const char *get_id() const override;

  static std::array<uint8_t, 3> parse_lock_digits(const char *);
  static std::string serialize_lock_digits(const uint8_t *);
};

#endif // LOCLCIRCULAIRE_H
