#ifndef __BASE_HPP__
#define __BASE_HPP__
#include <memory>
#include <string>
#include "Logger.hpp"
#include "Literals.hpp"

#define STELLAR_VARIABLE_TO_STRING(var) #var 

namespace Core {

template <typename TObj> using Scope = std::unique_ptr<TObj>;

template <typename TObj, typename... TArgs>
constexpr Scope<TObj> CreateScope(TArgs &&...args) {
  return std::make_unique<TObj>(std::forward<TArgs>(args)...);
}

template <typename TObj> using Ref = std::shared_ptr<TObj>;

template <typename TObj, typename... TArgs>
constexpr Ref<TObj> CreateRef(TArgs &&...args) {
  return std::make_shared<TObj>(std::forward<TArgs>(args)...);
}
 
} // !namespace Core
#endif // __BASE_HPP__