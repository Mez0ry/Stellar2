#ifndef __KEYBOARD_INPUT__HPP__
#define __KEYBOARD_INPUT__HPP__
#include "SDL2/SDL_keyboard.h"
#include <algorithm>
#include <bitset>
#include <unordered_map>
#include <limits>
class KeyboardInput {
public:
  KeyboardInput() = delete;
  ~KeyboardInput() = delete;

  static bool IsPressed(SDL_Keycode key);

  static bool IsReleased(SDL_Keycode key);

  static uint32_t Size() noexcept;
  
  static void ChangeState(SDL_Keycode key, bool value);
  std::bitset<std::numeric_limits<SDL_Keycode>::max()>::reference operator[](size_t key);

  static void SetKeyPressCounter(SDL_Keycode key, int16_t counter);
  static int16_t GetKeyPressesCounter(SDL_Keycode key);
private:
  static std::bitset<std::numeric_limits<SDL_Keycode>::max()> m_Keys;
  static std::unordered_map<int32_t,int16_t> m_KeyPressesCounter;
};

#endif //!__KEYBOARD_INPUT__HPP__