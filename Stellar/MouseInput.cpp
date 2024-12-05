#include "MouseInput.hpp"

std::bitset<10> MouseInput::m_Button = {0};

std::unordered_map<MouseState, bool> MouseInput::m_MouseState{
    {MouseState::MOUSE_IN_MOTION, false},
    {MouseState::MOUSE_BUTTON_UP, false},
    {MouseState::MOUSE_BUTTON_DOWN, false},
    {MouseState::MOUSE_EMPTY_STATE, false}};

bool MouseInput::IsPressed(int32_t button) { return m_Button[button]; }

bool MouseInput::IsReleased(int32_t button) { return !(m_Button[button]); }

bool MouseInput::GetMouseState(MouseState state) { return m_MouseState[state]; }

Vec2i MouseInput::GetMousePosition() {
  Vec2i pos;
  SDL_GetMouseState(&pos.x, &pos.y);
  return pos;
}

void MouseInput::SetMousePosition(Vec2i pos){
  SDL_WarpMouseGlobal(pos.x,pos.y);
}

void MouseInput::ChangeButtonState(uint32_t button, bool value) {
  m_Button[button] = value;
}

void MouseInput::ChangeMouseState(MouseState mouse_state, bool value) {
  m_MouseState[mouse_state] = value;
}

void MouseInput::ResetMouseState() {
  for (auto &[key, value] : m_MouseState) {
    value = false;
  }
}
