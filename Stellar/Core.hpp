#ifndef __BASE_HPP__
#define __BASE_HPP__
#include "init_library.hpp"
#include <memory>
#include <string>
#include "Logger.hpp"
#include "Literals.hpp"

#define STELLAR_VARIABLE_TO_STRING(var) #var 

namespace Core {

template <typename T> using Scope = std::unique_ptr<T>;

template <typename T, typename... Args>
constexpr Scope<T> CreateScope(Args &&...args) {
  return std::make_unique<T>(std::forward<Args>(args)...);
}

template <typename T> using Ref = std::shared_ptr<T>;

template <typename T, typename... Args>
constexpr Ref<T> CreateRef(Args &&...args) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

struct LibraryOptions {
  LibraryOptions(uint32_t sdl_flags, uint32_t img_flags, bool initialize_ttf) : m_SDLFlags(sdl_flags), m_SDLImageFlags(img_flags), m_InitializeTTF(initialize_ttf) {}
  LibraryOptions() : m_SDLFlags(0), m_SDLImageFlags(0), m_InitializeTTF(false) {}
  uint32_t m_SDLFlags;
  uint32_t m_SDLImageFlags;
  bool m_InitializeTTF;
};

 class STELLAR_INIT{
	private:
	details::init_library<details::SDL,uint32_t> m_SDL;
    details::init_library<details::SDL_Image,uint32_t> m_IMG;
	details::init_library<details::SDL_TTF> m_TTF;
    
	public:
	STELLAR_INIT(const LibraryOptions& lib_options) : m_SDL(lib_options.m_SDLFlags),
													  m_IMG(lib_options.m_SDLImageFlags)
	{
	  
	}

	~STELLAR_INIT(){
		
	}
	
	private:
 };

 
} // namespace Core
#endif // __BASE_HPP__