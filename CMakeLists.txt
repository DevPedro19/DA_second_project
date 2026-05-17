cmake_minimum_required(VERSION 3.26)
project(RegisterAllocation)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(RegisterAllocation
        include/allocation.h
        include/WebBuilder.h
        include/CLI.h
        include/TxtParser.h
        include/ExecutionPlan.h
        include/InfoMenu.h
        include/BasicAlgorithm.h
        include/HybridAlgorithm.h

        data_structures/UFDS.h
        data_structures/Graph.h

        src/main.cpp
        src/WebBuilder.cpp
        src/UFDS.cpp
        src/CLI.cpp
        src/InfoMenu.cpp
        src/TxtParser.cpp
        
        
        src/BasicAlgorithm.cpp
        include/OutputWriter.h
        src/OutputWriter.cpp
        include/SpillingAlgorithm.h
        src/SpillingAlgorithm.cpp
        include/AlgorithmAggregator.h
        src/AlgorithmAggregator.cpp
        include/SplittingAlgorithm.h
        src/SplittingAlgorithm.cpp
        src/HybridAlgorithm.cpp
        include/ColoringAlgorithm.h
)
# Output main.exe to the project root
set_target_properties(RegisterAllocation PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
