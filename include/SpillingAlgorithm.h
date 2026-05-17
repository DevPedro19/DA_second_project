#ifndef DA_SECOND_PROJECT_SPILLINGALGORITHM_H
#define DA_SECOND_PROJECT_SPILLINGALGORITHM_H

#include "BasicAlgorithm.h"
#include "../data_structures/Graph.h"

/**
 * @brief Class that represents the Spilling algorithm.
 * @details The spilling algorithm is used when the graph cannot be colored with the given `numColors` from the execution plan. It will deactivate nodes from the graph in order to reduce the number of registers (colors) needed.
 */
class SpillingAlgorithm {
public:
    /**
     * @brief Constructs the Spilling algorithm using a `basicAlgorithm` instance.
     * @param coloring_algorithm The coloring algorithm instance. It is used to see if the splitting was effective in reducing the number of colors needed to color the graph, it tests if the spilled graph is colorable with `numColors` colors.
     */
    explicit SpillingAlgorithm(ColoringAlgorithm* coloring_algorithm);

    /**
     * @brief The main spilling algorithm.
     * @details The algorithm works as follows:
     * 1. It creates a priority queue of the active vertices in the graph, ordered by the spilling criteria the `spilling comp` function. The queue helps to select the best vertice (web) to be spilled.
     * 2. Inserts all active vertices to the queue.
     * 3. Iterates from 1 to the `maxRegsToSpill` parameter, in each iteration it:
     *   a. Extracts the vertex with the highest priority (the one that is the best candidate for spilling) from the queue and disables it in the graph (spills it).
     *   b. Updates the priority queue for the neighbors of the spilled vertex, since their degree and neighbor degree sum may have changed.
     *   c. Executes the basic algorithm on the modified graph to check if it can be colored with `numColors` colors. If it can, it returns the number of colors used. If it cannot, it continues to the next iteration to spill another vertex.
     * 4. If after spilling up to `maxRegsToSpill` vertices the graph still cannot be colored with `numColors` colors, it returns 0 to indicate failure.
     * @param interferenceGraph The interference graph to be spilled and colored.
     * @param maxWebsToSpill The maximum number of vertices (webs) that can be disabled (spilled).
     * @param numColors The maximum number of colors (registers) the graph can be colored.
     * @return The number of registers the graph can be colored. If 0 it means the graph still cannot be colored.
     * @par Complexity:
     * Time: O(s * ColoringAlgorithmComplexity) where s is the number of vertices spilled until a valid coloring is
     * found (or until `maxWebsToSpill` is reached) and ColoringAlgorithmComplexity is the complexity of the coloring
     * algorithm used.
     */
    int execute(Graph& interferenceGraph, int maxWebsToSpill, int numColors) const;

private:
    /**
     * @brief Comparison function for the priority queue used in the spilling algorithm.
     * @details It defines the spilling criteria for selecting which vertex to spill first. The criteria are as follows:
     * 1. Higher degree: vertices with more neighbors are more difficult to color, so they are prioritized for spilling.
     * 2. Higher neighbor degree sum: if two vertices have the same degree, the one whose neighbors have a higher total degree is prioritized for spilling, as it is likely to cause more conflicts if not spilled.
     * 3. Shorter live range: if two vertices have the same degree and the same neighbor degree sum, the one with the shorter live range is prioritized since it as the least number of accesses, and therefore the least number of reads/writes associated, so it is more likely to be beneficial to spill it.
     * @param v1 First vertex.
     * @param v2 Second vertex.
     * @return True if v1 should be spilled before v2, false otherwise.
     * @par Complexity:
     * Time: O(E), where E is the number of edges in the graph.
     */
    static bool spillingComp(const Vertex& v1, const Vertex& v2);

    /**
     * @brief Instance of the coloring algorithm.
     */
    ColoringAlgorithm* coloring_algorithm;
};

#endif //DA_SECOND_PROJECT_SPILLINGALGORITHM_H
