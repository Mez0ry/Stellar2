#ifndef __ENGINE_HPP__
#define __ENGINE_HPP__
#include "Core.hpp"
#include <algorithm>
#include <unordered_map>
#include "init_library.hpp"

class Engine {
private:
  using hash_code_t = std::size_t;
public:
  static bool Initialize(uint32_t sdl2_flags, uint32_t sdl_img_flags, bool initialize_sdl_ttf);
  
  template <typename T,typename ... Args> 
  static void RegisterModule(Args&&... args) {
    auto& context = instance();
    auto& modules_map = context.m_ModulesMap;

    if(!HasModule<T>()){
      modules_map.insert(std::make_pair(context.GetHashCode<T>(), Core::CreateRef<T,Args ...>( std::forward<Args>(args)... )));
    }
  }

  template <typename ... _Ts, class = typename std::enable_if_t<(sizeof...(_Ts) > 1),std::nullptr_t> >
  static void RegisterModule(){
    (RegisterModule<_Ts>(), ...);
  }
  
  template <typename T>
  static void UnRegisterModule(){
    auto& context = instance();
    auto& modules_map = context.m_ModulesMap;

    auto it = std::find_if(modules_map.begin(), modules_map.end(),[&](const auto &service_pair) {
      return (service_pair.first == context.GetHashCode<T>());
    });

    if(it != modules_map.end()){
      modules_map.erase(it);
    }
  }

  template <typename ... _Ts, class = typename std::enable_if_t<(sizeof...(_Ts) > 1),std::nullptr_t> >
  static void UnRegisterModule(){
    (UnRegisterModule<_Ts>(), ...);
  }

  template <typename T>
  static bool HasModule() {
    auto& context = instance();
    auto& modules_map = context.m_ModulesMap;

    auto it = std::find_if(modules_map.begin(), modules_map.end(),[&](const auto &service_pair) {
      return (service_pair.first == context.GetHashCode<T>());
    });

    return (it != modules_map.end()) ? true : false;
  }

  template<typename T>
  [[nodiscard]] static Core::Ref<T> GetModule(){
    auto& context = instance();
    auto& modules_map = context.m_ModulesMap;

    auto it = std::find_if(modules_map.begin(), modules_map.end(),[&](const auto &service_pair) {
      return (service_pair.first == context.GetHashCode<T>());
    });

    if(it != modules_map.end()){
      return std::static_pointer_cast<T>(it->second);
    }
    return nullptr;
  }

    template <typename T>
  static bool HasLibrary() {
    auto& context = instance();
    auto& library_map = context.m_Libraries;

    auto it = std::find_if(library_map.begin(), library_map.end(),[&](const auto &lib_pair) {
      return (lib_pair.first == context.GetHashCode<T>());
    });

    return (it != library_map.end()) ? true : false;
  }

  template <typename T>
  static bool LibraryIsInitialized(){
    auto& context = instance();
    auto& library_map = context.m_Libraries;

    auto it = std::find_if(library_map.begin(), library_map.end(),[&](const auto &lib_pair) {
      return (lib_pair.first == context.GetHashCode<T>());
    });

    if((it != library_map.end())){
      return library_map.find(it)->second->IsInitialized();
    }

    return false;
  }

private:
  template <typename T> 
  hash_code_t GetHashCode() {
    return typeid(decltype(std::declval<T>())).hash_code();
  }

private:
  Engine() {}

  static Engine &instance() {
    static Engine engine;

    if (!Logger::IsCreated()) {
      Logger::OnCreate();
    }

    return engine;
  }

private:
  std::unordered_map<hash_code_t, Core::Ref<void>> m_ModulesMap;
  std::unordered_map<hash_code_t,Core::Ref<void>> m_Libraries;
};

#endif //! __ENGINE_HPP__