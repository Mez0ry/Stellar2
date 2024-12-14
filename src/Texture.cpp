#include "Texture.hpp"

Texture::Texture() noexcept :m_Angle(0), m_TextureFlip(TextureFlip::SDL_FLIP_NONE), m_Texture(nullptr) {}

Texture::Texture(SDL_Texture * texture){
  (*this) = texture;
}

Texture::~Texture() noexcept{
  Reset();
}

Core::Ref<SDL_Texture> Texture::CreateTextureFromSurface(const Core::Ref<Renderer> renderer,SDL_Surface* surface){
  return CreateTextureFromSurface(*renderer,surface);
}

Core::Ref<SDL_Texture> Texture::CreateTextureFromSurface(Renderer& renderer,SDL_Surface* surface){
  Texture texture = SDL_CreateTextureFromSurface(renderer,surface);
  if(!texture){
    STELLAR_CORE_CRITICAL_THROW(std::runtime_error,"Failed to create texture from surface ","Texture::CreateTextureFromSurface(Renderer& renderer, SDL_Surface* surface), Failed to create texture from surface, SDL Error: {0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
    return nullptr;
  }
  return texture;
}

[[nodiscard]] Core::Ref<SDL_Texture> Texture::CreateTexture(const Core::Ref<Renderer> renderer,uint32_t format, int access, int w, int h){
  return CreateTexture(*renderer,format,access,w,h);
}

[[nodiscard]] Core::Ref<SDL_Texture> Texture::CreateTexture(const Renderer& renderer, uint32_t format, int access, int w, int h){
  SDL_Texture* texture = SDL_CreateTexture(renderer,format,access,w,h);
  if(texture == nullptr){
    STELLAR_CORE_CRITICAL_THROW(std::runtime_error,"Failed to create texture ","Texture::CreateTexture(uint32_t format: {3}, int access: {4}, int w: {5}, int h: {6}), Failed to create texture, SDL Error: {0}, Failed at {1}:{2}",
     SDL_GetError(),
     STELLAR_FILENAME,STELLAR_LINE,
     format,
     access,
     w,h
     );
    return nullptr;
  }
  return Core::Ref<SDL_Texture>(SDL_CreateTexture(renderer,format,access,w,h),TextureDeleter());
}

void Texture::ShareSDLTexture(const Texture& texture) {
  if(m_Texture == texture.m_Texture){
    return;
  }

  Reset();
  m_Texture = texture.m_Texture;
}

void Texture::ShareSDLTexture(const Core::Ref<SDL_Texture> texture) {
  if(m_Texture == texture){
    return;
  }

  Reset();
  m_Texture = texture;
}

void Texture::Reset() {
  if (m_Texture.use_count()) {
    m_Texture.reset();
    m_Texture = nullptr;
  }
}

void Texture::UpdateTexturePixels(const SDL_Rect* rect,const void* pixels,int pitch){
  if(SDL_UpdateTexture(m_Texture.get(),rect,pixels,pitch) != 0){
    STELLAR_CORE_ERROR("Texture::UpdateTexturePixels, Failed to update texture pixels with new pixel data, SDL Error:{0}, Failed at {1}:{2}", SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

void Texture::SetPixelAt(uint8_t* pixels,uint32_t texture_width,const Pointi& point,Color color){
  std::memcpy(&pixels[(point.x + texture_width * point.y) * sizeof(color)],&color,sizeof(color));
}

Color Texture::GetPixelColorAt(uint8_t* pixels, uint32_t texture_width,const Pointi& point){
  Color color;
  memcpy(reinterpret_cast<char*>(&color),reinterpret_cast<char*>(&pixels[(point.x + texture_width * point.y) * sizeof(color)]),sizeof(color));
  
  return color;
}

void Texture::QueryTexture(const Texture &texture, uint32_t *format_out, int *access_out, ObjectSize *size_out)
{
  int w,h;
  SDL_QueryTexture(texture,format_out,access_out,&w,&h);
  if(size_out){
    size_out->SetWidth(w);
    size_out->SetHeight(h);
  }
}

double Texture::RotateTowards(const Pointi pos){
  m_Angle = Angled::Rad2Degree(Pointi::GetRotationAngle(GetPosition(),pos));
  return m_Angle.GetAngle();
}

double Texture::RotateTowards(const Texture& texture){
  m_Angle = Angled::Rad2Degree(Vec2i::GetRotationAngle(texture.GetRect().Center(),texture.GetRect().Center()));
  return m_Angle.GetAngle();
}
