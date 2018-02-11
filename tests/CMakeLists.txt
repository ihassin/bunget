cmake_minimum_required (VERSION 3.7.2)

set(CMAKE_COLOR_MAKEFILE   ON)

add_definitions(-DDEBUG)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fexceptions -Wall -fpermissive -ggdb")

set(HOME /home/pi)
set(ProjectsRoot ${HOME}/projects)

set(CutestRoot ${ProjectsRoot}/cutest)
set(CutestSource ${CutestRoot}/lib)
set(CutestBinary ${CutestRoot}/link)

set(BungetRoot ${ProjectsRoot}/bunget)
set(BungetSource ${BungetRoot}/lib)
set(BungetBinary ${BungetRoot}/link)

add_subdirectory(${CutestSource} ${CutestBinary} EXCLUDE_FROM_ALL)

link_directories(${CutestBinary})

file(GLOB SRC_FILES *.cpp *.h)
add_executable(cutest ${SRC_FILES})

target_link_libraries (cutest cutestLib bungetLib)

include_directories(${CutestSource})
include_directories(${BungetSource})

set(EXECUTABLE_OUTPUT_PATH ../bin)
