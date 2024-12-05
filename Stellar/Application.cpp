#include "Application.hpp"

Application::Application() : m_bIsRunning(false)
{
    if(Engine::Initialize(SDL_INIT_EVERYTHING,IMG_INIT_PNG | IMG_INIT_JPG,true)){
        m_bIsRunning = true;
        
        Engine::RegisterModule<Window>("Stellar test",0,0,800,800, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
        Engine::RegisterModule<Renderer>(Engine::GetModule<Window>(),-1,SDL_RENDERER_SOFTWARE | SDL_RENDERER_TARGETTEXTURE);
        Engine::RegisterModule<EventHandler>();
        m_SceneManager.AddScene<Menu>(Engine::GetModule<Renderer>(),Engine::GetModule<Window>(),&m_SceneManager);
        m_SceneManager.AddChildScene<Menu,Playing>();
        m_SceneManager.AddChildScene<Menu,Exit>();
    }
}

Application::~Application()
{
    
}

bool Application::Run()
{
    if(!m_bIsRunning){
        return false;
    }

    auto renderer = Engine::GetModule<Renderer>();
    renderer->SetRenderDrawColor(Color(255,0,0,255));

    while(m_bIsRunning){
        renderer->RenderClear();

        InputHandler();
        Update();
        Render();

        renderer->RenderPresent();
        SDL_Delay(5);
    }
    
    return true;
}

void Application::InputHandler()
{
   auto events = Engine::GetModule<EventHandler>();
   events->PollEvents();
   if(KeyboardInput::IsPressed(SDLK_0)){
        m_SceneManager.TransitionTo<Playing>();
   }else if(KeyboardInput::IsPressed(SDLK_1)){
        m_SceneManager.TransitionTo<Menu>();
   }else if(KeyboardInput::IsPressed(SDLK_2)){
     m_SceneManager.TransitionTo<Menu,Exit>();
   }else if(KeyboardInput::IsPressed(SDLK_3)){

   }
}

void Application::Update([[maybe_unused]] double dt)
{
    m_SceneManager.Update(dt);
}

void Application::Render()
{
    auto renderer = Engine::GetModule<Renderer>();
    if(!renderer){
        return;
    }
}
