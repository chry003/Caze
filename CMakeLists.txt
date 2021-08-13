cmake_minimum_required(VERSION 3.13)
project(Caze VERSION 0.1)

include_directories(Caze-Core/src)
include_directories(Dependencies/vendor)

file(GLOB source_code Caze-Core/main.cpp)
file(GLOB_RECURSE classes_cxx Caze-Core/src/*.cpp)
file(GLOB_RECURSE classes_c Caze-Core/src/*.c)

set(source ${source_code} ${classes_cxx} ${classes_c})

add_executable(Caze ${source})

find_library(
	glfwlib
	NAMES glfw
	HINTS "./Dependencies/lib"
)

find_library(
	dllib
	NAMES dl-2.33
	HINTS "./Dependencies/lib"
)

find_library(
	gllib
	NAMES GL
	HINTS "./Dependencies/lib"
)

find_library(
	mlib
	NAMES m
	HINTS "./Dependencies/lib"
)

find_library(
	pthreadlib
	NAMES pthread-2.33
	HINTS "./Dependencies/lib"
)

find_library(
	X11lib
	NAMES X11
	HINTS "./Dependencies/lib"
)

find_library(
	Xilib
	NAMES Xi
	HINTS "./Dependencies/lib"
)

find_library(
	Xrandrlib
	NAMES Xrandr
	HINTS "./Dependencies/lib"
)

target_link_libraries(Caze ${glfwlib})
target_link_libraries(Caze ${dllib})
target_link_libraries(Caze ${gllib})
target_link_libraries(Caze ${mlib})
target_link_libraries(Caze ${pthreadlib})
target_link_libraries(Caze ${X11lib})
target_link_libraries(Caze ${Xilib})
target_link_libraries(Caze ${Xrandrlib})