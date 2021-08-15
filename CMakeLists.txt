cmake_minimum_required(VERSION 3.13)
project(Caze VERSION 0.1)

include_directories(Caze-Core)
include_directories(Dependencies/vendor)

# file(GLOB libcz Caze-Core/cz.cpp)
file(GLOB_RECURSE lib_cxx Caze-Core/*.cpp)
file(GLOB_RECURSE lib_c Caze-Core/*.c)

set(source ${lib_cxx} ${lib_c})

find_library(glfwlib libglfw.so PATHS "./Dependencies/lib")

find_library(
	dllib
	NAMES dl-2.33
	HINTS "./Dependencies/lib"
)

add_library(cz SHARED ${source})
target_link_libraries(cz ${glfwlib})

add_executable(Caze "Caze-Sandbox/main.cpp")

target_link_libraries(Caze PUBLIC "cz")