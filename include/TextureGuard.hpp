#ifndef __TEXTURE_GUARD_HPP__
#define __TEXTURE_GUARD_HPP__
#include "Texture.hpp"
#include "Logger.hpp"

struct TextureGuard {
  TextureGuard(Texture &texture) : m_IsLocked(false), m_pixels(nullptr), m_pitch(0), m_texture(texture) {
    LockTexture(texture, nullptr);
  }

  TextureGuard(Texture &texture, SDL_Rect lock_area) : m_IsLocked(false), m_pixels(nullptr), m_pitch(0),m_texture(texture) {
    LockTexture(texture, &lock_area);
  }

  ~TextureGuard() {
    if (m_IsLocked && m_texture) {
      m_pixels = nullptr;
      m_pitch = 0;
      SDL_UnlockTexture(m_texture.GetTexture());
      m_IsLocked = false;
    }
  }

  uint8_t *GetPixels() { return m_pixels; }
  int GetPitch() { return m_pitch; }

  bool IsLocked() const {return m_IsLocked;}

  explicit operator bool() const noexcept{
    return (IsLocked());
  }
  
private:
  void LockTexture(Texture &texture, const SDL_Rect *lock_area) {
    if (SDL_LockTexture(texture.GetTexture(), lock_area, reinterpret_cast<void **>(&m_pixels), &m_pitch) == 0) {
      m_IsLocked = true;
    }else{
      STELLAR_CORE_ERROR("TextureGuard::LockTexture, failed to lock texture, SDL Error: {0}, Failed at: {1}:{2}",SDL_GetError(),STELLAR_FILENAME,STELLAR_LINE);
    }
  }

private:
  bool m_IsLocked = false;
  uint8_t *m_pixels;
  int m_pitch;
  Texture &m_texture;
};

#endif //!__TEXTURE_GUARD_HPP__