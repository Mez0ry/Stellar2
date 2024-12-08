#ifndef __SURFACE_HPP__
#define __SURFACE_HPP__
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Logger.hpp"
#include "Core.hpp"
#include "SourceDestRect.hpp"

#include <string>

struct SurfaceDeleter {
  void operator()(SDL_Surface *surface) {
    if(surface != nullptr){
      SDL_FreeSurface(surface);
      surface = nullptr;
    }
  }
};

struct LockSurface{
private:
  SDL_Surface* m_Surface;
public:
  LockSurface() : m_Surface(nullptr){}
  LockSurface(SDL_Surface* surface) : m_Surface(surface){
    Lock(surface);
  }

  /**
   * @return true on success
   */
  bool Lock(SDL_Surface* surface){
    this->m_Surface = surface;

    if(SDL_MUSTLOCK(m_Surface)){
      if (SDL_LockSurface(m_Surface) < 0){
        return false;
      }
    }
    return true;
  }

  void Unlock(){
    if (SDL_MUSTLOCK(m_Surface)){ 
      SDL_UnlockSurface(m_Surface); 
    } 
  }

  ~LockSurface(){
    Unlock();
  }
};

class Surface : public SourceDestRect<Surface>{
public:
  Surface() noexcept;
  Surface(SDL_Surface* surface);
  Surface(const std::string& path);
  ~Surface() noexcept;
  
  Surface(const Surface &other) {
    m_Surface = other.m_Surface;
  }

  Surface(Surface &&other) noexcept {
   m_Surface = std::move(other.m_Surface);
   other.m_Surface = nullptr;
  }

  Surface& operator=(const Surface& other){
    ShareSDLSurface(other);
    return (*this);
  }
  
  Surface& operator=(Surface&& other){
    m_Surface = std::move(other.m_Surface);
    other.m_Surface = nullptr;
    return (*this);
  }
  
  Surface& operator=(SDL_Surface* other){
    m_Surface = SurfaceCreator(other).CreateSurface();
    return (*this);
  }

  /**
   * @brief loads surface with image
  */
  Core::Ref<SDL_Surface> LoadSurface(const std::string& image_path);
  
  void ShareSDLSurface(const Surface& surface);
  void ShareSDLSurface(const Core::Ref<SDL_Surface>& surface);

  SDL_Surface* GetSurface() const {return m_Surface.get();}
  SDL_Surface* GetSurface() {return m_Surface.get();}

  void Reset();

  explicit operator bool() const noexcept { return (m_Surface != nullptr); }

  operator SDL_Surface*() const noexcept{
    return m_Surface.get();
  }
public:

struct SurfaceCreator{
   SDL_Surface* m_Surface;
   std::string m_SurfacePath;
   SurfaceCreator(SDL_Surface* surf){
    m_Surface = surf;
   }

   SurfaceCreator(const std::string& path) : m_SurfacePath(path){
    m_Surface = IMG_Load(path.c_str());
   }
   
   bool IsValid() const {
    if(m_Surface == nullptr){
        if(m_SurfacePath.empty()){
          STELLAR_CORE_ERROR("Surface::SurfaceCreator::IsValid(), Error: parameter surface == nullptr, Failed at {0}:{1}",STELLAR_FILENAME,STELLAR_LINE);
        }else{
          STELLAR_CORE_ERROR("Surface::SurfaceCreator::IsValid(), Error: parameter surface == nullptr, surface image path {0}, Failed at {1}:{2}",m_SurfacePath,STELLAR_FILENAME,STELLAR_LINE);
        }
        return false;
    }
    return true;
   }
   
   Core::Ref<SDL_Surface> CreateSurface() const{
    if(IsValid()){
        return Core::Ref<SDL_Surface>(m_Surface,SurfaceDeleter());
    }
    return nullptr;
   }
};

private:
  Core::Ref<SDL_Surface> m_Surface;
};
#endif //! __SURFACE_HPP__