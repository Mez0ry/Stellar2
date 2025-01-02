#include "Window.hpp"
#include "Logger.hpp"

Window::Window(const char *title, int x, int y, int w,int h, uint32_t flags) : m_Window(nullptr){
    m_Window = SDL_CreateWindow(title,x,y,w,h,flags);

    if(m_Window == nullptr){
        STELLAR_CORE_CRITICAL_THROW(std::runtime_error,"Failed to create a window","Window::Window,Failed to create a window, SDL Error: {0}, Failed at {1}:{2}" , SDL_GetError(),STELLAR_FILENAME, STELLAR_LINE);
    }else{
        STELLAR_CORE_INFO("Window successfully created, title: {0}, position: (x: {1},y: {2}) , size: (w: {3}, h: {4})) ",title,x,y,w,h);
    }
}

Window::~Window(){
    SDL_DestroyWindow(m_Window);
}

void Window::SetMousePositionInWindow(const Core::Ref<Window> window,Vec2i pos){
  if(!window) 
    return;
  SDL_WarpMouseInWindow(*window,pos.x,pos.y);
}

void Window::SetOpacity(float opacity)
{
  if(SDL_SetWindowOpacity((*this),opacity) == -1){
    STELLAR_CORE_ERROR("Failed to set the window opacity, reason: {0}", SDL_GetError());
  }
}

float Window::GetOpacity() const
{
  float curr_opacity = {};
  SDL_GetWindowOpacity((*this),&curr_opacity);
  return curr_opacity;
}

void Window::UpdateWindowSurface(){
    if(SDL_UpdateWindowSurface(m_Window)){
        STELLAR_CORE_ERROR("Window::UpdateWindowSurface,Failed to update window surface, SDL Error: {0}, Failed at {1}:{2}" , SDL_GetError(),STELLAR_FILENAME, STELLAR_LINE);
    }
}

void Window::CreateWindowSurface(){
    m_WindowSurface = SDL_GetWindowSurface(m_Window);
}

void Window::SetIcon(const std::string& icon_path)
{
    SDL_SetWindowIcon(this->GetWindow(),m_IconSurface.LoadSurface(icon_path).get());
}

SDL_Surface* Window::GetWindowSurface(){
    return m_WindowSurface;
}

uint32_t Window::GetPixelFormat(){
    return SDL_GetWindowPixelFormat(m_Window);
}

std::tuple<int,int> Window::GetWindowSize() const{
    std::tuple<int,int> window_size;

    SDL_GetWindowSize(m_Window,&std::get<0>(window_size),&std::get<1>(window_size));
    return window_size;
}