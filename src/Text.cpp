#include "Text.hpp"

Text::Text() noexcept : m_LoadedTextChanged(false),m_ColorChanged(false)  
{
 
}

Text::Text(const Font& font) : m_LoadedTextChanged(false),m_ColorChanged(false)
{
  ShareFont(font);
}

Text::Text(const Core::Ref<TTF_Font>& font) : m_LoadedTextChanged(false),m_ColorChanged(false)
{
  ShareFont(font);
}

Text::Text(const char* font_path, const int font_size, const char* text,const Color& color) : m_Color(color),m_LoadedTextChanged(false),m_ColorChanged(false)
{
  ShareFont(Font::StaticLoadFont(font_path,font_size));
  LoadText(text,m_Color);
  this->SetFontSize(font_size);
}

Text::Text(const Font& font, const char* text,const Color& color) : m_Color(color),m_LoadedTextChanged(false),m_ColorChanged(false)
{
  LoadText(font,text,m_Color);
}

Text::~Text() noexcept
{
  Reset();
}

void Text::ChangeText(const char* text)
{
  if(m_LoadedText != std::string_view(text)){
    m_LoadedText = text;
    m_LoadedTextChanged = true;
  }
}

void Text::ChangeColor(const Color& color)
{
  if(m_Color != color){
    m_Color = color;
    m_ColorChanged = true;
  }
}

void Text::LoadText(const char *text, const Color &color)
{
  Reset();
  ChangeColor(color);
  ChangeText(text);

}

void Text::LoadText(const Font& font,const char *text, const Color &color){
  ShareFont(font);
  LoadText(text,color);
}

void Text::Reset()
{
  m_TextTexture.Reset();
}

void Text::SetLoadedTextStatus(bool value)
{
  m_LoadedTextChanged = value;
}

void Text::SetColorChangedStatus(bool value)
{
  m_ColorChanged = value;
}

bool Text::IsChanged()
{
  return (m_LoadedTextChanged || m_ColorChanged);
}