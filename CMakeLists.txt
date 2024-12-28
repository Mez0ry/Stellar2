cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

include(FindPackageHandleStandardArgs)
include(CheckIPOSupported)
check_ipo_supported(RESULT ipo_is_supported OUTPUT error)

set(LibraryName Stellar)
project(${LibraryName})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(OS_BITNESS 64)

if(CMAKE_SIZEOF_VOID_P EQUAL 4)
	set(OS_BITNESS 32)
endif()

if(MSVC)
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Release>:Release>")
	set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

	target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC _CRT_SECURE_NO_WARNINGS)
	set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")  
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

file(GLOB_RECURSE PROJECT_HEADER_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")

file(GLOB_RECURSE PROJECT_SOURCE_FILES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_library(Stellar STATIC
    ${PROJECT_SOURCE_FILES} ${PROJECT_HEADER_FILES}
)

target_link_libraries(Stellar ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} ${SDL2_TTF_LIBRARIES} ${SDL2_MIXER_LIBRARIES} ${SPDLOG_LIBRARIES})	