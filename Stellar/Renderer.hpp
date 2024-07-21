#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__
#include "SDL2/SDL.h"
#include "SDL2/SDL_rect.h"
#include "Window.hpp"
#include "Core.hpp"
#include "Color.hpp"
#include "Vector.hpp"

class Texture;

class Text;

class Surface;

class Renderer {
public:
  Renderer() = default;
  Renderer(const Core::Ref<Window> window, int index, uint32_t flags);
  Renderer(Window& window, int index, uint32_t flags);
  ~Renderer();

  Renderer(const Renderer&) = delete;
  Renderer(Renderer&&) = delete;
  Renderer& operator=(const Renderer&) = delete;
  Renderer& operator=(Renderer&&) = delete;
public:
  void CreateRenderer(Window& window,int index,uint32_t flags);
  void RenderClear();
  void RenderFlush();
  void RenderPresent();
public:
  void SetRenderDrawColor(const Color& color);
  
  void Render(const Texture &texture);
  void BlitSurface(Surface& src,SDL_Surface* dst);
  void ScaledSurface(Surface& src,SDL_Surface* dst);
public:
/**
 * @todo primitives
 */
  

public:
  [[nodiscard]] SDL_Renderer *GetRenderer() const { return m_Renderer; }
 
  explicit operator bool() const noexcept{
    return (m_Renderer != nullptr);
  }

  operator SDL_Renderer*() const noexcept{
    return m_Renderer;
  }
  
private:
  SDL_Renderer *m_Renderer;
};
#endif //!__RENDERER_HPP__