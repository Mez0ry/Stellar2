cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(FindPackageHandleStandardArgs)

project(Stellar)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(OS_BITNESS 64)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(OS_BITNESS 32)
endif()

set(STELLAR_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build/lib/${OS_BITNESS}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${STELLAR_OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${STELLAR_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${STELLAR_OUTPUT_DIR}")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/SDL2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

find_package(spdlog REQUIRED)

include_directories(Stellar ${CMAKE_CURRENT_SOURCE_DIR}/include)
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


set(STELLAR_HEADERS
	include/GUI/Button.hpp
	include/AABB.hpp
	include/Action.hpp
	include/Angle.hpp
	include/Clickable.hpp
	include/Color.hpp
	include/Core.hpp
	include/Draggable.hpp
	include/Engine.hpp
	include/EventHandler.hpp
	include/KeyFrame.hpp
	include/Font.hpp
	include/GameScene.hpp
	include/Hoverable.hpp
	include/init_library.hpp
	include/KeyboardInput.hpp
	include/Literals.hpp
	include/Logger.hpp
	include/Matrix.hpp
	include/MouseInput.hpp
	include/ObjectSize.hpp
	include/Rect.hpp
	include/Renderer.hpp
	include/SceneManager.hpp
	include/SourceDestRect.hpp
	include/Surface.hpp
	include/Text.hpp
	include/Texture.hpp
	include/TextureGuard.hpp
	include/Timer.hpp
	include/Vector.hpp
	include/Window.hpp
	include/WindowInput.hpp
	include/Lerp.hpp
	include/Easing.hpp
)

set(STELLAR_SOURCES  
	src/AABB.cpp
	src/Engine.cpp
	src/EventHandler.cpp
	src/Font.cpp
	src/KeyboardInput.cpp
	src/Logger.cpp
	src/MouseInput.cpp
	src/Renderer.cpp
	src/SceneManager.cpp
	src/Surface.cpp
	src/Text.cpp
	src/Texture.cpp
	src/Timer.cpp
	src/Window.cpp
	src/WindowInput.cpp
	src/Lerp.cpp
	src/Easing.cpp
	src/KeyFrame.cpp
)

add_library(Stellar STATIC
    ${STELLAR_SOURCES} ${STELLAR_HEADERS}
)

target_link_libraries(Stellar ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SPDLOG_LIBRARIES})	