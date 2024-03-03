cmake_minimum_required(VERSION 3.23)
project(pianotiles C)

set(CMAKE_C_STANDARD 23)

add_executable(pianotiles main.c)
target_link_libraries(pianotiles -lmingw32 -lalleg44 -llibpng16 -llibloadpng -llibjpgalleg)
