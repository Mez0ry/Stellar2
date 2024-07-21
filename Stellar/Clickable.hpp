#ifndef __STELLAR_CLICKABLE_HPP__
#define __STELLAR_CLICKABLE_HPP__
#include "Action.hpp"
#include "MouseInput.hpp"
#include <functional>

template <class _Ty, typename ... _Args> 
class Clickable : public _Ty {
public:
  Clickable() = default;
  ~Clickable() = default;

  template <typename _OnClickAction> 
  void OnClick(_OnClickAction action) {
    m_OnClick = action;
  }

  void Execute() { m_OnClick.Execute(); }
  
  bool IsClicked() const {
    return (MouseInput::IsPressed(SDL_BUTTON_LEFT) && AABB::PointIsOnObject(MouseInput::GetMousePosition(), (*this)));
  }

  explicit operator bool() const noexcept { return IsClicked(); }

private:
  Action<_Args ...> m_OnClick;
};

#endif //!__STELLAR_CLICKABLE_HPP__