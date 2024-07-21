#include "Font.hpp"

Core::Ref<TTF_Font> Font::LoadFont(const char *path, uint32_t font_size){
  m_Font = Font::StaticLoadFont(path,font_size);
  m_FontSize = font_size;
  m_FontPath = path;
  return m_Font;
}

void Font::ChangeFontSize(int font_size) {
  if(TTF_SetFontSize((*this),font_size) == -1){
    STELLAR_CORE_ERROR("Font::SetFontSize(font_size: {0}), Failed to open font, SDL_ttf Error: {1}, Failed at {2}:{3}",font_size,TTF_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
}

[[nodiscard]] Core::Ref<TTF_Font> Font::StaticLoadFont(const char *path, uint32_t font_size)
{
  TTF_Font* font = TTF_OpenFont(path, font_size);

  auto final_font = Core::Ref<TTF_Font>(font,TTF_FontDeleter());
  
  if (final_font == nullptr)
  {
    STELLAR_CORE_ERROR("static Font::LoadFont(path: {0},font_size: {1}), Failed to open font, SDL_ttf Error: {2}, Failed at {3}:{4}",path,font_size,TTF_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }

  return final_font;
}

void Font::ShareFont(const Core::Ref<TTF_Font>& font)
{
  this->m_Font = font;
}

void Font::ShareFont(const Font& font){
  this->m_Font = font.GetFont();
}

void Font::ResetFont()
{
  if(m_Font.unique()){
    m_Font.reset();
    m_Font = nullptr;
  }
}