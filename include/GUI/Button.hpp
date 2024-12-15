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
  Button() : m_Text(nullptr),m_StrText(""),m_strTextChanged(false),m_Color(0,0,0,255),m_ColorChanged(true),m_BtnPrevSize(0,0){}

  Button(const Texture& texture) : m_Text(nullptr),m_StrText(""),m_strTextChanged(false),m_Color(0,0,0,255),m_ColorChanged(true),m_BtnPrevSize(0,0){
    this->ShareSDLTexture(texture);
  }
  Button(const Texture& texture,const Text& text) : m_Text(text),m_StrText(""),m_strTextChanged(false),m_Color(0,0,0,255),m_ColorChanged(false),m_BtnPrevSize(0,0){
    this->ShareSDLTexture(texture);
  }

  Button(const Texture& texture, const char* font_path,const char* text, Color text_color) : m_StrText(text), m_Color(text_color),m_BtnPrevSize(0,0){
    this->ShareSDLTexture(texture);
    m_Text.LoadFont(font_path,15);
    m_ColorChanged = true;
  }

  void ChangeTextColor(Color color){
    if(m_Color != color){
      m_ColorChanged = true;
      m_Color = color;
    }
  }

  Color GetTextColor() const {
    return m_Color;
  }
  
  void ChangeText(const std::string text){
    if(m_Text.GetLoadedText() != text){
      m_StrText = text;
      m_strTextChanged = true;
    }
  }
  
  void Render(const Core::Ref<Renderer> renderer){
    if(m_strTextChanged || m_ColorChanged){
      m_StrText = (m_StrText.empty()) ? m_Text.GetLoadedText() : m_StrText;
      m_Text.LoadText(renderer,m_StrText.c_str(),m_Color);
    }
    
    if(m_BtnPrevPos != this->GetPosition() || m_BtnPrevSize != this->GetSize() || m_BtnPrevPos.IsEmpty()){
      m_BtnPrevPos = this->GetPosition();
      m_BtnPrevSize = this->GetSize();

      if(m_Text && this->operator std::shared_ptr<SDL_Texture>()){
        ScaleTextSizeToFit(renderer,m_Text);
      }
    }

    if(this->operator std::shared_ptr<SDL_Texture>()){
      renderer->Render(this->SelfTexture());
    }

    if(m_Text){
      auto src_size = ObjectSize(0,0);
      m_Text->QueryTexture(m_Text,nullptr,nullptr,&src_size);
      m_Text->SetRect<SourceRect>({0,0},src_size);
      renderer->Render(m_Text);
    }
    
  }

private:
 void ScaleTextSizeToFit(const Core::Ref<Renderer> renderer,Text& text){
  auto src_size = ObjectSize(0,0);
  text->QueryTexture(text,nullptr,nullptr,&src_size);
  text->SetRect<SourceRect>({0,0},src_size);

  auto button_size = this->GetSize();
  auto final_font_size = button_size.GetHeight() / 2;  

  text.ChangeFontSize(final_font_size);
  auto dest_size = ObjectSize((button_size.GetWidth() * 0.8),button_size.HalfHeight() * 0.8);
  auto center = this->GetRect<DestRect>().Center();

  text->SetRect<DestRect>(Vec2i(center.x - dest_size.HalfWidth(),center.y - dest_size.HalfHeight() ),dest_size);
  text.LoadText(renderer,text.GetLoadedText().c_str(),text.GetLoadedColor());
 }

private:
  std::string m_StrText;
  bool m_strTextChanged;

  Color m_Color;
  bool m_ColorChanged;

  Vec2i m_BtnPrevPos;
  ObjectSize m_BtnPrevSize;
};
#endif //!__STELLAR_BUTTON_HPP__  