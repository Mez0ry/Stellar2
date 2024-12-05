#include "Renderer.hpp"

#include "Texture.hpp"
#include "Surface.hpp"

#include "Text.hpp"
#include "Vector.hpp"
#include "Logger.hpp"

Renderer::Renderer(const Core::Ref<Window> window, int index, uint32_t flags) : m_Renderer(nullptr) {
  CreateRenderer(*window,index,flags);
}

Renderer::Renderer(Window& window, int index, uint32_t flags) : m_Renderer(nullptr) {
  CreateRenderer(window,index,flags);
}

Renderer::~Renderer() {
  if (m_Renderer) {
    SDL_DestroyRenderer(m_Renderer);
  }
}

void Renderer::CreateRenderer(Window& window,int index,uint32_t flags){
  m_Renderer = SDL_CreateRenderer(window, index, flags);
  if (m_Renderer == NULL) {
    STELLAR_CORE_CRITICAL_THROW(std::runtime_error,"Failed to create Renderer","Renderer::CreateRenderer(Window& window,int index,uint32_t flags), Failed to create renderer, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }else{
    STELLAR_CORE_INFO("Renderer successfully created, the index of the initialized rendering driver: {0}",index);
    window.CreateWindowSurface();
  }
}

void Renderer::RenderClear() { 
  if(SDL_RenderClear(m_Renderer)){
    STELLAR_CORE_ERROR("Renderer::RenderClear, Failed to render clear, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::RenderFlush() { 
  if(SDL_RenderFlush(m_Renderer)){
    STELLAR_CORE_ERROR("Renderer::SDL_RenderFlush, Failed to render flush, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  } 
}

void Renderer::RenderPresent() { 
  SDL_RenderPresent(m_Renderer); 
}

void Renderer::SetRenderDrawColor(const Color &color) {
  if(SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a)){
    STELLAR_CORE_ERROR("Renderer::SetRenderDrawColor, Failed to set renderer draw color, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::Render(const Texture &texture) {
  auto& dst_rect = texture.GetRect<DestRect>();
  auto& src_rect = texture.GetRect<SourceRect>();
  auto* s_rect_res = (!src_rect.IsEmpty()) ? static_cast<const SDL_Rect*>(src_rect): nullptr;
  auto* d_rect_res = (!dst_rect.IsEmpty()) ? static_cast<const SDL_Rect*>(dst_rect): nullptr;

  if(SDL_RenderCopyEx(m_Renderer,texture, s_rect_res,d_rect_res,texture.GetAngle(),texture.GetOrigin(),texture.GetFlip())){
    STELLAR_CORE_ERROR("Renderer::Renderer(const Texture& texture), Failed to render texture, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::BlitSurface(Surface &src,SDL_Surface* dst){
  auto& dst_rect = src.GetRect<DestRect>();
  auto& src_rect = src.GetRect<SourceRect>();
  auto* s_rect_res = (!src_rect.IsEmpty()) ? static_cast<const SDL_Rect*>(src_rect): nullptr;
  auto* d_rect_res = (!dst_rect.IsEmpty()) ? static_cast<SDL_Rect*>(dst_rect): nullptr;

  if(SDL_BlitSurface(src,s_rect_res,dst,d_rect_res)){
    STELLAR_CORE_ERROR("Renderer::BlitSurface(const Surface& src,SDL_Surface* dst), Failed to blit surface, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Renderer::ScaledSurface(Surface& src,SDL_Surface* dst){
  auto& dst_rect = src.GetRect<DestRect>();
  auto& src_rect = src.GetRect<SourceRect>();
  auto* s_rect_res = (!src_rect.IsEmpty()) ? static_cast<const SDL_Rect*>(src_rect): nullptr;
  auto* d_rect_res = (!dst_rect.IsEmpty()) ? static_cast<SDL_Rect*>(dst_rect): nullptr;

  if(SDL_BlitScaled(src,s_rect_res,dst,d_rect_res)){
    STELLAR_CORE_ERROR("Renderer::ScaledSurface(Surface& src,SDL_Surface* dst), Failed to blit surface, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}
