#ifndef __STELLAR_HOVERABLE_HPP__
#define __STELLAR_HOVERABLE_HPP__
#include "Rect.hpp"
#include <functional>
#include "AABB.hpp"

template <class _Ty,typename ... _Args>
class Hoverable : public _Ty{
public:
  Hoverable() : m_IsHovered(false){}

  ~Hoverable() = default;

  template <typename _OnHoverAction> 
  void OnHover(_OnHoverAction action) {
    m_OnHover = action;
  }
  
  void ExecuteOnHover() { m_OnHover.Execute();}
  
  bool IsHovered() const {
    if((AABB::PointIsOnObject(MouseInput::GetMousePosition(), (*this)))){
        m_IsHovered = true;
    }else{
        m_IsHovered = false;
    }
    return m_IsHovered;
  }

  explicit operator bool() const noexcept { return IsHovered(); }

private:
  Action<_Args ...> m_OnHover;
  mutable bool m_IsHovered;
};
#endif //!__STELLAR_HOVERABLE_HPP__