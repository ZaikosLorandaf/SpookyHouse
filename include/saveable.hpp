#pragma once
#include "save_record.hpp"
#include <functional>
#include <optional>

class Savable {
public:
  virtual const char *get_type() const = 0;
  virtual const char *get_id() const = 0;
  virtual void save_record(SaveReccord) const;
  virtual std::optional<std::reference_wrapper<const SaveReccord>>
  get_save_reccord() const;
};
