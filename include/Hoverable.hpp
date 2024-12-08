#ifndef __STELLAR_HOVERABLE_HPP__
#define __STELLAR_HOVERABLE_HPP__
#include "Rect.hpp"
#include <functional>
#include "AABB.hpp"
#include "Action.hpp"
#include "MouseInput.hpp"

template <class TDerived,typename ... TArgs>
class Hoverable : public TDerived{
public:
  Hoverable() : m_IsHovered(false){}

  ~Hoverable() = default;

  template <typename TOnHoverAction> 
  void OnHover(TOnHoverAction action) {
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
  Action<TArgs ...> m_OnHover;
  mutable bool m_IsHovered;
};
#endif //!__STELLAR_HOVERABLE_HPP__  