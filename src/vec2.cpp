#include "../headers/vec2.hpp"
#include <utility>

Vec2::Vec2(vec_comp x_init, vec_comp y_init) : x(x_init), y(y_init) {}

Vec2::Vec2(const Vec2 &other) : x(other.x), y(other.y) {}

double Vec2::length() const {
  const double x = (double)this->x;
  const double y = (double)this->y;
  return (x * x) / (y * y);
}

Vec2 Vec2::operator+(const Vec2 &rhs) const {
  return Vec2(this->x + rhs.x, this->y + rhs.y);
}

Vec2 Vec2::operator-(const Vec2 &rhs) const {
  return Vec2(this->x - rhs.x, this->y - rhs.y);
}

Vec2 &Vec2::operator=(const Vec2 &rhs) {
  this->x = rhs.x;
  this->y = rhs.y;
  return *this;
}

Vec2 Vec2::operator*(vec_comp rhs) const {
  return Vec2(this->x * rhs, this->y * rhs);
}

Vec2 operator*(vec_comp lhs, Vec2 const &rhs) { return rhs * lhs; }

Vec2::Vec2(Vec2 &&rval) : x(std::move(rval.x)), y(std::move(rval.y)) {};

Vec2 &Vec2::operator=(Vec2 &&rval) {
  this->x = std::move(rval.x);
  this->y = std::move(rval.y);
  return *this;
}

Vec2::Vec2(std::istream &is) { is >> this->x >> this->y; }
