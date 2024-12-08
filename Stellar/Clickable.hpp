#ifndef __STELLAR_CLICKABLE_HPP__
#define __STELLAR_CLICKABLE_HPP__
#include "Action.hpp"
#include "MouseInput.hpp"
#include <functional>
#include "AABB.hpp"

template <class TDerived, typename ... TArgs> 
class Clickable : public TDerived {
public:
  Clickable() = default;
  ~Clickable() = default;

  template <typename TOnClickAction> 
  void OnClick(TOnClickAction action) {
    m_OnClick = action;
  }

  void Execute() { m_OnClick.Execute(); }
  
  bool IsClicked() const {
    return (MouseInput::IsPressed(SDL_BUTTON_LEFT) && AABB::PointIsOnObject(MouseInput::GetMousePosition(), (*this)));
  }

  explicit operator bool() const noexcept { return IsClicked(); }

private:
  Action<TArgs ...> m_OnClick;
};

#endif //!__STELLAR_CLICKABLE_HPP__