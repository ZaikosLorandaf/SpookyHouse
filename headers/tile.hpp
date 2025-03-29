#pragma once
class Tile {
public:
  virtual ~Tile() = 0;
  virtual Tile *copy_ptr() const = 0;
};

class TileWall : public Tile {
public:
  TileWall() = default;
  ~TileWall() = default;
  TileWall(const TileWall &);
  TileWall *copy_ptr() const override;
};

class TileEmpty : public Tile {
public:
  TileEmpty() = default;
  ~TileEmpty() = default;
  TileEmpty(const TileEmpty &);
  TileEmpty *copy_ptr() const override;
};
