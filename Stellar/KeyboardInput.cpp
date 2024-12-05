#include "KeyboardInput.hpp"

std::bitset<351> KeyboardInput::m_Keys = {0};

bool KeyboardInput::IsPressed(uint32_t key) {
  if (IsKeyOutOfrange(key)) {
    key = KeycodeFixedLayout(key);
  }
  return KeyboardInput::m_Keys[key];
}

bool KeyboardInput::IsReleased(uint32_t key) {
  if (IsKeyOutOfrange(key)) {
    key = KeycodeFixedLayout(key);
  }
  return !(KeyboardInput::m_Keys[key]);
}

uint32_t KeyboardInput::Size() noexcept { return KeyboardInput::m_Keys.size(); }

void KeyboardInput::ChangeState(uint32_t key, bool value) {
  if (IsKeyOutOfrange(key)) {
    key = KeycodeFixedLayout(key);
    key = std::clamp(key, 0u, 351u);
  }
  KeyboardInput::m_Keys[key] = value;
}

int32_t KeyboardInput::KeycodeFixedLayout(const int32_t key_code) {
  return (key_code - (SDLK_SCANCODE_MASK)) + 66;
}
bool KeyboardInput::IsKeyOutOfrange(const uint32_t key) {
  return (key > KeyboardInput::m_Keys.size());
}