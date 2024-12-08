#ifndef __WINDOW_INFO_HPP__
#define __WINDOW_INFO_HPP__
#include "SDL2/SDL.h"
#include <bitset>

class WindowInput{
 public:
 WindowInput()  = delete;
 ~WindowInput() = delete;

 static void SetStatus(SDL_WindowEventID event_id, bool status);
 static bool OnEvent(SDL_WindowEventID event_id);
 
 static void Reset();

 std::bitset<255UL>::reference operator[](SDL_WindowEventID key){
    return m_EventsSet[key];
 }
 private:
  static std::bitset<255> m_EventsSet;
};
#endif //!__WINDOW_INFO_HPP__