#ifndef __KEYBOARD_INPUT__HPP__
#define __KEYBOARD_INPUT__HPP__
#include "SDL2/SDL_keyboard.h"
#include <algorithm>
#include <bitset>
#include <unordered_map>
#include <limits>

enum class KeyState : uint8_t{
  KEY_UP,KEY_DOWN, EMPTY
};

class KeyboardInput {
public:
  KeyboardInput() = delete;
  ~KeyboardInput() = delete;

  static bool IsPressed(SDL_Keycode key);
  static bool IsReleased(SDL_Keycode key);

  static bool IsKeyUp(SDL_Keycode key);
  static bool IsKeyDown(SDL_Keycode key);

  static uint32_t Size() noexcept;
  
  static void SetKeyState(SDL_Keycode key, KeyState key_state);
  static KeyState GetKeyState(SDL_Keycode key);

  static void ChangeState(SDL_Keycode key, bool value);
  std::bitset<std::numeric_limits<SDL_Keycode>::max()>::reference operator[](size_t key);

  static void SetKeyPressCounter(SDL_Keycode key, int16_t counter);
  static int16_t GetKeyPressesCounter(SDL_Keycode key);

  static void ResetKeysState();
private:
  static std::unordered_map<SDL_Keycode,bool> m_Keys;
  static std::unordered_map<int32_t,int16_t> m_KeyPressesCounter;
  static std::unordered_map<SDL_Keycode,KeyState> m_KeysState;
};

#endif //!__KEYBOARD_INPUT__HPP__