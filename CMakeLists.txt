cmake_minimum_required(VERSION 3.10)
project(makeui)

set(CMAKE_CXX_STANDARD 11)

include_directories("C:/msys64/mingw64/include/ncursesw")
link_directories("C:/msys64/mingw64/lib")

add_executable(makeui main.c)
target_link_libraries(makeui ncursesw)
