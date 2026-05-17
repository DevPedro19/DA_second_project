#ifndef DA_SECOND_PROJECT_BASICALGORITHM_H
#define DA_SECOND_PROJECT_BASICALGORITHM_H

#include "ColoringAlgorithm.h"


/** @brief Basic coloring algorithm, a greedy algorithm, which is not optimal. */
class BasicAlgorithm : public ColoringAlgorithm {
public:
    /**
     * This method essentially tries to find the minimum number of colors needed, iteratively
     * increasing the number of colors used until it finds a valid coloring or reaches the maximum number of colors
     * allowed. Internally uses runAlgorithm, which corresponds to the actual implementation of the basic coloring algorithm.
     * @param interferenceGraph The interference graph to color.
     * @param maxColors The maximum number of colors allowed for coloring the graph.
     * @return The number of colors used for coloring the graph, or 0 if it is not possible to color the graph with the given maximum number of colors.
     */
    int execute(Graph &interferenceGraph, int maxColors) override;
private:
    static bool runAlgorithm(Graph &interferenceGraph, int& numColors);
};

#endif //DA_SECOND_PROJECT_BASICALGORITHM_H
