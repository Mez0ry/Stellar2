#ifndef __RECT_HPP__
#define __RECT_HPP__
#include "ObjectSize.hpp"
#include "SDL2/SDL_rect.h"
#include "Vector.hpp"

class Rect {
public:
  int x, y, w, h;

public:
  Rect() : x(0), y(0), w(0), h(0){};
  ~Rect() = default;

  Rect(int x_, int y_, int w_, int h_) : x(x_), y(y_), w(w_), h(h_) {}
  Rect(const Vec2i &pos, int w_, int h_) : x(pos.x), y(pos.y), w(w_), h(h_) {}
  Rect(const Vec2i &pos, const ObjectSize &rect_size)
      : x(pos.x), y(pos.y), w(rect_size.GetWidth()), h(rect_size.GetHeight()) {}

  Rect &operator-=(const Vec2i &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return (*this);
  }

  Rect &operator+=(const Vec2i &rhs) {
    x += rhs.x;
    y += rhs.y;
    return (*this);
  }

  friend Rect operator+(Rect lhs, const Vec2i &rhs) {
    lhs += rhs;
    return lhs;
  }

  friend Rect operator-(Rect lhs, const Vec2i &rhs) {
    lhs -= rhs;
    return lhs;
  }

  Rect &operator-=(const ObjectSize &rhs) {
    w -= rhs.GetWidth();
    h -= rhs.GetHeight();
    return (*this);
  }

  Rect &operator+=(const ObjectSize &rhs) {
    w += rhs.GetWidth();
    h += rhs.GetHeight();
    return (*this);
  }

  friend Rect operator+(Rect lhs, const ObjectSize &rhs) {
    lhs += rhs;
    return lhs;
  }

  friend Rect operator-(Rect lhs, const ObjectSize &rhs) {
    lhs -= rhs;
    return lhs;
  }

  Rect &operator=(const ObjectSize &rhs) {
    w = rhs.GetWidth();
    h = rhs.GetHeight();
    return (*this);
  }

  Rect &operator=(const Vec2i &pos) {
    x = pos.x;
    y = pos.y;
    return (*this);
  }

  constexpr bool operator==(int rhs) const {
    return (x == rhs && y == rhs && w == rhs && h == rhs);
  }

  constexpr bool operator!=(int rhs) const {
    return !(x == rhs && y == rhs && w == rhs && h == rhs);
  }

  bool IsEmpty() const { return ((*this) == 0); }

  const Vec2i TopLeft() const { return Vec2i(x, y); }

  const Vec2i TopRight() const { return Vec2i(x + w, y); }

  const Vec2i BottomLeft() const { return Vec2i(x, y + h); }

  const Vec2i BottomRight() const { return Vec2i(x + w, y + h); }

  const Vec2i Center() const { return Vec2i{x + (w / 2), y + (h / 2)};}

  const Vec2i MidLeft() const { return Vec2i(x, (y + h) / 2); }
  
  const Vec2i MidRight() const { return Vec2i(x + w, (y + h) / 2); }

  const Vec2i MidTop() const { return Vec2i((x + w) / 2, y); }

  const Vec2i MidBottom() const { return Vec2i((x + w) / 2, (y + h) / 2); }

  operator const SDL_Rect *() const noexcept {
    if (IsEmpty())
      return nullptr;
    const_cast<SDL_Rect &>(m_Rect).x = x;
    const_cast<SDL_Rect &>(m_Rect).y = y;
    const_cast<SDL_Rect &>(m_Rect).w = w;
    const_cast<SDL_Rect &>(m_Rect).h = h;
    return &m_Rect;
  }

  operator SDL_Rect *() noexcept {
    if (IsEmpty())
      return nullptr;
    m_Rect.x = x;
    m_Rect.y = y;
    m_Rect.w = w;
    m_Rect.h = h;
    return &m_Rect;
  }

private:
  SDL_Rect m_Rect;
};
#endif //! __RECT_HPP__