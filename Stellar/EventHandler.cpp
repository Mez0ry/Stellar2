#include "EventHandler.hpp"

void EventHandler::PollEvents(){
    WindowInput::Reset();
    MouseInput::ResetMouseState();

    while(SDL_PollEvent(&m_Event)){
    switch(m_Event.type){
      case SDL_QUIT:{
        m_IsQuit = true;
        break;
      }
      case SDL_KEYDOWN:{
        KeyboardInput::ChangeState(m_Event.key.keysym.sym,true);
        break;
      }
      
      case SDL_KEYUP:{
        KeyboardInput::ChangeState(m_Event.key.keysym.sym,false);
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