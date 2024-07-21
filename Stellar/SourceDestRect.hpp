#ifndef __SOURCE_RECT_HPP__
#define __SOURCE_RECT_HPP__
#include "Rect.hpp"
#include "Logger.hpp"

struct SourceRect {};
struct DestRect {};

template <typename, typename = DestRect> constexpr bool is_dst_rect_v = false;

template <typename T>
constexpr bool is_dst_rect_v<T, DestRect> = std::is_same<T, DestRect>::value;

template <typename, typename = SourceRect> constexpr bool is_src_rect_v = false;

template <typename T>
constexpr bool is_src_rect_v<T, SourceRect> = std::is_same<T, SourceRect>::value;

template <typename _Derived> 
class SourceDestRect {
protected:
  Rect m_src;
  Rect m_dst;
public:
  template <typename T = DestRect>
  void SetRect(const Vec2i &pos, const ObjectSize &size) {
    STELLAR_ASSERT(not is_src_rect_v<T> || not is_dst_rect_v<T>,"template argument is neither SourceRect nor DestRect, it has {0} type",typeid(T).name());
    if constexpr (is_src_rect_v<T>) {
      m_src = pos;
      m_src = size;
    } else if (is_dst_rect_v<T>) {
      m_dst = pos;
      m_dst = size;
    }
  }

  template <typename T = DestRect> 
  const Rect &GetRect() const {
    STELLAR_ASSERT(not is_src_rect_v<T> || not is_dst_rect_v<T>,"template argument is neither SourceRect nor DestRect, it has {0} type",typeid(T).name());
    if constexpr (is_src_rect_v<T>) {
      return m_src;
    } else if (is_dst_rect_v<T>) {
      return m_dst;
    }
  }

   template <typename T = DestRect> 
  Rect &GetRect() {
    STELLAR_ASSERT(not is_src_rect_v<T> || not is_dst_rect_v<T>,"template argument is neither SourceRect nor DestRect, it has {0} type",typeid(T).name());
    if constexpr (is_src_rect_v<T>) {
      return m_src;
    } else if (is_dst_rect_v<T>) {
      return m_dst;
    }
  }

  template <typename T = DestRect>
  void SetSize(const ObjectSize &size) {
    SetRect<T>(GetPosition(),size);
  }

  template <typename T = DestRect> 
  void SetPosition(const Vec2i &pos) {
    SetRect<T>(pos,GetSize());
  }

  template <typename T = DestRect> 
  Vec2i GetPosition() const {
    const Rect& rect = GetRect<T>();
    return Vec2i(rect.x,rect.y);
  }
  
  template <typename T = DestRect> 
  ObjectSize GetSize() const {
    const Rect& rect = GetRect<T>();
    return ObjectSize(rect.w,rect.h);
  }


  template <typename T = DestRect>
  const Vec2i TopLeft() const { return GetPosition<T>(); }

  template <typename T = DestRect>
  const Vec2i TopRight() const {
    return GetRect<T>().TopRight();
  }

  template <typename T = DestRect>
  const Vec2i BottomLeft() const {
    return  GetRect<T>().BottomLeft();
  }

 template <typename T = DestRect>
  const Vec2i BottomRight() const {
    return GetRect<T>().BottomRight();
  }
};

#endif //!__SOURCE_RECT_HPP__