cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(FindPackageHandleStandardArgs)

project(Stellar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

find_package(spdlog REQUIRED)

include_directories(Stellar ${CMAKE_CURRENT_SOURCE_DIR}/Stellar)
include_directories(Stellar ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${SPDLOG_INCLUDE_DIRS})

if(SDL2_FOUND)
	message("SDL2 found")
endif()

if(SDL2_IMAGE_FOUND)
	message("SDL2_image found")
endif()

if(SDL2_TTF_FOUND)
	message("SDL2_ttf found")
endif()

if(SDL2_MIXER_FOUND)
	message("SDL2_mixer found")
endif()

if(spdlog_FOUND)
	message("sdplog found")
endif()
 
add_library(Stellar STATIC
    Stellar/GUI/Button.hpp
	Stellar/AABB.hpp
	Stellar/AABB.cpp
	Stellar/Action.hpp
	Stellar/Clickable.hpp
	Stellar/Color.hpp
	Stellar/Core.hpp
	Stellar/Draggable.hpp
	Stellar/KeyboardInput.cpp
	Stellar/KeyboardInput.hpp
	Stellar/EventHandler.hpp
	Stellar/EventHandler.cpp
	Stellar/Font.hpp
	Stellar/Font.cpp
	Stellar/Hoverable.hpp
	Stellar/init_library.hpp
	Stellar/Literals.hpp
	Stellar/Logger.hpp
	Stellar/Logger.cpp
	Stellar/MouseInput.hpp
	Stellar/MouseInput.cpp
	Stellar/ObjectSize.hpp
	Stellar/Rect.hpp
	Stellar/Renderer.hpp
	Stellar/Renderer.cpp
	Stellar/ServiceLocator.hpp
	Stellar/SourceDestRect.hpp
	Stellar/Surface.hpp
	Stellar/Surface.cpp
	Stellar/Text.hpp
	Stellar/Text.cpp
	Stellar/Texture.hpp
	Stellar/Texture.cpp
	Stellar/TextureGuard.hpp
	Stellar/Timer.hpp
	Stellar/Timer.cpp
	Stellar/Timestep.hpp
	Stellar/Vector.hpp
	Stellar/Window.hpp
	Stellar/Window.cpp
	Stellar/WindowInput.hpp
	Stellar/WindowInput.cpp
)

target_include_directories(Stellar PUBLIC ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SPDLOG_LIBRARIES})

target_link_libraries(Stellar SDL2::Main SDL2::Image SDL2::TTF SDL2::Mixer spdlog fmt)