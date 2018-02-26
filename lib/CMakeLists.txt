##
##    Copyright: O-Marius Chincisan 2016-2017 Zirexix Inc
##
##    This program is distributed
##    WITHOUT ANY WARRANTY; without even the implied warranty of
##    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
##
##    This program, or portions of it cannot be used in commercial
##    products without the written consent of the author.
##
##
cmake_minimum_required (VERSION 2.6)

include_directories ("./include")

add_definitions(-DDEBUG)
add_definitions(-DACL_MTU_FRAG)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -ggdb -Wall")
set(LIBRARY_OUTPUT_PATH ../link)

file(GLOB SRC_FILES *.cpp *.h)
add_library(bungetLib ${SRC_FILES})
