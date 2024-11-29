cmake_minimum_required(VERSION 3.29)
project(CubeRotation C)

set(CMAKE_C_STANDARD 11)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(/opt/homebrew/include)


add_executable(CubeRotation
        Cube.c)

target_link_libraries(CubeRotation OpenGL::GL GLUT::GLUT)
