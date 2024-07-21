#ifndef __KEYBOARD_INPUT__HPP__
#define __KEYBOARD_INPUT__HPP__
#include "SDL2/SDL_keyboard.h"
#include "algorithm"
#include <bitset>

class KeyboardInput {
public:
  KeyboardInput() = delete;
  ~KeyboardInput() = delete;

  static bool IsPressed(uint32_t key);

  static bool IsReleased(uint32_t key);

  static size_t size();

  static void ChangeState(uint32_t key, bool value);
  std::bitset<351UL>::reference operator[](uint32_t key);

private:
  static int32_t KeycodeFixedLayout(const int32_t key_code);
  static bool IsKeyOutOfrange(const uint32_t key);

private:
  static std::bitset<351> m_Keys;
};
#endif //!__KEYBOARD_INPUT__HPP__