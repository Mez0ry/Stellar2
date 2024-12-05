#ifndef __APPLICATION_HPP__
#define __APPLICATION_HPP__
#include "Core.hpp"
#include <cstdint>

#include "Engine.hpp"
#include "Renderer.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"

#include "SceneManager.hpp"
#include "GameScene.hpp"

class Menu : public GameScene{
public:
  Menu(const Core::Ref<Renderer> renderer, const Core::Ref<Window> window, SceneManager* scene_manager){}
  
  void OnCreate() { m_Once = false;};
  void OnResize([[maybe_unused]] const Core::Ref<Window> window) override {}
  void OnDestroy() {};
  
  void HandleInput(const Core::Ref<EventHandler> event_handler) override {}
  void Update(float dt) override {if(!m_Once){m_Once = !m_Once; STELLAR_CORE_INFO("Menu scene updated, counter: {0}",i);}}
  void Render(const Core::Ref<Renderer> renderer) override {}
private:
  bool m_Once = false;
  int i = 0;
};

class Exit : public GameScene{
public:
  void OnCreate() { m_Once = false;};
  void OnResize([[maybe_unused]] const Core::Ref<Window> window) override {}
  void OnDestroy() {};
  
  void HandleInput(const Core::Ref<EventHandler> event_handler) override {}
  void Update(float dt) override {if(!m_Once){m_Once = !m_Once; STELLAR_CORE_INFO("Exit scene updated, counter: {0}",i);}}
  void Render(const Core::Ref<Renderer> renderer) override {}
private:
  bool m_Once = false;
  int i = 0;
};

class Playing : public GameScene{
public:
  void OnCreate() { m_Once = false;};
  void OnResize([[maybe_unused]] const Core::Ref<Window> window) override {}
  void OnDestroy() {};
  
  void HandleInput(const Core::Ref<EventHandler> event_handler) override {}
  void Update(float dt) override {if(!m_Once){ m_Once = !m_Once; STELLAR_CORE_INFO("Playing scene updated, counter: {0}",i);}}
  void Render(const Core::Ref<Renderer> renderer) override {}
private:
  bool m_Once = false;
  int i = 0;
};

class Application{
public:
    Application();
    ~Application();
    
    /**
     * @brief Runs the application
     * @returns true on success and false on failure
     */
    bool Run();
private:
    void InputHandler();
    void Update([[maybe_unused]] double dt = 1.0);
    void Render();
    
private:
    bool m_bIsRunning;
    SceneManager m_SceneManager;
};

#endif // __APPLICATION_HPP__