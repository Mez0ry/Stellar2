#ifndef __SOURCE_RECT_HPP__
#define __SOURCE_RECT_HPP__
#include "Rect.hpp"
#include "Logger.hpp"

struct SourceRect {};
struct DestRect {};

template <class, typename = DestRect> constexpr bool is_dst_rect_v = false;

template <class TRect>
constexpr bool is_dst_rect_v<TRect, DestRect> = std::is_same<TRect, DestRect>::value;

template <class, typename = SourceRect> constexpr bool is_src_rect_v = false;

template <class TRect>
constexpr bool is_src_rect_v<TRect, SourceRect> = std::is_same<TRect, SourceRect>::value;

template <class TDerived> 
class SourceDestRect {
protected:
  Rect m_src;
  Rect m_dst;
public:
  template <class TRect = DestRect>
  void SetRect(const Vec2i &pos, const ObjectSize &size) {
    STELLAR_CORE_ASSERT(not is_src_rect_v<TRect> || not is_dst_rect_v<TRect>,"template argument is neither SourceRect nor DestRect, it has {0} type",typeid(TRect).name());
    if constexpr (is_src_rect_v<TRect>) {
      m_src = pos;
      m_src = size;
    } else if (is_dst_rect_v<TRect>) {
      m_dst = pos;
      m_dst = size;
    }
  }

  template <class TRect = DestRect> 
  const Rect &GetRect() const {
    STELLAR_CORE_ASSERT(not is_src_rect_v<TRect> || not is_dst_rect_v<TRect>,"template argument is neither SourceRect nor DestRect, it has {0} type",typeid(TRect).name());
    if constexpr (is_src_rect_v<TRect>) {
      return m_src;
    } else if (is_dst_rect_v<TRect>) {
      return m_dst;
    }
  }

   template <class TRect = DestRect> 
  Rect &GetRect() {
    STELLAR_CORE_ASSERT(not is_src_rect_v<TRect> || not is_dst_rect_v<TRect>,"template argument is neither SourceRect nor DestRect, it has {0} type",typeid(TRect).name());
    if constexpr (is_src_rect_v<TRect>) {
      return m_src;
    } else if (is_dst_rect_v<TRect>) {
      return m_dst;
    }
  }

  template <class TRect = DestRect>
  void SetSize(const ObjectSize &size) {
    SetRect<TRect>(GetPosition(),size);
  }

  template <class TRect = DestRect> 
  void SetPosition(const Vec2i &pos) {
    SetRect<TRect>(pos,GetSize());
  }

  template <class TRect = DestRect> 
  Vec2i GetPosition() const {
    const Rect& rect = GetRect<TRect>();
    return Vec2i(rect.x,rect.y);
  }
  
  template <class TRect = DestRect> 
  ObjectSize GetSize() const {
    const Rect& rect = GetRect<TRect>();
    return ObjectSize(rect.w,rect.h);
  }


  template <class TRect = DestRect>
  const Vec2i TopLeft() const { return GetPosition<TRect>(); }

  template <class TRect = DestRect>
  const Vec2i TopRight() const {
    return GetRect<TRect>().TopRight();
  }

  template <class TRect = DestRect>
  const Vec2i BottomLeft() const {
    return  GetRect<TRect>().BottomLeft();
  }

 template <class TRect = DestRect>
  const Vec2i BottomRight() const {
    return GetRect<TRect>().BottomRight();
  }
};

#endif //!__SOURCE_RECT_HPP__