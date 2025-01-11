#include "EventHandler.hpp"

void EventHandler::PollEvents(){
    WindowInput::Reset();
    MouseInput::ResetMouseState();
    KeyboardInput::ResetKeysState();
    
    while(SDL_PollEvent(&m_Event)){
    switch(m_Event.type){
      case SDL_QUIT:{
        m_IsQuit = true;
        break;
      }
      case SDL_KEYDOWN:{
        KeyboardInput::ChangeState(m_Event.key.keysym.sym,true);
        KeyboardInput::SetKeyState(m_Event.key.keysym.sym,KeyState::KEY_DOWN);

        if(m_Event.key.state == SDL_PRESSED){
          auto key_press_cnt_val = KeyboardInput::GetKeyPressesCounter(m_Event.key.keysym.sym);
          KeyboardInput::SetKeyPressCounter(m_Event.key.keysym.sym,++key_press_cnt_val);
        }

        break;
      }
      case SDL_KEYUP:{
        KeyboardInput::ChangeState(m_Event.key.keysym.sym,false);
        KeyboardInput::SetKeyState(m_Event.key.keysym.sym,KeyState::KEY_UP);

        if(m_Event.key.state == SDL_RELEASED){
          KeyboardInput::SetKeyPressCounter(m_Event.key.keysym.sym,-1);
        }
        break;
      }
      
      case SDL_WINDOWEVENT:{
        WindowInput::SetStatus(static_cast<SDL_WindowEventID>(m_Event.window.event),true);
        break;
      }
      case SDL_MOUSEBUTTONDOWN:{
        MouseInput::ChangeButtonState(m_Event.button.button,true);
        MouseInput::ChangeMouseState(MouseState::MOUSE_BUTTON_DOWN,true);

        break;
      }
      case SDL_MOUSEBUTTONUP:{
        MouseInput::ChangeButtonState(m_Event.button.button,false);
        MouseInput::ChangeMouseState(MouseState::MOUSE_BUTTON_UP,true);
        break;
      }
      case SDL_MOUSEMOTION:{
        MouseInput::ChangeMouseState(MouseState::MOUSE_IN_MOTION,true);
        break;
      }
    }
    SDL_Delay(3);
  }
}