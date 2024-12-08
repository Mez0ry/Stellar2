#include "Text.hpp"

Text::Text() noexcept
{
 
}
Text::Text(const Core::Ref<Renderer> renderer,const char* font_path, const int font_size, const char* text,const Color& color) : m_Color(color)
{
  ShareFont(Font::StaticLoadFont(font_path,font_size));
  LoadText(renderer,text,m_Color);
  this->SetFontSize(font_size);
}

Text::Text(const Core::Ref<Renderer> renderer,const Font& font, const char* text,const Color& color) : m_Color(color)
{
  ShareFont(font);
  LoadText(renderer,text,m_Color);
}

Text::~Text() noexcept
{
  Reset();
}

Texture& Text::LoadText(const Core::Ref<Renderer> renderer,const char *text, const Color &color)
{
  Reset();
  m_Color = color;
  m_LoadedText = text;
  
  if(!GetFont()){
    STELLAR_CORE_CRITICAL_THROW(std::runtime_error,"m_Font is nullptr"," arg text: {0}, Failed at {1}:{2}",text,STELLAR_FILENAME,STELLAR_LINE);
  }
  
  Surface surface = TTF_RenderText_Solid(GetFont().get(), text, color);
  if (surface == nullptr)
  {
    STELLAR_CORE_ERROR("Text::LoadText, Failed to create text surface, SDL_ttf Error: {0}, Failed at {1}:{2}", TTF_GetError(),STELLAR_FILENAME,STELLAR_LINE);
  }
  
  m_TextTexture.ShareSDLTexture(Texture::CreateTextureFromSurface(renderer,surface));
  
  return m_TextTexture;
}

void Text::Reset()
{
  m_TextTexture.Reset();
}