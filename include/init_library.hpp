#ifndef __SDL_LIBRARIES_HPP__
#define __SDL_LIBRARIES_HPP__
#include "Logger.hpp"
#include <functional>
#include <iostream>
#include <type_traits>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <optional>

namespace details {

enum class LibraryStatus { SUCCESS = 0, FAILED = 1 };

template <class TLibrary ,typename TInitCb,typename TDeinitCb, typename ... TArgs>
class ILibrary {
protected:
  std::function<int(TArgs ...)> m_init;
  std::function<void()> m_deinit;
private:
 TLibrary* Derived() {return static_cast<TLibrary*>(this);}
public:
  ILibrary(TInitCb& init_cb,TDeinitCb& deinit_cb) : m_init(std::function<int(TArgs ...)>(init_cb)), m_deinit(std::function<void()>(deinit_cb)){}
  virtual ~ILibrary() {}

  LibraryStatus Init(TArgs&& ... args) { Derived()->Init(args ...); }
  void DeInit() { m_deinit();}
  const char* GetError() { return Derived()->GetError();}
};

class SDL : public ILibrary<SDL, decltype(SDL_Init),decltype(SDL_Quit),uint32_t> {
public:
  SDL() : ILibrary(SDL_Init,SDL_Quit){}
  
  LibraryStatus Init(uint32_t flags) {
    if (m_init(flags) == 0) {
      return LibraryStatus::SUCCESS;
    }

    return LibraryStatus::FAILED;
  }

  const char *GetError() const  { return SDL_GetError(); }
};

class SDL_Image : public ILibrary<SDL_Image,decltype(IMG_Init), decltype(IMG_Quit),uint32_t> {
public:
  SDL_Image() : ILibrary(IMG_Init,IMG_Quit) {}

  LibraryStatus Init(uint32_t flags) {
    if (((m_init(flags)) & flags) != flags) {
      return LibraryStatus::FAILED;
    }

    return LibraryStatus::SUCCESS;
  }

  const char *GetError() const { return IMG_GetError(); }
};

class SDL_TTF : public ILibrary<SDL_TTF,decltype(TTF_Init),decltype(TTF_Quit)> {

public:
  SDL_TTF() : ILibrary(TTF_Init,TTF_Quit)  {}

  LibraryStatus Init() {
    if (m_init() == 0) {
      return LibraryStatus::SUCCESS;
    }
    return LibraryStatus::FAILED;
  }
  
  const char *GetError() const { return TTF_GetError(); }
};

template <typename T, typename dummy = T>
struct is_sdl_library : std::false_type {};

template <typename T>
struct is_sdl_library<T, typename std::enable_if_t<(std::is_same<T, SDL>::value || std::is_same<T, SDL_Image>::value || std::is_same<T, SDL_TTF>::value),T>> : std::true_type {};

template <typename pack>
struct is_empty : std::false_type
 { };

template <template <auto...> class Z, auto... Is>
struct is_empty<Z<Is...>> : std::bool_constant<sizeof...(Is) == 0U>
 { };

template <typename T, typename ... TArgs> 
class init_library {
private:
  std::unique_ptr<T> m_Lib;
  const std::string m_LibraryName;
  bool m_IsInitialized;
public:
 
  init_library(TArgs ... args) : m_Lib(std::make_unique<T>()),m_LibraryName(GetLibraryName<T>()), m_IsInitialized(false){
    STELLAR_CORE_ASSERT( is_sdl_library<T>::value, "template argument T is not and SDL library, it has type {0} ",typeid(decltype(m_Lib.get())).name());

    if constexpr ((std::is_invocable_v<decltype(&T::Init), T &, TArgs...>)) {
      if (m_Lib->Init(args ...) == LibraryStatus::SUCCESS) {
        STELLAR_CORE_INFO("{0} library successfully initialized", m_LibraryName);
        m_IsInitialized = true;

      } else {
        STELLAR_CORE_ERROR("Failed to initialize {0} library, {0} Error: {1} ", m_LibraryName, m_Lib->GetError());
      }
    }
  }

  init_library(const init_library& other) = delete;
  init_library(init_library& other) = delete;
  init_library& operator=(const init_library&) = delete;
  
  init_library(init_library&& other) = delete;
  init_library& operator=(init_library&& other) = delete;

  bool IsInitialized() const {return m_IsInitialized;}

  void Deinitialize() {
    m_Lib->DeInit();
    m_IsInitialized = false;
    STELLAR_CORE_INFO("{0} library successfully deinitialized",m_LibraryName);
  }

  ~init_library() {
    if(IsInitialized()){
      Deinitialize();
    }
  }
  
  
private:
  template <typename TLibrary>
  const std::string GetLibraryName() {
    const uint8_t size = 100;
    char library_name[size];
    std::memset(&library_name, '\0', sizeof(char) * size);
    std::memcpy(&library_name, &typeid(T).name()[1],strlen(typeid(T).name()) - 1);
    return std::string(library_name,size);
  }
};

} // namespace details
#endif //!__SDL_LIBRARIES_HPP__