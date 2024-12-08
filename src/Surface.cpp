#include "Surface.hpp"

Surface::Surface() noexcept : m_Surface(nullptr){
   
}

Surface::Surface(SDL_Surface* surface) : m_Surface(nullptr){
  m_Surface = SurfaceCreator(surface).CreateSurface();
}

Surface::Surface(const std::string& path) : m_Surface(nullptr){
  LoadSurface(path);
}

Surface::~Surface() noexcept{
  Reset();
}

Core::Ref<SDL_Surface> Surface::LoadSurface(const std::string& image_path){
  Reset();
  m_Surface = SurfaceCreator(image_path).CreateSurface();
  
  return m_Surface;
}

void Surface::ShareSDLSurface(const Surface& surface){
  Reset();
  m_Surface = surface.m_Surface;
}

void Surface::ShareSDLSurface(const Core::Ref<SDL_Surface>& surface){
  Reset();
  m_Surface = surface;
}

void Surface::Reset(){
  if (m_Surface != nullptr) {
    m_Surface.reset();
    m_Surface = nullptr;
  }
}