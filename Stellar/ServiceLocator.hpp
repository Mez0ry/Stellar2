#ifndef __SERVICE_LOCATOR_HPP__
#define __SERVICE_LOCATOR_HPP__
#include "Core.hpp"
#include <algorithm>
#include <unordered_map>

class ServiceLocator {
private:
  using hash_code = std::size_t;

public:
  template <typename T,typename ... Args> 
  static void RegisterService(Args&&... args) {
    auto& context = instance();
    auto& services_map = context.m_ServicesMap;

    if(!HasService<T>()){
      services_map.insert(std::make_pair(context.GetHashCode<T>(), Core::CreateRef<T,Args ...>( std::forward<Args>(args)... )));
    }
  }

  template <typename ... _Ts, class = typename std::enable_if_t<(sizeof...(_Ts) > 1),std::nullptr_t> >
  static void RegisterService(){
    (RegisterService<_Ts>(), ...);
  }

  template <typename T>
  static void UnRegisterService(){
    auto& context = instance();
    auto& services_map = context.m_ServicesMap;

    auto it = std::find_if(services_map.begin(), services_map.end(),[&](const auto &service_pair) {
      return (service_pair.first == context.GetHashCode<T>());
    });

    if(it != services_map.end()){
      services_map.erase(it);
    }
  }

  template <typename ... _Ts, class = typename std::enable_if_t<(sizeof...(_Ts) > 1),std::nullptr_t> >
  static void UnRegisterService(){
    (UnRegisterService<_Ts>(), ...);
  }

  template <typename T>
  static bool HasService() {
    auto& context = instance();
    auto& services_map = context.m_ServicesMap;

    auto it = std::find_if(services_map.begin(), services_map.end(),[&](const auto &service_pair) {
      return (service_pair.first == context.GetHashCode<T>());
    });

    return (it != services_map.end()) ? true : false;
  }

  template<typename T>
  [[nodiscard]] static Core::Ref<T> GetService(){
    auto& context = instance();
    auto& services_map = context.m_ServicesMap;

    auto it = std::find_if(services_map.begin(), services_map.end(),[&](const auto &service_pair) {
      return (service_pair.first == context.GetHashCode<T>());
    });

    if(it != services_map.end()){
      return std::static_pointer_cast<T>(it->second);
    }
    return nullptr;
  }

private:
  template <typename T> 
  hash_code GetHashCode() {
    return typeid(decltype(std::declval<T>())).hash_code();
  }

private:
  ServiceLocator() {}

  static ServiceLocator &instance() {
    static ServiceLocator service_locator;
    return service_locator;
  }

private:
  std::unordered_map<hash_code, Core::Ref<void>> m_ServicesMap;
};
#endif //! __SERVICE_LOCATOR_HPP__