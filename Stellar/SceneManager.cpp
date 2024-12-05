#include "SceneManager.hpp"

SceneManager::SceneManager(): m_pCurrentScene(nullptr), m_CurrentSceneHash(0) {
    
}

SceneManager::~SceneManager() {}

void SceneManager::OnResize(const Core::Ref<Window> window){
    if(!m_pCurrentScene) 
        return;
    m_pCurrentScene->OnResize(window);
}

void SceneManager::HandleInput(const Core::Ref<EventHandler> event_handler) { 
    if(!m_pCurrentScene) 
        return;
    m_pCurrentScene->HandleInput(event_handler); 
}

void SceneManager::Update(float dt) {
    if(!m_pCurrentScene) 
        return;
    m_pCurrentScene->Update(dt); 
}

void SceneManager::Render(const Core::Ref<Renderer> renderer) {
    if(!m_pCurrentScene) 
        return;
    m_pCurrentScene->Render(renderer); 
}
