#include "WindowInput.hpp"

std::bitset<255> WindowInput::m_EventsSet = {0};

void WindowInput::SetStatus(SDL_WindowEventID event_id, bool status) {
  m_EventsSet[event_id] = status;
}

bool WindowInput::OnEvent(SDL_WindowEventID event_id) {
  return m_EventsSet[event_id];
}

void WindowInput::Reset() { m_EventsSet.reset(); }