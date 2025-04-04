#pragma once
#include <optional>
#include <string>

class Tile {
public:
  virtual ~Tile() = 0;
  // virtual Tile *copy_ptr() const = 0;
};

class TileWall : public Tile {
public:
  TileWall() = default;
  ~TileWall() = default;
  TileWall(const TileWall &);
  // TileWall *copy_ptr() const override;
};

class TileEmpty : public Tile {
public:
  TileEmpty() = default;
  ~TileEmpty() = default;
  TileEmpty(const TileEmpty &);
  // TileEmpty *copy_ptr() const override;
};

#define OPTIONAL_STRING std::optional<std::string>
#define OPTIONAL_STRING_REF                                                    \
  std::optional<std::reference_wrapper<const std::string>>

class TileMapEntrace : public Tile {
private:
  OPTIONAL_STRING from, to;

public:
  TileMapEntrace(OPTIONAL_STRING from_map_path = OPTIONAL_STRING(),
                 OPTIONAL_STRING to_map_path = OPTIONAL_STRING());
  ~TileMapEntrace() = default;

  TileMapEntrace(const TileMapEntrace &) = default;
  TileMapEntrace(TileMapEntrace &&) = default;

  OPTIONAL_STRING_REF from_map() const;
  OPTIONAL_STRING_REF to_map() const;
  // TileMapEntrace *copy_ptr() const override;

  TileMapEntrace &operator=(const TileMapEntrace &) = default;
  TileMapEntrace &operator=(TileMapEntrace &&) = default;
};

#undef OPTIONAL_STRING
#undef OPTIONAL_STRING_REF
