#ifndef DA_SECOND_PROJECT_SPILLINGALGORITHM_H
#define DA_SECOND_PROJECT_SPILLINGALGORITHM_H

#include "BasicAlgorithm.h"
#include "../data_structures/Graph.h"

/**
 * @brief Implementation of the spilling algorithm, which is a heuristic algorithm that tries to find the
 * best vertex (web) to spill (send to memory, reducing interference) and then colors the graph with the basic algorithm
 * @param interferenceGraph The interference graph to color.
 * @param maxWebsToSpill The maximum number of webs that can be spilled to memory.
 * @param numColors The number of colors allowed for coloring the graph.
 * @return The number of colors used for coloring the graph, or 0 if
 * it is not possible to color the graph with the given maximum number of colors after spilling the specified number of webs
 */
class SpillingAlgorithm {
public:
    /** @brief Constructor for the SpillingAlgorithm class, which takes a pointer to a ColoringAlgorithm as a parameter.
     * This allows the SpillingAlgorithm to use any coloring algorithm that implements the ColoringAlgorithm interface,
     * making it more flexible and reusable. */
    explicit SpillingAlgorithm(ColoringAlgorithm* coloring_algorithm);
    int execute(Graph &interferenceGraph, int maxWebsToSpill, int numColors);

private:
    static bool spillingComp(const Vertex& v1, const Vertex& v2);

    ColoringAlgorithm* coloring_algorithm;
};

#endif //DA_SECOND_PROJECT_SPILLINGALGORITHM_H
