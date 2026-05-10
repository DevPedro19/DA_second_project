#include "AlgorithmAggregator.h"

// Basic Algorithm is initialized with default constructor
AlgorithmAggregator::AlgorithmAggregator() : spillingAlgorithm(basicAlgorithm) {}

int AlgorithmAggregator::runBasicAlgorithm(Graph& interferenceGraph, int& numColors) const {
    return basicAlgorithm.execute(interferenceGraph, numColors);
}

int AlgorithmAggregator::runSpillingAlgorithm(Graph &interferenceGraph, int maxRegsToSpill, int numColors) {
    return spillingAlgorithm.execute(interferenceGraph, maxRegsToSpill, numColors);
}
