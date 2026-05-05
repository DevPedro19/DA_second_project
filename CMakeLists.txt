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
        include/CLI.h
        src/CLI.cpp
        include/TxtParser.h
        src/TxtParser.cpp
        include/ExecutionPlan.h
)

add_executable(test
        include/allocation.h
        src/test.cpp
        include/TxtParser.h
        src/TxtParser.cpp
        include/ExecutionPlan.h
)