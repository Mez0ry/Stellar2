#ifndef __SCENE_MANAGER_HPP__
#define __SCENE_MANAGER_HPP__
#include "Core.hpp"
#include "GameScene.hpp"
#include <unordered_map>
#include <algorithm>
#include <stdexcept>

class SceneManager {
private:
  using hash_code_t = std::size_t;
  using scene_map_t = std::unordered_map<hash_code_t, Core::Ref<GameScene>>;
public:
  SceneManager();
  ~SceneManager();
  
  void OnResize(const Core::Ref<Window> window);
  void HandleInput(const Core::Ref<EventHandler> event_handler);
  void Update(float dt);
  void Render(const Core::Ref<Renderer> renderer);

  /**
   * @brief Adds the root scene to the map
   * @tparam TScene scene to add
   * @tparam TArgs scene args to construct object
   */
  template <typename TScene, typename... TArgs> 
  void AddScene(TArgs &&...args) {
    static_assert(std::is_base_of_v<GameScene,TScene>,"Scene that you trying to add must be base of 'GameScene' ");

    if (!HasScene<TScene>()) {
      auto curr_scene = Core::CreateRef<TScene>(std::forward<TArgs>(args)...);
      auto hash_code_t = GetHashCode<TScene>();

      if(!m_pCurrentScene && m_RootScenesMap.empty()){ // the first added scene is the default one
        m_CurrentSceneHash = hash_code_t;
        m_pCurrentScene = curr_scene;
      }
    
      m_RootScenesMap.insert(std::make_pair(hash_code_t, curr_scene));
    }
  }
  /// @brief Adds child scene to some root scene
  /// @tparam TRootScene root scene
  /// @tparam TChildScene  child scene that will be attached to the root scene
  /// @tparam ...TChildArgs type of child args
  /// @param ...child_args child args to construct child scene object
  template <typename TRootScene,typename TChildScene, typename ... TChildArgs>
  void AddChildScene(TChildArgs &&... child_args){
    static_assert(std::is_base_of_v<GameScene,TChildScene>,"Child scene that you trying to add must be base of 'GameScene' ");
    
    auto root_it = GetSceneIt<TRootScene>(m_RootScenesMap);
    if(root_it == m_RootScenesMap.end()) 
      return;

    if(!HasScene<TRootScene,TChildScene>()){
      auto& child_nodes_map = root_it->second->m_BaseChildScenesMap;

      auto curr_child_scene = Core::CreateRef<TChildScene>(std::forward<TChildArgs>(child_args)...);
      auto child_hash_code = GetHashCode<TChildScene>();

      if(!m_pCurrentScene && child_nodes_map.empty()){
        m_CurrentSceneHash = child_hash_code;
        m_pCurrentScene = curr_child_scene;
      }

      child_nodes_map.insert(std::make_pair(child_hash_code,curr_child_scene));
    }
  }

  template <typename TScene> 
  bool HasScene() const {
    return !(GetSceneIt<TScene>(m_RootScenesMap) == m_RootScenesMap.end());
  }
  
  template <typename TRootScene, typename TChildScene>
  bool HasScene() const{
    const auto& child_map = GetChildSceneMap<TRootScene>(m_RootScenesMap);

    return !(GetSceneIt<TRootScene,TChildScene>(m_RootScenesMap) == child_map.end());
  }

  template <typename TScene> 
  void TransitionTo() {
    if(!m_pCurrentScene || m_RootScenesMap.empty()){
      return;
    }

    hash_code_t scene_hash = GetHashCode<TScene>();
    if (m_CurrentSceneHash == scene_hash)
      return;
    
    auto it = GetSceneIt<TScene>(m_RootScenesMap);

    if(it == m_RootScenesMap.end()){
      STELLAR_CORE_ERROR("Failed to get scene from root scenes map, transition won't be made");
      return ;
    }

    if(!IsRootOfChild<TScene>(m_CurrentSceneHash) && IsChildScene(m_CurrentSceneHash)){
      auto& scene_ref = *m_pCurrentScene;
      STELLAR_CORE_WARN_ONCE("scene transition has been failed cos it was attempt to make a transition to wrong root scene, from {0} scene to the root {1}",typeid(scene_ref).name(), typeid(TScene).name());
      return;
    }

    if (m_pCurrentScene != nullptr) {
      m_pCurrentScene->OnDestroy();
      m_pCurrentScene = nullptr;
    }
     
    m_pCurrentScene = it->second;
    m_pCurrentScene->OnCreate();
    m_CurrentSceneHash = scene_hash;
  }

  /// @brief Transition from root scene to its child
  /// @tparam TRootScene root scene
  /// @tparam TChildScene child scene
  template <typename TRootScene, typename TChildScene>
  void TransitionTo(){
    if(!m_pCurrentScene || m_RootScenesMap.empty()){
      return;
    }

    auto child_scene_hash = GetHashCode<TChildScene>();

    if(m_CurrentSceneHash == child_scene_hash)
      return;
    
    auto is_not_child_scene = !IsChildScene(m_CurrentSceneHash);

    if(is_not_child_scene && m_pCurrentScene->m_BaseChildScenesMap.count(child_scene_hash) == 0){
      auto& scene_ref = *m_pCurrentScene;
      STELLAR_CORE_WARN_ONCE("scene transition has been failed cos it was attempt to make a transition to  wrong root scene. Scene transition: from {0}(root scene)  to the {1} scene which is the root of {2} ",typeid(scene_ref).name(), typeid(TChildScene).name(), typeid(TRootScene).name());
      return;
    }
    
    auto child_scene_it = GetSceneIt<TRootScene,TChildScene>(m_RootScenesMap);
    
    if(child_scene_it == GetChildSceneMap<TRootScene>(m_RootScenesMap).end()){
      return;
    }
    
    if (m_pCurrentScene != nullptr) {
      m_pCurrentScene->OnDestroy();
      m_pCurrentScene = nullptr;
    }

    m_pCurrentScene = child_scene_it->second;
    m_pCurrentScene->OnCreate();
    m_CurrentSceneHash = child_scene_hash;
  }
  
  template <typename TRootScene>
  bool IsRootOfChild(const hash_code_t child_hash) const{
    
    if(m_RootScenesMap.count(child_hash) > 0){
      return false;
    }

    auto it = GetSceneIt<TRootScene>(m_RootScenesMap);
    
    if(it != m_RootScenesMap.end()){

      if(it->second->m_BaseChildScenesMap.empty()){
        return false;
      }
    
      if(it->second->m_BaseChildScenesMap.count(child_hash) > 0){
        return true;
      }
    }
    
    return false;
  }

private:
 
  /// @brief searches for scene in map
  /// @tparam TScene scene type that we trying to find in map
  /// @param scene_map map of scenes
  /// @return iterator of scene
  template <typename TScene>
  auto GetSceneIt(const scene_map_t& scene_map) const{
    auto it = std::find_if(scene_map.begin(), scene_map.end(), [&](const auto &scene_pair) {
        return (scene_pair.first == GetHashCode<TScene>());
    });

    return it;
  }

  /// @brief searches for child scene in the Root scene
  /// @tparam TRootScene root scene type
  /// @tparam TChildScene  child scene type
  /// @param root_scene_map 
  /// @throws runtime error in case if RootScene couldn't be found or if ChildScene couldn't be found
  /// @returns iterator of child scene
  template <typename TRootScene, typename TChildScene>
  auto GetSceneIt(const scene_map_t& root_scene_map) const{
    auto root_it = GetSceneIt<TRootScene>(root_scene_map);

    if(root_it == root_scene_map.end()){
      const std::string error = "TRootScene doesnt exist, TRootScene name: " + (std::string)typeid(TRootScene).name();
      throw std::invalid_argument(error);
    }

    auto& child_scenes_map = root_it->second->m_BaseChildScenesMap;
    auto child_it = GetSceneIt<TChildScene>(child_scenes_map);

    return child_it;
  }


  template <typename TRootScene>
  const scene_map_t& GetChildSceneMap(const scene_map_t& root_scene_map) const{
    auto root_it = GetSceneIt<TRootScene>(root_scene_map);
    if(root_it == root_scene_map.end()){
      const std::string error = "TRootScene doesn't exist, TRootScene name: " + (std::string)typeid(TRootScene).name();
      throw std::invalid_argument(error);
      return root_scene_map;
    }

    auto& child_scenes_map = root_it->second->m_BaseChildScenesMap;

    return child_scenes_map;
  }

  bool IsChildScene(hash_code_t child_hash) const{
      auto& root = m_RootScenesMap;

      if(root.count(child_hash) > 0){
        return false;
      }

      for(auto& scene : root){
        if(scene.second->m_BaseChildScenesMap.count(child_hash) > 0){
          return true;
        }
      }
      return false;
  }
private:
  template <typename TScene> 
  hash_code_t GetHashCode() const{
    return typeid(decltype(std::declval<TScene>())).hash_code();
  }

private:
  scene_map_t m_RootScenesMap;
  Core::Ref<GameScene> m_pCurrentScene;
  hash_code_t m_CurrentSceneHash;
};

#endif //!__SCENE_MANAGER_HPP__