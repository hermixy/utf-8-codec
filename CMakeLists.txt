cmake_minimum_required(VERSION 2.6)

project(Utf8String)

if (CMAKE_COMPILER_IS_GNUCC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror -Wfatal-errors")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ansi -pedantic")
elseif (MSVC)
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall")
	set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /WX")
endif (CMAKE_COMPILER_IS_GNUCC)

add_library("utf8-string"
	"utf8-point.c"
	"utf8-sequence.c"
	"utf8-string.c")

enable_testing()

add_executable("utf8-point-test" "utf8-point-test.c")

target_link_libraries("utf8-point-test" "utf8-string")

add_test("utf8-point-test" "utf8-point-test")

