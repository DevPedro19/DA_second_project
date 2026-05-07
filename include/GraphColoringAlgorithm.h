#ifndef DA_SECOND_PROJECT_GRAPHCOLORINGALGORITHM_H
#define DA_SECOND_PROJECT_GRAPHCOLORINGALGORITHM_H

#include "../data_structures/Graph.h"

class GraphColoringAlgorithm {
public:
    virtual ~GraphColoringAlgorithm() = default;

    virtual bool execute(Graph& interferenceGraph, int numColors) = 0;
};

#endif //DA_SECOND_PROJECT_GRAPHCOLORINGALGORITHM_H
