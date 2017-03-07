INCLUDE(ExternalProject)

# Set default ExternalProject root directory
SET_DIRECTORY_PROPERTIES(PROPERTIES EP_PREFIX ${CMAKE_BINARY_DIR}/third_party)

# Add gtest
# http://stackoverflow.com/questions/9689183/cmake-googletest
ExternalProject_Add(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        INSTALL_COMMAND ""
        LOG_DOWNLOAD ON
        LOG_CONFIGURE ON
        LOG_BUILD ON)

# Specify include dir
ExternalProject_Get_Property(googletest source_dir)
set(GTEST_INCLUDE_DIRS ${CMAKE_BINARY_DIR}/third_party/googletest/googletest/include)

# Library
ExternalProject_Get_Property(googletest binary_dir)
set(GTEST_LIBRARY_PATH ${binary_dir}/googlemock/gtest/libgtest.a)
set(GTEST_LIBRARY gtest)
add_library(${GTEST_LIBRARY} UNKNOWN IMPORTED)
set_property(TARGET ${GTEST_LIBRARY} PROPERTY IMPORTED_LOCATION
        ${GTEST_LIBRARY_PATH})
add_dependencies(${GTEST_LIBRARY} googletest)

set(
        DARKFEED_TEST_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/exchanges_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/quotes_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/hashing_test.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/states_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/timestamp_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/trades_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/symbols_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/price_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/flatbuffers_serializer_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/sbe_serializer_test.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_main.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/halts_test.cpp
)

set(XXHASH_SRCS ${CMAKE_SOURCE_DIR}/external/xxHash/xxhash.c)
set(CCTZ_SRCS
        ${CMAKE_SOURCE_DIR}/external/cctz/src/time_zone_format.cc
        ${CMAKE_SOURCE_DIR}/external/cctz/src/time_zone_if.cc
        ${CMAKE_SOURCE_DIR}/external/cctz/src/time_zone_impl.cc
        ${CMAKE_SOURCE_DIR}/external/cctz/src/time_zone_info.cc
        ${CMAKE_SOURCE_DIR}/external/cctz/src/time_zone_libc.cc
        ${CMAKE_SOURCE_DIR}/external/cctz/src/time_zone_lookup.cc
        ${CMAKE_SOURCE_DIR}/external/cctz/src/time_zone_posix.cc
        )

add_executable(unit_tests ${DARKFEED_TEST_SRCS} ${DARKFEED_SRCS} ${XXHASH_SRCS} ${CCTZ_SRCS})
target_include_directories(unit_tests PRIVATE ${FLATBUFFERS_INCLUDE_DIR} ${GTEST_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(unit_tests z re2 ${GTEST_LIBRARY} pthread)
add_test(unittests unit_tests)
