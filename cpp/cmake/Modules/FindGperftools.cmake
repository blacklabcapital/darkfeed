find_library(GPERFTOOLS_TCMALLOC
  NAMES tcmalloc
  HINTS ${Gperftools_ROOT_DIR}/lib)

find_library(GPERFTOOLS_PROFILER
  NAMES profiler
  HINTS ${Gperftools_ROOT_DIR}/lib)

find_library(GPERFTOOLS_TCMALLOC_AND_PROFILER
  NAMES tcmalloc_and_profiler
  HINTS ${Gperftools_ROOT_DIR}/lib)

find_path(GPERFTOOLS_INCLUDE_DIR
  NAMES gperftools/heap-profiler.h
  HINTS ${Gperftools_ROOT_DIR}/include)

set(GPERFTOOLS_LIBRARIES ${GPERFTOOLS_TCMALLOC_AND_PROFILER})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(
  Gperftools
  DEFAULT_MSG
  GPERFTOOLS_LIBRARIES
  GPERFTOOLS_INCLUDE_DIR)

mark_as_advanced(
  Gperftools_ROOT_DIR
  GPERFTOOLS_TCMALLOC
  GPERFTOOLS_PROFILER
  GPERFTOOLS_TCMALLOC_AND_PROFILER
  GPERFTOOLS_LIBRARIES
GPERFTOOLS_INCLUDE_DIR)
