set(DARKFEED_SRCS
        ${CMAKE_CURRENT_SOURCE_DIR}/types/exchanges.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/types/quotes.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/types/event.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/types/halts.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/states.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/locks.cpp
        #${CMAKE_CURRENT_SOURCE_DIR}/state_utils.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/types/timestamp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/types/trades.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/types/symbol.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/types/price.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/util/hashing.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/util/hashing/crc32c/crc32ctable.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/util/hashing/crc32c/crc32ctables.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/util/hashing/crc32c/crc32cintel.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/util/hashing/crc32c/crc32cintel_table.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/serialization/flatbuffers_serializer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/serialization/sbe_serializer.cpp
)
set(DARKFEED_SRCS ${DARKFEED_SRCS} PARENT_SCOPE)
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
add_library(darkfeed_shared SHARED ${DARKFEED_SRCS} ${CCTZ_SRCS} ${XXHASH_SRCS})
add_library(darkfeed_static STATIC ${DARKFEED_SRCS} ${CCTZ_SRCS} ${XXHASH_SRCS})
target_include_directories(darkfeed_static PRIVATE ${CMAKE_SOURCE_DIR}/external/cctz/include)
target_include_directories(darkfeed_shared PRIVATE ${CMAKE_SOURCE_DIR}/external/cctz/include)
set_target_properties(darkfeed_static PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(darkfeed_static PROPERTIES OUTPUT_NAME mfeed)
set_target_properties(darkfeed_static PROPERTIES OUTPUT_NAME mfeed)
target_link_libraries(darkfeed_shared z tcmalloc_minimal re2)
target_link_libraries(darkfeed_static tcmalloc_minimal re2)
install(
        TARGETS darkfeed_shared
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
install(
        TARGETS darkfeed_static
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
