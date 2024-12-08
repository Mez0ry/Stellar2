#include "Engine.hpp"
#include "init_library.hpp"
#include "Core.hpp"

bool Engine::Initialize(uint32_t sdl2_flags, uint32_t sdl_img_flags, bool initialize_sdl_ttf)
{
    auto& context = instance();

    if(sdl2_flags != 0){
      hash_code_t sdl_hash = context.GetHashCode<details::SDL>();
      context.m_Libraries.insert(std::make_pair(sdl_hash,Core::CreateRef<details::init_library<details::SDL,uint32_t>>(sdl2_flags)));
    }

    if(sdl2_flags == 0 && (sdl_img_flags != 0 || initialize_sdl_ttf)){
        STELLAR_CORE_CRITICAL("some other library can't be initialized before SDL2");
        return false;
    }

    if(sdl_img_flags != 0){
        
        hash_code_t sdl_img_hash = context.GetHashCode<details::SDL_Image>();
        context.m_Libraries.insert(std::make_pair(sdl_img_hash,Core::CreateRef<details::init_library<details::SDL_Image,uint32_t>>(sdl_img_flags)));
    }
    
    if(initialize_sdl_ttf){
       hash_code_t sdl_ttf_hash = context.GetHashCode<details::SDL_TTF>();
       context.m_Libraries.insert(std::make_pair(sdl_ttf_hash,Core::CreateRef<details::init_library<details::SDL_TTF>>()));
    }

    return true;
}
