#ifndef __STELLAR_FONT_HPP__
#define __STELLAR_FONT_HPP__
#include "Core.hpp"
#include "Logger.hpp"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL.h"

struct TTF_FontDeleter {
  void operator()(TTF_Font *font) {
    if (font != nullptr) {
      TTF_CloseFont(font);
      font = nullptr;
    }
  }
};

class Font {
public:
  Font() = default;
  Font(const Core::Ref<TTF_Font>& font) : m_Font(font),m_FontSize(TTF_FontHeight(font.get())){}
  Font(Font &&other) { (*this) = std::move(other); }

  Font(const Font &other) { (*this) = other; }

  ~Font() = default;

  Font &operator=(const Font &other) {
    m_Font = other.m_Font;
    m_FontSize = other.m_FontSize;
    m_FontPath = other.m_FontPath;

    return (*this);
  }

  Font &operator=(const Core::Ref<TTF_Font>& font) {
    m_Font = font;
    return (*this);
  }

  Font &operator=(Font &&other) {
    if (this == &other) {
      return (*this);
    }
    m_Font = std::move(other.m_Font);
    m_FontSize = std::move(other.m_FontSize);
    m_FontPath = std::move(other.m_FontPath);
    other.m_FontSize = 0;
    other.m_Font.reset();
    other.m_Font = nullptr;

    return (*this);
  }
  
  Core::Ref<TTF_Font> LoadFont(const char *path, uint32_t font_size);
  /**
   * @brief changes font size dynamically 
   */
  void ChangeFontSize(int font_size);

  [[nodiscard]] static Core::Ref<TTF_Font> StaticLoadFont(const char *path, uint32_t font_size);
  void ShareFont(const Core::Ref<TTF_Font> &font);
  void ShareFont(const Font& font);
  void ResetFont();
  
  uint32_t GetFontSize() const {return m_FontSize;}
  explicit operator bool() const noexcept { return (m_Font != nullptr); }

  operator TTF_Font *() const noexcept { return m_Font.get(); }

  auto& GetSelfFont() {return (*this);}

  auto& GetFontPath() const {return m_FontPath;}
protected:  
  const Core::Ref<TTF_Font> &GetFont() const { return m_Font; }
  void SetFontSize(uint32_t font_size){m_FontSize = font_size;}
  void SetFontPath(const char* font_path) {m_FontPath = font_path;}
private:
  Core::Ref<TTF_Font> m_Font;
  uint32_t m_FontSize;
  std::string m_FontPath;
};
#endif //! __STELLAR_FONT_HPP__