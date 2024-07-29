
set(SPDLOG_PATH "" CACHE STRING "Custom spdlog Library path")

set(_SPDLOG_NO_DEFAULT_PATH OFF)
if(SPDLOG_PATH)
  set(_SPDLOG_NO_DEFAULT_PATH ON)
endif()

set(SPDLOG_NO_DEFAULT_PATH ${_SPDLOG_NO_DEFAULT_PATH}
    CACHE BOOL "Disable search sdplog Library in default path")
unset(_SPDLOG_NO_DEFAULT_PATH)

set(SPDLOG_NO_DEFAULT_PATH_CMD)
if(SPDLOG_NO_DEFAULT_PATH)
  set(SPDLOG_NO_DEFAULT_PATH_CMD NO_DEFAULT_PATH)
endif()

find_path(SPDLOG_INCLUDE_DIR spdlog.h
  HINTS
    ENV SPDLOG_ROOT
    ENV SPDLOG_INCLUDE_DIR
  PATHS
    ${SPDLOG_ROOT}
    /usr
    /usr/local
    $ENV{HOME}/.local
    ../vendor
    ${SPDLOG_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES spdlog
                include/spdlog include
  PATHS ${SPDLOG_PATH}
  DOC "Where the spdlog headers can be found"
)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
  set(VC_LIB_PATH_SUFFIX lib/x64)
else()
  set(VC_LIB_PATH_SUFFIX lib/x86)
endif()

find_library(SPDLOG_LIBRARY
  NAMES spdlog
  HINTS
    ENV SPDLOG_ROOT
    ENV SPDLOG_INCLUDE_DIR
    ${SPDLOG_NO_DEFAULT_PATH_CMD}
  PATH_SUFFIXES lib ${VC_LIB_PATH_SUFFIX}
  PATHS ${SPDLOG_PATH}
  DOC "Where the spdlog Library can be found"
)

if(SPDLOG_INCLUDE_DIR AND EXISTS "${SPDLOG_INCLUDE_DIR}/spdlog.h")
  file(STRINGS "${SPDLOG_INCLUDE_DIR}/spdlog.h" SPDLOG_VERSION_MAJOR_LINE REGEX "^#define[ \t]+SPDLOG_VERSION_MAJOR[ \t]+[0-9]+$")
  file(STRINGS "${SPDLOG_INCLUDE_DIR}/spdlog.h" SPDLOG_VERSION_MINOR_LINE REGEX "^#define[ \t]+SPDLOG_VERSION_MINOR[ \t]+[0-9]+$")
  
  string(REGEX REPLACE "^#define[ \t]+SPDLOG_MAJOR_VERSION[ \t]+([0-9]+)$" "\\1" SPDLOG_VERSION_MAJOR "${SPDLOG_VERSION_MAJOR_LINE}")
  string(REGEX REPLACE "^#define[ \t]+SPDLOG_MINOR_VERSION[ \t]+([0-9]+)$" "\\1" SPDLOG_VERSION_MINOR "${SPDLOG_VERSION_MINOR_LINE}")
  
  set(SPDLOG_VERSION_STRING ${SPDLOG_VERSION_MAJOR}.${SPDLOG_VERSION_MINOR})
  
  unset(SPDLOG_VERSION_MAJOR_LINE)
  unset(SPDLOG_VERSION_MINOR_LINE)
  unset(SPDLOG_VERSION_MAJOR)
  unset(SPDLOG_VERSION_MINOR)

endif()

set(SPDLOG_LIBRARIES ${SPDLOG_LIBRARY})
set(SPDLOG_INCLUDE_DIRS ${SPDLOG_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(spdlog
                                  REQUIRED_VARS SPDLOG_LIBRARIES SPDLOG_INCLUDE_DIRS
                                  VERSION_VAR SPDLOG_VERSION_STRING)


mark_as_advanced(SPDLOG_PATH
                 _SPDLOG_NO_DEFAULT_PATH
                 SPDLOG_LIBRARY
                 SPDLOG_INCLUDE_DIR)


if(spdlog_TTF_FOUND)
  # spdlog::spdlog target
  if(SPDLOG_LIBRARY AND NOT TARGET spdlog::spdlog)
    add_library(spdlog::spdlog UNKNOWN IMPORTED)
    set_target_properties(spdlog::spdlog PROPERTIES
                          IMPORTED_LOCATION "${SPDLOG_LIBRARY}"
                          INTERFACE_INCLUDE_DIRECTORIES "${SPDLOG_INCLUDE_DIR}"
                          INTERFACE_LINK_LIBRARIES spdlog::Core)
  endif()
endif()
