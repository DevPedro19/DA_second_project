#ifndef DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H
#define DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H

#include "BasicAlgorithm.h"
#include "SpillingAlgorithm.h"
#include "SplittingAlgorithm.h"

/**
 * @brief Class that aggregates all algorithms, acting as a unified wrapper for register allocation strategies on an interference graph.
 * @details his class provides a single entry point for executing the three register allocation algorithms: basic, spilling and splitting. Each algorithm attempts to color the interference graph with at most `numColor`. If the graph cannot be colored, the spilling and splitting algorithms will apply heuristics to reduce the number of registers needed.
 */
class AlgorithmAggregator {
public:
    /**
     * @brief Default constructor. Initializes all internal algorithm instances.
     */
    AlgorithmAggregator();

    /**
     * @brief Runs the basic graph coloring algorithm on the given interference graph.
     * @param interferenceGraph The interference graph to be colored.
     * @param numColors The number of available registers (colors). This parameter here is passed by reference because the basic algorithm may modify it if it runs the DSatur algorithm, which finds the minimum colors needed to color the graph.
     * @return The number of registers (colors) used to color the graph, if the value is 0 it means it couldn't color it.
     */
    int runBasicAlgorithm(Graph& interferenceGraph, int& numColors) const;

    /**
     * @brief Runs the spilling algorithm on the given interference graph. This algorithm attempts to spill up to `maxRegsToSpill` registers in order to reduce the number of colors needed to color the graph.
     * @param interferenceGraph The interference graph to be colored.
     * @param maxRegsToSpill The maximum number of registers (vertices) that can be spilled (disabled).
     * @param numColors The number of available registers (colors).
     * @return The number of registers (colors) used. If the value is 0 it means it still couldn't color it.
     */
    int runSpillingAlgorithm(Graph &interferenceGraph, int maxRegsToSpill, int numColors);

    /**
     * @brief Runs the splitting algorithm on the given interference graph. This algorithm attempts to split up to `maxWebsToSplit` webs (vertices) in order to reduce the number of colors needed to color the graph.
     * @param interferenceGraph The interference graph to be colored.
     * @param maxWebsToSplit The maximum number of webs that can be split.
     * @param numColors The number of available registers (colors).
     * @return The number of registers (colors) used. If the value is 0 it means it still couldn't color it.
     */
    int runSplittingAlgorithm(Graph &interferenceGraph, int maxWebsToSplit, int numColors);

private:
    /**
     * @brief Instance of the basic coloring algorithm.
     */
    BasicAlgorithm basicAlgorithm;

    /**
     * @brief Instance of the spilling algorithm.
     */
    SpillingAlgorithm spillingAlgorithm;

    /**
     * @brief Instance of the splitting algorithm.
     */
    SplittingAlgorithm splittingAlgorithm;
};

#endif //DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H
