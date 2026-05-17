#ifndef DA_SECOND_PROJECT_BASICALGORITHM_H
#define DA_SECOND_PROJECT_BASICALGORITHM_H

#include "ColoringAlgorithm.h"


/**
 * @brief Basic coloring algorithm, a greedy algorithm, which is not optimal.
 */
class BasicAlgorithm : public ColoringAlgorithm {
public:
    /** @brief This method essentially tries to find the minimum number of colors needed, iteratively
     * increasing the number of colors used until it finds a valid coloring or reaches the maximum number of colors
     * allowed. Internally uses runAlgorithm, which corresponds to the actual implementation of the basic coloring algorithm.
     * @param interferenceGraph The interference graph to color.
     * @param maxColors The maximum number of colors allowed for coloring the graph.
     * @return Returns true if the coloring was successful with the given number of colors, false otherwise.
     * @par Complexity:
     * Time: O(k(V^2 + VE)), where V is the number of vertices, E is the number of edges and k is the number of colors used until a valid coloring is found.
     */
    int execute(Graph &interferenceGraph, int maxColors) override;
private:
    /**
     * @brief Implementation of the basic coloring algorithm. It works as follows:
     * @details The internal algorithm (implemented in run algorithm) works as follows:
     * 1. While there are still active vertices in the graph:
     *   a. It looks for vertices with degree less than the current number of colors
     *   (which are essentially the vertices that can be colored with the current number of colors)
     *   b. if that vertex is still active, it's added to the stack and disabled (removed from the graph).
     *   c. If no vertex was removed in this iteration, it means that all remaining vertices are impossible the color
     *   according to the current color restriction so the algorithm returns false.
     * 2. In the coloring phase, while keeping track of the maximum color used:
     *   a. It pops vertices from the stack, re-enabling them in the graph and assigning them a color, that's not used
     *   by any of the existing neighbors.
     *   b. The assigned color is the minimum color that is not used by any of the neighbors.
     *   c. Updates the neighbor's neighbor colors to include the color assigned to the current vertex.
     * @param interferenceGraph
     * @param numColors
     * @return
     * @par Complexity:
     * Time: O(V^2 + VE), where V is the number of vertices and E is the number of edges
     */
    static bool runAlgorithm(Graph &interferenceGraph, int& numColors);
};

#endif //DA_SECOND_PROJECT_BASICALGORITHM_H
