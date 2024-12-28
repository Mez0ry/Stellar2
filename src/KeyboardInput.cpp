#include "KeyboardInput.hpp"

std::bitset<std::numeric_limits<SDL_Keycode>::max()> KeyboardInput::m_Keys = {0};
std::unordered_map<int32_t,int16_t> KeyboardInput::m_KeyPressesCounter = {{0,int16_t(-1)}};

bool KeyboardInput::IsPressed(SDL_Keycode key) {
  return KeyboardInput::m_Keys[key];
}

bool KeyboardInput::IsReleased(SDL_Keycode key) {
  return !(KeyboardInput::m_Keys[key]);
}

uint32_t KeyboardInput::Size() noexcept { return KeyboardInput::m_Keys.size(); }

void KeyboardInput::ChangeState(SDL_Keycode key, bool value) {
  KeyboardInput::m_Keys[key] = value;
}

void KeyboardInput::SetKeyPressCounter(SDL_Keycode key, int16_t counter)
{
  KeyboardInput::m_KeyPressesCounter[key] = counter;
}

int16_t KeyboardInput::GetKeyPressesCounter(SDL_Keycode key)
{
  KeyboardInput::m_KeyPressesCounter.try_emplace(key,int16_t(-1));

  return KeyboardInput::m_KeyPressesCounter[key];
}