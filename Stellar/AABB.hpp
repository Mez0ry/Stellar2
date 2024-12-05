#ifndef __STELLAR_AABB_HPP__
#define __STELLAR_AABB_HPP__
#include "Texture.hpp"
#include "Vector.hpp"
#include "Text.hpp"

class Rect;

class AABB {
public:
  static bool PointIsOnObject(const Pointi &point,const Texture &texture);
  static bool PointIsOnObject(const Pointi& point, const Text& text);
  static bool PointIsOnObject(const Pointi& point, const Rect& rect);
  
  static bool isColliding(const Texture &lhs, const Texture &rhs);
  static bool isColliding(const Text &lhs, const Text &rhs);
  static bool isColliding(const Rect& lhs, const Rect& rhs);
private:
  AABB() = default;
  ~AABB() = default;
};
#endif //!__STELLAR_AABB_HPP__