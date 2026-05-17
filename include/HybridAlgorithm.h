#ifndef DA_SECOND_PROJECT_DSATURALGORITHM_H
#define DA_SECOND_PROJECT_DSATURALGORITHM_H

#include "ColoringAlgorithm.h"

/**
 * @brief Hybrid coloring algorithm, which combines multiple approaches to achieve better complexity.
 */
class HybridAlgorithm : public ColoringAlgorithm {
public:
    /**
     * @brief This method essentially tries to find the minimum number of colors needed,
     * iteratively increasing the number of colors used until it finds a valid coloring or
     * reaches the maximum number of colors allowed. Internally uses runAlgorithm,
     * which corresponds to the actual implementation of the hybrid coloring algorithm.
     * @param interferenceGraph The interference graph to color.
     * @param maxColors The maximum number of colors allowed for coloring the graph.
     * @return The number of colors used for coloring the graph, or 0 if it is not possible to color the graph with the given maximum number of colors.
     * @par Complexity:
     * Time: O(k(DSatur + V)), where V is the number of vertices, E is the number of edges.
     */
    int execute(Graph &interferenceGraph, int maxColors) override;
private:
    /**
     * @brief Implementation of one color coloring.
     * @details Iterates over all vertices of the graph and checks if they have any active edges.
     * In that case the graph cannot be colored with just one color, returning false.
     * If no vertex has active edges, the graph can be colored with just one color.
     * @param interferenceGraph The interference graph to check.
     * @return Returns true if the graph has no edges, false otherwise.
     * @par Complexity
     * Time: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
     */
    static bool graphHasNoEdges(const Graph &interferenceGraph);

    /**
     * @brief This function checks if the graph is bipartite, which means it can be colored with two colors.
     * @details The algorithm works as follows:
     * 1. It iterates over all vertices of the graph, if it finds an uncolored vertex, it starts a depth first search
     * (DFS) from that vertex, trying to color the graph with two colors.
     * 2. In the DFS, it tries to color the current vertex with a color different from its neighbors.
     * If it finds a neighbor with the same color, it means the graph is not bipartite and the algorithm returns false.
     * If it successfully colors the graph with two colors, it continues to check the next uncolored vertex until all
     * vertices are colored or a conflict is found.
     * @param interferenceGraph The interference graph to check.
     * @return Returns true if the graph is bipartite, false otherwise.
     * @par Complexity
     * Time: O(V + E), where V is the number of vertices and E is the number of edges in the graph.
     */
    static bool isGraphBipartite(const Graph &interferenceGraph);
    static bool dfsColoring(Vertex* vertex, int color);

    /**
    * @brief Comparison function for the priority queue used in the DSatur algorithm.
    * @details It defines the saturation degree criteria for selecting which vertex to color first. The criteria are as follows:
    * 1. Higher saturation degree: vertices with more different colors in their neighbors are more difficult to color, so they
    * are prioritized for coloring.
    * 2. Higher degree: if two vertices have the same saturation degree, the one with more neighbors is prioritized for coloring,
    * as it is likely to cause more conflicts if not colored.
    * @param v1 First vertex.
    * @param v2 Second vertex.
    * @return True if v1 should be colored before v2, false otherwise.
    * @par Complexity
    * Time: O(1) for the comparison
    */
    static bool DSaturComp(const Vertex& v1, const Vertex& v2);

    /**
     * @brief Implementation of the DSatur coloring algorithm. It works as follows:
     * 1. It creates a priority queue of the active vertices in the graph, ordered by the comparison function defined).
     * 2. Inserts all active vertices to the queue.
     * 3. While the queue is not empty:
     *  a. It extracts the hardest to color vertex.
     *  b. It finds the minimum color that is not used by its neighbors and assigns it to the vertex.
     *  c. It updates the neighbor colors of its neighbors and updates their position in the priority queue accordingly.
     * 4. It keeps track of the maximum color used, which is the number of colors needed to color the graph.
     * @param interferenceGraph The interference graph to color.
     * @param numColors The number of colors used to color the graph, which is updated by the algorithm.
     * @return Returns true if the graph was successfully colored with the number of colors used, false otherwise
     * (if the number of colors used exceeds the maximum number of colors allowed).
     * @par Complexity
     * Time: O(V logV + VE logV), where V is the number of vertices and E is the number of edges in the graph.
    */
    static bool DSatur(const Graph &interferenceGraph, int& numColors);

    /**
     * @brief Considering the number of colors allowed, it selects the best algorithm for that task.
     * @param interferenceGraph The interference graph to color.
     * @param numColors The number of colors allowed to color the graph. This variable is updated by the algorithm to
     * reflect the actual number of colors used to color the graph,
     * which can be less than the maximum number of colors allowed.
     * @return Returns true if the giraph was successfully colored with the number of colors used, false otherwise (if the number of colors used exceeds the maximum number of colors allowed).
     * @par Complexity
     * Time: in the worst case, it takes the same time as the DSatur algorithm.
     */
    static bool runAlgorithm(const Graph &interferenceGraph, int& numColors);
};

#endif //DA_SECOND_PROJECT_DSATURALGORITHM_H