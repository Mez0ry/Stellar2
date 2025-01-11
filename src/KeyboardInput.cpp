#include "KeyboardInput.hpp"

std::bitset<std::numeric_limits<SDL_Keycode>::max()> KeyboardInput::m_Keys = {0};
std::unordered_map<int32_t,int16_t> KeyboardInput::m_KeyPressesCounter = {{0,int16_t(-1)}};
std::unordered_map<SDL_Keycode,KeyState> KeyboardInput::m_KeysState = {};

bool KeyboardInput::IsPressed(SDL_Keycode key) {
  return KeyboardInput::m_Keys[key];
}

bool KeyboardInput::IsReleased(SDL_Keycode key) {
  return !(KeyboardInput::m_Keys[key]);
}

bool KeyboardInput::IsKeyUp(SDL_Keycode key)
{
  return (KeyboardInput::m_KeysState[key] == KeyState::KEY_UP);
}

bool KeyboardInput::IsKeyDown(SDL_Keycode key)
{
  return (KeyboardInput::m_KeysState[key] == KeyState::KEY_DOWN);
}

uint32_t KeyboardInput::Size() noexcept { return KeyboardInput::m_Keys.size(); }

void KeyboardInput::SetKeyState(SDL_Keycode key, KeyState key_state)
{
  KeyboardInput::m_KeysState[key] = key_state;
}

KeyState KeyboardInput::GetKeyState(SDL_Keycode key)
{
  return KeyboardInput::m_KeysState[key];
}

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

void KeyboardInput::ResetKeysState() {
  for (auto &[key, state] : m_KeysState) {
    state = KeyState::EMPTY;
  }
}
