#ifndef DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H
#define DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H

#include "BasicAlgorithm.h"
#include "HybridAlgorithm.h"
#include "SpillingAlgorithm.h"
#include "SplittingAlgorithm.h"

/**
 * @brief Unified interface for running different variations of register allocation algorithms
 */
class AlgorithmAggregator {
public:
    AlgorithmAggregator();
    /**
     * @brief Runs the basic algorithm (essentially Chaitin's algorithm) on the given interference graph
     * @param interferenceGraph The graph representing variable interferences
     * @param numColors The number of available registers (colors)
     * @return The number of colors used after allocation
     */
    int runBasicAlgorithm(Graph& interferenceGraph, int& numColors);

    /**
     * @brief Runs the basic algorithm and spills registers to memory, if needed, on the given interference graph
     * @param interferenceGraph The graph representing variable interferences
     * @param maxRegsToSpill The maximum number of registers that can be spilled to memory
     * @param numColors The number of available registers (colors)
     * @return The number of colors used after allocation
     */
    int runSpillingAlgorithm(Graph &interferenceGraph, int maxRegsToSpill, int numColors);

    /**
     * @brief Runs the basic algorithm and splits live ranges, if needed, on the given interference graph
     * @param interferenceGraph The graph representing variable interferences
     * @param maxWebsToSplit The maximum number of live ranges (webs) that can be split
     * @param numColors The number of available registers (colors)
     * @return The number of colors used after allocation
     */
    int runSplittingAlgorithm(Graph &interferenceGraph, int maxWebsToSplit, int numColors);

    /**
     * @brief Runs a splitting algorithm that internally uses the hybrid algorithm for coloring, on the given interference graph
     * @param interferenceGraph The graph representing variable interferences
     * @param numColors The number of available registers (colors)
     * @param maxWebsToSplit The maximum number of live ranges (webs) that can be split
     * @return The number of colors used after allocation
     */
    int runFreeAlgorithm(Graph &interferenceGraph, int numColors, int maxWebsToSplit);

private:
    // Both are initialized with their default constructors
    BasicAlgorithm basicAlgorithm;
    HybridAlgorithm hybridAlgorithm;

    // Spilling and splitting algorithms internally have a coloring algorithm (in this case can be basic or hybrid)
    SpillingAlgorithm spillingAlgorithm;
    SplittingAlgorithm splittingAlgorithm;
    SplittingAlgorithm freeAlgorithm; // Our free algorithm is essentially a splitting algorithm
};

#endif //DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H