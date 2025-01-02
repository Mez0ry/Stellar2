#ifndef __STELLAR_BUTTON_HPP__
#define __STELLAR_BUTTON_HPP__
#include "../Clickable.hpp"
#include "../Hoverable.hpp"
#include "../Text.hpp"
#include "../Literals.hpp"
#include <unordered_map>

class Button : public Hoverable<Clickable<Texture>> {
  Text m_Text;
public:
  Button() : m_Text(nullptr),m_StrText(""),m_Color(0,0,0,255),m_BtnPrevSize(0,0){}

  Button(const Texture& texture) : m_Text(nullptr),m_StrText(""),m_Color(0,0,0,255),m_BtnPrevSize(0,0){
    this->ShareSDLTexture(texture);
  }
  Button(const Texture& texture,const Text& text) : m_Text(text),m_StrText(""),m_Color(0,0,0,255),m_BtnPrevSize(0,0){
    this->ShareSDLTexture(texture);
  }

  Button(const Texture& texture, const char* font_path,const char* text, Color text_color) : m_StrText(text), m_Color(text_color),m_BtnPrevSize(0,0){
    this->ShareSDLTexture(texture);
    m_Text.LoadFont(font_path,15);
  }

  Button(const Texture& texture, const Core::Ref<TTF_Font>& font,const char* text, Color text_color) : m_StrText(text), m_Color(text_color),m_BtnPrevSize(0,0){
    this->ShareSDLTexture(texture);
    m_Text.ShareFont(font);
  }

  void ChangeTextColor(Color color){
    m_Text.ChangeColor(color);
  }

  Color GetTextColor() const {
    return m_Color;
  }
  
  void ChangeText(const std::string text){
    m_Text.ChangeText(text.c_str());
  }
  
  void Render(const Core::Ref<Renderer> renderer,TextRenderType type = TextRenderType::BLENDED){
    if(m_BtnPrevPos != this->GetPosition() || m_BtnPrevSize != this->GetSize() || m_BtnPrevPos.IsEmpty()){
      m_BtnPrevPos = this->GetPosition();
      m_BtnPrevSize = this->GetSize();

      if(m_Text && this->SelfTexture()){
        ScaleTextSizeToFit(m_Text);
      }
    }

    if(this->SelfTexture()){
      renderer->Render(this->SelfTexture());
    }

    if(m_Text){
      auto src_size = ObjectSize(0,0);
      m_Text->QueryTexture(m_Text,nullptr,nullptr,&src_size);
      m_Text->SetRect<SourceRect>({0,0},src_size);
      renderer->Render(m_Text,type);
    }
    
  }

private:
 void ScaleTextSizeToFit(Text& text){
  auto src_size = ObjectSize(0,0);
  text->QueryTexture(text,nullptr,nullptr,&src_size);
  text->SetRect<SourceRect>({0,0},src_size);

  auto button_size = this->GetSize();
  auto final_font_size = button_size.GetHeight() / 2;  

  text.ChangeFontSize(final_font_size);
  auto dest_size = ObjectSize((button_size.GetWidth() * 0.8),button_size.HalfHeight() * 0.8);
  auto center = this->GetRect<DestRect>().Center();

  text->SetRect<DestRect>(Vec2i(center.x - dest_size.HalfWidth(),center.y - dest_size.HalfHeight() ),dest_size);
  text.LoadText(text.GetLoadedText().c_str(),text.GetLoadedColor());
 }

private:
  std::string m_StrText;
  Color m_Color;

  Vec2i m_BtnPrevPos;
  ObjectSize m_BtnPrevSize;
};
#endif //!__STELLAR_BUTTON_HPP__  