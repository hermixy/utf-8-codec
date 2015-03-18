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

add_library("utf-8-codec"
	"utf8-closed-intervals.h"
	"utf8-closed-intervals.c"
	"utf8-byte.h"
	"utf8-byte.c"
	"utf8-sequence.h"
	"utf8-sequence.c")

enable_testing()

add_executable("utf8-byte-test" "utf8-byte-test.c")

target_link_libraries("utf8-byte-test" "utf-8-codec")

add_test("utf8-byte-test" "utf8-byte-test")

add_executable("utf8-sequence-test" "utf8-sequence-test.c")

target_link_libraries("utf8-sequence-test" "utf-8-codec")

add_test("utf8-sequence-test" "utf8-sequence-test")

