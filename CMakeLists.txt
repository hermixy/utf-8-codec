cmake_minimum_required(VERSION 2.6)

project(Utf8Codec)

if (CMAKE_COMPILER_IS_GNUCC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wfatal-errors")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic")
elseif (MSVC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX")
endif (CMAKE_COMPILER_IS_GNUCC)

add_library("utf-8-codec" "utf-8-codec.c")

configure_file("Utf8CodecConfig.cmake.in"
	"Utf8CodecConfig.cmake" @ONLY)

install(TARGETS "utf-8-codec"
	EXPORT "Utf8CodecTargets"
	ARCHIVE DESTINATION "lib"
	LIBRARY DESTINATION "lib")

install(EXPORT "Utf8CodecTargets"
	DESTINATION "share/Utf8Codec/CMake")

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/Utf8CodecConfig.cmake"
	DESTINATION "share/Utf8Codec/CMake")

install(FILES "utf-8-codec.h"
	DESTINATION "include/utf-8-codec.h")

set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "A UTF-8 encoder and decoder library for C")
set (CPACK_PACKAGE_VENDOR "c-sweets")
set (CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set (CPACK_PACKAGE_VERSION_MAJOR ${GCOLLECTOR_VERSION_MAJOR})
set (CPACK_PACKAGE_VERSION_MINOR ${GCOLLECTOR_VERSION_MINOR})
set (CPACK_PACKAGE_VERSION_PATCH ${GCOLLECTOR_VERSION_PATCH})
set (CPACK_PACKAGE_CONTACT "taylorcholberton@gmail.com")

include(CPack)

enable_testing()

add_executable("utf-8-codec-test" "utf-8-codec-test.c")

target_link_libraries("utf-8-codec-test" "utf-8-codec")

add_test("utf-8-codec-test" "utf-8-codec-test")

find_package(Doxygen)
if (DOXYGEN_EXECUTABLE)
	add_custom_target("doc" ALL
		COMMAND ${DOXYGEN_EXECUTABLE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating doxygen files")
endif (DOXYGEN_EXECUTABLE)

