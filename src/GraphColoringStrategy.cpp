#include "GraphColoringStrategy.h"
#include "GraphColoringAlgorithm.h"

GraphColoringStrategy::GraphColoringStrategy() = default;

void GraphColoringStrategy::setStrategy(GraphColoringAlgorithm* graphColoringAlgorithm) {
    this->graphColoringAlgorithm = graphColoringAlgorithm;
}

bool GraphColoringStrategy::execute(Graph& interferenceGraph, int& numColors) const {
    return this->graphColoringAlgorithm->execute(interferenceGraph, numColors);
}
