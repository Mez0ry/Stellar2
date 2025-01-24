cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(FindPackageHandleStandardArgs)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_is_supported OUTPUT error)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/generators/conan_toolchain.cmake)

set(LibraryName Stellar)
project(${LibraryName})

option(BUILD_USING_EXTERNAL_SDL2 "Build using external SDL2" OFF)
option(BUILD_USING_EXTERNAL_SDL2_image "Build using external SDL2 image" OFF)
option(BUILD_USING_EXTERNAL_SDL2_ttf "Build using external SDL2 ttf" OFF)
option(BUILD_USING_EXTERNAL_SDL2_mixer "Build using external SDL2 mixer" OFF)
option(BUILD_USING_EXTERNAL_SPDLOG "Build using external spdlog" OFF)
option(BUILD_ALL_EXTERNALLY "Build every 3rd party libs using external copies" OFF)

set(OS_BITNESS 64)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(OS_BITNESS 32)
endif()

if(MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
	add_definitions(-D_CRT_SECURE_NO_WARNINGS)
	#set_target_properties("${LibraryName}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

set(STELLAR_OUTPUT_DIR "${CMAKE_SOURCE_DIR}/build/lib/${OS_BITNESS}/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${STELLAR_OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${STELLAR_OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${STELLAR_OUTPUT_DIR}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/build/generators")
list(APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_LIST_DIR}/build/generators")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

include_directories(${LibraryName} ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${LibraryName} ${SDL2_INCLUDE_DIRS})
include_directories(${LibraryName} ${SDL2_image_INCLUDE_DIRS})
include_directories(${LibraryName} ${SDL2_ttf_INCLUDE_DIRS})
include_directories(${LibraryName} ${SDL2_mixer_INCLUDE_DIRS})
include_directories(${LibraryName} ${spdlog_INCLUDE_DIRS})
include_directories(${LibraryName} ${fmt_INCLUDE_DIRS})

file(GLOB_RECURSE PROJECT_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

file(GLOB_RECURSE PROJECT_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(${LibraryName} STATIC
    ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES}
)

target_link_libraries(${LibraryName}  ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SPDLOG_LIBRARIES})	

if(BUILD_USING_EXTERNAL_SDL2 OR BUILD_ALL_EXTERNALLY)
	target_link_libraries(${LibraryName} ${SDL2_LIBRARIES})
else()
	target_link_libraries(${LibraryName} SDL2::SDL2)
endif()

if(BUILD_USING_EXTERNAL_SDL2_image OR BUILD_ALL_EXTERNALLY)
	target_link_libraries(${LibraryName} ${SDL2_IMAGE_LIBRARIES})
else()
	target_link_libraries(${LibraryName} SDL2_image::SDL2_image)
endif()

if(BUILD_USING_EXTERNAL_SDL2_ttf OR BUILD_ALL_EXTERNALLY)
	target_link_libraries(${LibraryName} ${SDL2_TTF_LIBRARIES})
else()
	target_link_libraries(${LibraryName} sdl_ttf::sdl_ttf)
endif()

if(BUILD_USING_EXTERNAL_SDL2_mixer OR BUILD_ALL_EXTERNALLY) 
	target_link_libraries(${LibraryName} ${SDL2_MIXER_LIBRARIES})
else()
	target_link_libraries(${LibraryName} SDL2_mixer::SDL2_mixer)
endif()

if(BUILD_USING_EXTERNAL_SPDLOG OR BUILD_ALL_EXTERNALLY)
	target_link_libraries(${LibraryName} ${SPDLOG_LIBRARIES})
else()
	target_link_libraries(${LibraryName} spdlog::spdlog fmt::fmt)
endif()