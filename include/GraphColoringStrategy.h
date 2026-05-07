#ifndef DA_SECOND_PROJECT_GRAPHCOLORINGSTRATEGY_H
#define DA_SECOND_PROJECT_GRAPHCOLORINGSTRATEGY_H

#include "../data_structures/Graph.h"
#include "GraphColoringAlgorithm.h"

class GraphColoringStrategy {
public:
    explicit GraphColoringStrategy();
    virtual ~GraphColoringStrategy() = default;

    void setStrategy(GraphColoringAlgorithm* graphColoringAlgorithm);
    bool execute(Graph &interferenceGraph, int &numColors) const;

private:
    GraphColoringAlgorithm* graphColoringAlgorithm{};
};

#endif //DA_SECOND_PROJECT_GRAPHCOLORINGSTRATEGY_H
