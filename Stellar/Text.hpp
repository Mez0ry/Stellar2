#ifndef __TEXT_HPP__
#define __TEXT_HPP__

#include "Vector.hpp"
#include "Core.hpp"

#include "Font.hpp"
#include "Texture.hpp"
#include "Surface.hpp"

#include "Color.hpp"

class Text : public Font{
public:
  Text() noexcept;
  Text(const Font& font) {ShareFont(font);}
  Text(const Core::Ref<TTF_Font>& font) { ShareFont(font);}
  Text(const Core::Ref<Renderer> renderer,const char* font_path, const int font_size, const char* text,const Color& color);
  Text(const Core::Ref<Renderer> renderer,const Font& font, const char *text, const Color &color);

  ~Text() noexcept;

  Text(Text &&other) {
    (*this) = std::move(other);
  }

  Text(const Text& other) : Font(){
    (*this) = other;
  }

  Text& operator=(const Text& other){
    if(this == &other){
      return (*this);
    }
    this->ShareFont(other.GetFont());
    this->SetFontSize(other.GetFontSize());
    this->SetFontPath(other.GetFontPath().c_str());
    
    this->m_TextTexture = other.m_TextTexture;
    this->m_Color = other.m_Color;
    this->m_LoadedText = std::string(other.m_LoadedText);
    return (*this);
  }

  Text& operator=(Text&& other){
    if(this == &other){
      return (*this);
    }
    this->ShareFont(std::move(GetFont()));
    this->SetFontSize(other.GetFontSize());
    other.SetFontSize(0);

    this->m_TextTexture = std::move(other.m_TextTexture);
    this->m_Color = std::move(other.m_Color);
    this->m_LoadedText = std::move(other.m_LoadedText);
    return (*this);
  }
  
  Texture* operator->(){
    return &m_TextTexture;
  }

  operator Texture&() noexcept{
    return m_TextTexture;
  }

  operator const Texture&() const noexcept{
    return m_TextTexture;
  }

  Texture& LoadText(const Core::Ref<Renderer> renderer,const char *text, const Color &color);
  const std::string& GetLoadedText() const {return m_LoadedText;}
  const Color GetLoadedColor() const {return m_Color;}
  void Reset();
protected:
  Texture& GetTextTexture() {return m_TextTexture;}
  const Texture& GetTextTexture() const {return m_TextTexture;}
private:
  Texture m_TextTexture;
  Color m_Color;
  std::string m_LoadedText;
};
#endif //! __TEXT_HPP__