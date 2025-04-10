#pragma once
#include <cstdint>
#include <istream>

typedef int32_t vec_comp;

class Vec2 {
public:
  vec_comp x, y;

  Vec2() = default;             // x=0; y=0
  Vec2(const Vec2 &);           // copy
  Vec2(Vec2 &&);                // move
  Vec2(vec_comp x, vec_comp y); // probably the constructor you should use
  Vec2(std::istream &);

  Vec2 operator+(const Vec2 &) const;
  Vec2 operator-(const Vec2 &) const;
  Vec2 operator*(vec_comp) const; // scaling
  Vec2 &operator=(const Vec2 &);  // copy
  Vec2 &operator=(Vec2 &&);       // move
  bool operator==(const Vec2 &) const;

  double length() const; // pythagorus
  // std::optional<vec_comp> dot_product(const Vec2 &) const; // not implemented
};

Vec2 operator*(vec_comp, const Vec2 &); // scaling
