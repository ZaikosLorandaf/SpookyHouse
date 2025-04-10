#include "saveable.hpp"
#include "tile.hpp"

class TileItem : public Tile, public Savable {
private:
  std::string id, item;
  bool taken;

  void save() const;

public:
  TileItem(std::string id, std::string item);
  TileItem(const TileItem &) = delete;
  TileItem(TileItem &&) = delete;
  TileItem &operator=(const TileItem &) = delete;
  TileItem &operator=(TileItem &&) = delete;

  virtual const char *get_type() const override;
  virtual const char *get_id() const override;
  const char *get_item_name() const;
  bool is_item_taken() const;
  bool take_item();

  ~TileItem();
};
