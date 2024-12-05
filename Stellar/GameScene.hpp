#ifndef __GAME_SCENE_HPP__
#define __GAME_SCENE_HPP__
#include "Core.hpp"
#include <vector>
#include <unordered_map>

class Renderer;
class Window;
class EventHandler;

class SceneManager;

class GameScene {
private:
  friend SceneManager;
public:
  virtual ~GameScene() {}

  virtual void OnCreate() {};
  virtual void OnResize([[maybe_unused]] const Core::Ref<Window> window) {}
  virtual void OnDestroy() {};
  
  virtual void HandleInput(const Core::Ref<EventHandler> event_handler) = 0;
  virtual void Update(float dt) = 0;
  virtual void Render(const Core::Ref<Renderer> renderer) = 0;
private:
  std::unordered_map<size_t,Core::Ref<GameScene>> m_BaseChildScenesMap;
};

#endif //! __GAME_SCENE_HPP__