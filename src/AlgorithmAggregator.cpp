#include "AlgorithmAggregator.h"

// Basic Algorithm is initialized with default constructor
AlgorithmAggregator::AlgorithmAggregator() : spillingAlgorithm(basicAlgorithm), splittingAlgorithm(basicAlgorithm) {
}

int AlgorithmAggregator::runBasicAlgorithm(Graph& interferenceGraph, int& numColors) const {
    return basicAlgorithm.execute(interferenceGraph, numColors);
}

int AlgorithmAggregator::runSpillingAlgorithm(Graph &interferenceGraph, int maxRegsToSpill, int numColors) {
    return spillingAlgorithm.execute(interferenceGraph, maxRegsToSpill, numColors);
}

int AlgorithmAggregator::runSplittingAlgorithm(Graph &interferenceGraph, int numColors, int maxWebsToSplit) {
    return splittingAlgorithm.execute(interferenceGraph, numColors, maxWebsToSplit);
}