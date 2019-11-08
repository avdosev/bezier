cmake_minimum_required(VERSION 3.15)
project(bezier)

set(CMAKE_CXX_STANDARD 17)

add_executable(bezier main.cpp
        computational_geometry/matrix.h
        computational_geometry/vec.h
        computational_geometry/computational_geometry.cpp
        computational_geometry/computational_geometry.h
        )