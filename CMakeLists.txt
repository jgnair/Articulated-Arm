cmake_minimum_required(VERSION 3.20)
project(Articulated_Arm)

set(CMAKE_CXX_STANDARD 14)

add_executable(Articulated_Arm main.cpp)
target_link_libraries(Articulated_Arm -lOpenGL32 -lfreeGLUT -lGLU32)
