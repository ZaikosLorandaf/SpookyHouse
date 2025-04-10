#include "tile_item.hpp"
#include "inventory.hpp"
#include "save_record.hpp"
#include <cstring>
#include <optional>

TileItem::TileItem(std::string id, std::string item_name)
    : id(std::move(id)), item(std::move(item_name)) {
  auto sr_maybe = this->get_save_reccord();
  if (!sr_maybe) {
    this->taken = false;
    return;
  }
  auto &sr = sr_maybe->get();
  auto maybe_value = sr.retrieve_value("TAKEN");
  if (!maybe_value || !std::strcmp(*maybe_value, "TRUE")) {
    this->taken = false;
    return;
  }
  this->taken = true;
}

const char *TileItem::get_id() const { return this->id.c_str(); }
const char *TileItem::get_type() const { return "ITEMTILE"; }

void TileItem::save() const {
  SaveReccord sr(1);
  sr.init_key_value("TAKEN", this->taken ? "TRUE" : "FALSE");
}

TileItem::~TileItem() { this->save(); }

const char *TileItem::get_item_name() const { return this->item.c_str(); }

bool TileItem::is_item_taken() const { return this->taken; }

bool TileItem::take_item() {
  if (this->taken)
    return false;
  this->taken = true;
  Inventory::pickup_key(this->item.c_str());
  return true;
}
