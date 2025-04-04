#pragma once
#include "save_record.hpp"

class ReccordCategory {
private:
  std::vector<std::pair<std::string, SaveReccord>> id_reccord_pairs;

public:
  ReccordCategory() = default;
  ReccordCategory(std::size_t);

  ReccordCategory(ReccordCategory &&) = default;
  ReccordCategory &operator=(ReccordCategory &&) = default;

  SaveReccord *get_reccord_with_id(const char *id);
  void set_reccord(const char *id, SaveReccord reccord);

  std::pair<std::vector<std::pair<std::string, SaveReccord>>::const_iterator,
            std::vector<std::pair<std::string, SaveReccord>>::const_iterator>
  get_iter() const;
};
