cmake_minimum_required(VERSION 3.26)
project(DA_second_project)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(DA_second_project
        include/allocation.h
        include/WebBuilder.h
        include/CLI.h
        include/TxtParser.h
        include/ExecutionPlan.h
        include/InfoMenu.h

        data_structures/UFDS.h
        data_structures/Graph.h

        src/main.cpp
        src/WebBuilder.cpp
        src/UFDS.cpp
        src/CLI.cpp
        src/InfoMenu.cpp
        src/TxtParser.cpp
)
