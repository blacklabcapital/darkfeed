cmake_minimum_required(VERSION 3.4)
project(darkfeed)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
include(CTest)
include(ExternalProject)
include(CheckCXXCompilerFlag)
include(FindSSE)
if (SSE4_2_FOUND)
    add_definitions(-DHAS_SSE_4_2)
endif ()
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if (BUILD_DOCUMENTATION)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif ()

    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${doxyfile_in} ${doxyfile} @ONLY)

    add_custom_target(doc
            COMMAND ${DOXYGEN_EXECUTABLE} ${doxyfile}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)

    install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif ()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -march=native")
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
    set(${CMAKE_CXX_FLAGS} "${CMAKE_CXX_FLAGS} -xHost -ipo")
endif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG -Wall -O3 -g")

find_package(FlatBuffers REQUIRED)
find_package(ZLIB REQUIRED)
find_package(RE2 REQUIRED)
find_package(Gperftools REQUIRED)

#Install CCTZ
execute_process(COMMAND git submodule update --init -- external/cctz WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
ExternalProject_Add(cctz
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/cctz
    PREFIX ${CMAKE_BINARY_DIR}/external
    INSTALL_DIR ${CMAKE_BINARY_DIR}/external
    BUILD_IN_SOURCE 1
    CONFIGURE_COMMAND ""
    BUILD_COMMAND "make"
    INSTALL_COMMAND make install PREFIX=${CMAKE_BINARY_DIR}/external
)
include_directories(${CMAKE_SOURCE_DIR}/external/cctz/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
#Install xxHash
execute_process(COMMAND git submodule update --init -- external/xxHash WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(external/xxHash)
#Install SBE
execute_process(COMMAND git submodule update --init -- external/simple-binary-encoding ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/external/simple-binary-encoding/sbe-tool/src/main/cpp)

link_directories(/usr/local/lib)
link_directories(/usr/local/lib64)
link_directories(${CMAKE_BINARY_DIR}/external/lib)
include_directories(${CMAKE_BINARY_DIR}/external/include)

add_subdirectory(src)
if(BUILD_DOCS)
    add_subdirectory(doc)
endif(BUILD_DOCS)
if (BUILD_TESTING)
    add_definitions(-DGTEST_HAS_TR1_TUPLE=0)
    include_directories(${CMAKE_BINARY_DIR}/third_party/src/googletest/googletest/include)
    add_subdirectory(tests)
endif (BUILD_TESTING)
install(DIRECTORY include/ DESTINATION include)
