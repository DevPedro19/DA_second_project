#ifndef DA_SECOND_PROJECT_BASICALGORITHM_H
#define DA_SECOND_PROJECT_BASICALGORITHM_H

#include "../data_structures/Graph.h"

class BasicAlgorithm {
public:
    int execute(Graph &interferenceGraph, int maxColors) const;

private:
    static bool graphHasNoEdges(const Graph &interferenceGraph);
    static bool isGraphBipartite(const Graph &interferenceGraph);
    static bool dfsColoring(Vertex* vertex, int color);
    static bool DSaturComp(const Vertex& v1, const Vertex& v2);
    static bool DSatur(const Graph &interferenceGraph, int& numColors);

    static bool runAlgorithm(const Graph &interferenceGraph, int& numColors);
};

#endif //DA_SECOND_PROJECT_BASICALGORITHM_H
