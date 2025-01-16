cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(FindPackageHandleStandardArgs)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_is_supported OUTPUT error)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_BINARY_DIR}/conan_toolchain.cmake)
 
set(LibraryName Stellar)
project(${LibraryName})

set(OS_BITNESS 64)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(OS_BITNESS 32)
endif()

if(MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

	#target_compile_definitions("${LibraryName}" PUBLIC _CRT_SECURE_NO_WARNINGS)
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

include_directories(Stellar ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_image_INCLUDE_DIRS})
include_directories(${SDL2_ttf_INCLUDE_DIRS})
include_directories(${SDL2_mixer_INCLUDE_DIRS})
include_directories(${spdlog_INCLUDE_DIRS})
include_directories(${fmt_INCLUDE_DIRS})

file(GLOB_RECURSE PROJECT_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

file(GLOB_RECURSE PROJECT_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(Stellar STATIC
    ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES}
)

target_link_libraries(Stellar PUBLIC spdlog::spdlog SDL2::SDL2 SDL2_image::SDL2_image sdl_ttf::sdl_ttf SDL2_mixer::SDL2_mixer fmt)	