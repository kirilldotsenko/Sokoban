cmake_minimum_required(VERSION 3.13)
set(CMAKE_CXX_STANDARD 11)


include_directories(/home/kirill/libtcod-1.5.1/include/)
link_directories(/home/kirill/libtcod-1.5.1/)


add_executable(untitled main.cpp GameFunctions.h cmake-build-debug/Board.h)


target_link_libraries(untitled -ltcod -ltcodxx)
