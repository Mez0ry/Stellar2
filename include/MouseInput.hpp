#ifndef __MOUSE_INPUT_HPP__
#define __MOUSE_INPUT_HPP__
#include "SDL2/SDL_mouse.h"
#include "Vector.hpp"
#include <bitset>
#include <unordered_map>

enum class MouseState : uint16_t {
  MOUSE_IN_MOTION = 1,
  MOUSE_BUTTON_UP,
  MOUSE_BUTTON_DOWN,
  MOUSE_EMPTY_STATE = 0
};

class Window;

class MouseInput {
private:

public:
  MouseInput() = delete;
  ~MouseInput() = delete;

  static bool IsPressed(int32_t button);
  static bool IsReleased(int32_t button);
  static bool GetMouseState(MouseState state);
  static Vec2i GetMousePosition();
  
  /**
   * @brief sets mouse position in the global screen space
   */
  static void SetMousePosition(Vec2i pos);
  static void ChangeButtonState(uint32_t button, bool value);
  static void ChangeMouseState(MouseState mouse_state, bool value);

  static void ResetMouseState();

  std::bitset<10UL>::reference operator[](int32_t button) {
    return m_Button[button];
  }

private:
  static std::bitset<10> m_Button;
  static std::unordered_map<MouseState,bool> m_MouseState;
};
#endif //! __MOUSE_INPUT_HPP__