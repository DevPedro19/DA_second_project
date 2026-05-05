cmake_minimum_required(VERSION 3.26)
project(DA_second_project)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(DA_second_project
        include/allocation.h
        src/main.cpp
        include/WebBuilder.h
        src/WebBuilder.cpp
        include/UFDS.h
        src/UFDS.cpp
)