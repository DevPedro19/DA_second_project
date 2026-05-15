#ifndef DA_SECOND_PROJECT_DSATURALGORITHM_H
#define DA_SECOND_PROJECT_DSATURALGORITHM_H

#include "ColoringAlgorithm.h"

class HybridAlgorithm : public ColoringAlgorithm {
public:
    int execute(Graph &interferenceGraph, int maxColors) override;
private:
    static bool graphHasNoEdges(const Graph &interferenceGraph);
    static bool isGraphBipartite(const Graph &interferenceGraph);
    static bool dfsColoring(Vertex* vertex, int color);
    static bool DSaturComp(const Vertex& v1, const Vertex& v2);
    static bool DSatur(const Graph &interferenceGraph, int& numColors);
    static bool runAlgorithm(const Graph &interferenceGraph, int& numColors);
};

#endif //DA_SECOND_PROJECT_DSATURALGORITHM_H