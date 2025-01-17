#ifndef __STELLAR_DRAGGABLE_HPP__
#define __STELLAR_DRAGGABLE_HPP__
#include "AABB.hpp"
#include "MouseInput.hpp"
#include <type_traits>
#include <functional>
#include "Action.hpp"
#include "KeyFrame.hpp"
#include <Renderer.hpp>
#include "Easing.hpp"

template <class TDerived,typename ... TArgs>
class Draggable : public TDerived{
private:
  Stellar::KeyFrame m_EasingKf;
  Stellar::easing_type_t m_Easing;
  int m_EaseDuration;
public:
  Draggable() : m_IsDraggable(false), m_Easing(Stellar::Easing::EaseInSine),m_EaseDuration(1){}
  ~Draggable() = default;

  void OnDrag(int ease_duration,const Stellar::keyframe_action_t& action,Stellar::easing_type_t easing = Stellar::Easing::EaseInSine){
    m_EaseDuration = ease_duration;
    m_Easing = easing;


    m_EasingKf.Setup(m_EaseDuration,action,true);
  }

  /**
   * @brief drags the object
   */
  void Drag(){
    
    m_IsDraggable = true;
  }

  void UpdateDragging( float dt){
    if(!m_EasingKf.IsActionEmpty() && m_IsDraggable){
      m_EasingKf.Update(dt);
    }
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