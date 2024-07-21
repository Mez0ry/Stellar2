#ifndef __WINDOW_HPP__
#define __WINDOW_HPP__
#include "SDL2/SDL.h"
#include <cstdint>
#include <tuple>
#include "Surface.hpp"

class Window {
public:
  Window(const char *title, int x, int y, int w, int h, uint32_t flags);
  ~Window();

  Window(const Window &) = delete;
  Window(Window &&) = delete;
  Window &operator=(const Window &) = delete;
  Window &operator=(Window &&) = delete;

  static void SetMousePositionInWindow(const Core::Ref<Window> window,Vec2i pos);

  void UpdateWindowSurface();
  void CreateWindowSurface();

  explicit operator bool() const noexcept { return (m_Window != nullptr); }
  
  operator SDL_Window*() const noexcept{
    return m_Window;
  }

public:
  [[nodiscard]] SDL_Window *GetWindow() const { return m_Window; }

  SDL_Surface* GetWindowSurface();
  
  uint32_t GetPixelFormat();
  
  std::tuple<int,int> GetWindowSize() const;
private:
  SDL_Window *m_Window;
  SDL_Surface* m_WindowSurface;
};
#endif //! __WINDOW_HPP__