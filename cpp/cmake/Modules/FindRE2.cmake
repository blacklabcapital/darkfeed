find_path(RE2_INCLUDE_DIR re2/re2.h NO_DEFAULT_PATH PATHS
  /usr/include
  /opt/local/include
  /usr/local/include
)

set(RE2_NAMES ${RE2_NAMES} re2)
find_library(RE2_LIBRARY NAMES ${RE2_NAMES} NO_DEFAULT_PATH PATHS
  /usr/local/lib
  /usr/local/re2/lib
  /opt/local/lib
  /usr/lib
)

if (RE2_INCLUDE_DIR AND RE2_LIBRARY)
  set(RE2_FOUND TRUE)
  set( RE2_LIBRARIES ${RE2_LIBRARY} )
else ()
  set(RE2_FOUND FALSE)
  set( RE2_LIBRARIES )
endif ()

if (RE2_FOUND)
  message(STATUS "Found RE2: ${RE2_LIBRARY}")
else ()
  message(STATUS "Not Found RE2: ${RE2_LIBRARY}")
  if (RE2_FIND_REQUIRED)
    message(STATUS "Looked for RE2 libraries named ${RE2_NAMES}.")
    message(FATAL_ERROR "Could NOT find RE2 library")
  endif ()
endif ()

mark_as_advanced(
  RE2_LIBRARY
  RE2_INCLUDE_DIR
)
