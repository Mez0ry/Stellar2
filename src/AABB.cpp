#include "AABB.hpp"
#include "Rect.hpp"

bool AABB::PointIsOnObject(const Pointi &point, const Texture &texture) {
 return (PointIsOnObject(point,texture.GetRect()));
}

bool AABB::PointIsOnObject(const Pointi& point, const Text& text){
  return (PointIsOnObject(point,static_cast<const Texture&>(text)));
}

bool AABB::PointIsOnObject(const Pointi &point, const Rect &rect)
{
  return (point.x >= rect.TopLeft().x && point.x <= rect.TopRight().x && point.y >= rect.TopLeft().y && point.y <= rect.BottomLeft().y);
}

bool AABB::isColliding(const Texture &lhs, const Texture &rhs) {
  return (isColliding(lhs.GetRect(),rhs.GetRect()));
}

bool AABB::isColliding(const Text &lhs, const Text &rhs) {
  return isColliding(static_cast<const Texture&>(lhs),static_cast<const Texture&>(rhs));
}

bool AABB::isColliding(const Rect &lhs, const Rect& rhs)
{
  if (lhs.BottomRight().y <= rhs.TopLeft().y) {
    return false;
  }

  if (lhs.TopLeft().y >= rhs.BottomLeft().y) {
    return false;
  }

  if (lhs.TopRight().x <= rhs.TopLeft().x) {
    return false;
  }

  if (lhs.TopLeft().x >= rhs.TopRight().x) {
    return false;
  }
  return true;
}
