#ifndef __EVENT_HANDLER_HPP__
#define __EVENT_HANDLER_HPP__
#include "SDL2/SDL.h"
#include "KeyboardInput.hpp"
#include "WindowInput.hpp"
#include "MouseInput.hpp"

class EventHandler {
public:
  EventHandler() : m_IsQuit(false) {}
  ~EventHandler() = default;
  
  EventHandler(const EventHandler &) = delete;
  EventHandler(EventHandler &&) = delete;
  EventHandler &operator=(const EventHandler &) = delete;
  EventHandler &operator=(EventHandler &&) = delete;
  
  bool IsQuit() const {return m_IsQuit;}
  
  void PollEvents();

private:
  SDL_Event m_Event;
  bool m_IsQuit;
};
#endif //!__EVENT_HANDLER_HPP__