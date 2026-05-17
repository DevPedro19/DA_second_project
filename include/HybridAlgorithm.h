#ifndef DA_SECOND_PROJECT_DSATURALGORITHM_H
#define DA_SECOND_PROJECT_DSATURALGORITHM_H

#include "ColoringAlgorithm.h"

/**
 * @brief Hybrid coloring algorithm, which combines multiple approaches to achieve better complexity.
 * @param interferenceGraph The interference graph to color.
 * @param maxColors The maximum number of colors allowed for coloring the graph.
 * @return The number of colors used for coloring the graph, or 0 if it is not possible to color the graph with the given maximum number of colors.
 */
class HybridAlgorithm : public ColoringAlgorithm {
public:
    /**
     * @brief This method first checks if the graph has no edges,
     * in which case it can be colored with just one color.
     * Then it checks if the graph is bipartite, in which case it can be colored with two colors.
     * Finally, if three or more colors are needed, it uses the DSatur algorithm to find a valid coloring.
     * @param interferenceGraph The interference graph to color.
     * @param maxColors The maximum number of colors allowed for coloring the graph.
     * @return The number of colors used for coloring the graph, or 0 if it is not possible to color the graph with the given maximum number of colors.
     */
    int execute(Graph &interferenceGraph, int maxColors) override;
private:
    // Helper methods for the different steps of the algorithm
    static bool graphHasNoEdges(const Graph &interferenceGraph);
    static bool isGraphBipartite(const Graph &interferenceGraph);
    static bool dfsColoring(Vertex* vertex, int color);
    static bool DSaturComp(const Vertex& v1, const Vertex& v2);
    static bool DSatur(const Graph &interferenceGraph, int& numColors);
    static bool runAlgorithm(const Graph &interferenceGraph, int& numColors);
};

#endif //DA_SECOND_PROJECT_DSATURALGORITHM_H