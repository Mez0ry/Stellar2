#ifndef __STELLAR_DRAGGABLE_HPP__
#define __STELLAR_DRAGGABLE_HPP__
#include "AABB.hpp"
#include "MouseInput.hpp"
#include <type_traits>
#include <functional>
#include "Action.hpp"

template <class TDerived,typename ... TArgs>
class Draggable : public TDerived{
private:
  Action<TArgs ...> m_Action;
  double m_t;
  const double m_smoothness = 0.00005555555; // the lower the smoother
public:
  Draggable() : m_t(0.0),m_IsDraggable(false){}
  ~Draggable() = default;
  
  template<typename _OnDragAction>
  void OnDrag(_OnDragAction on_drag_action){
    m_Action = on_drag_action;
  }

  void Drag(){
    if(m_Action){
      m_Action();
    }else{
      auto mouse_pos = MouseInput::GetMousePosition();
      ObjectSize half_object_size = GetDerived().template GetSize<DestRect>() / 2;
      const auto& texture_pos = GetDerived().template GetPosition<DestRect>();

      if(!m_IsDraggable){
        m_t = 0.0;
      }
      
      Vec2i final_pos = Vec2i{mouse_pos.x - half_object_size.GetWidth() ,mouse_pos.y - half_object_size.GetHeight()};
      final_pos = Vec2i::Lerp(texture_pos,final_pos,m_t);
      GetDerived().template SetPosition<DestRect>(final_pos);
      
      if(m_t < 1.0 && m_t >= 0){
        m_t += m_smoothness;
        m_t = std::clamp(m_t,0.0,1.0);
      }
    }

    m_IsDraggable = true;
  }

  void StopDragging(){
    m_IsDraggable = false;
  }

  bool IsDragging() const {return m_IsDraggable;}
private:
  bool m_IsDraggable;
  auto& GetDerived() {return static_cast<TDerived&>((*this)); }
};
#endif //!__STELLAR_DRAGGABLE_HPP__