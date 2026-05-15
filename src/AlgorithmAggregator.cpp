#include "AlgorithmAggregator.h"

// Basic Algorithm is initialized with default constructor
AlgorithmAggregator::AlgorithmAggregator()
    : spillingAlgorithm(&basicAlgorithm),
      splittingAlgorithm(&basicAlgorithm),
      freeAlgorithm(&hybridAlgorithm) {}

int AlgorithmAggregator::runBasicAlgorithm(Graph& interferenceGraph, int& numColors){
    return basicAlgorithm.execute(interferenceGraph, numColors);
}

int AlgorithmAggregator::runSpillingAlgorithm(Graph &interferenceGraph, int maxRegsToSpill, int numColors) {
    return spillingAlgorithm.execute(interferenceGraph, maxRegsToSpill, numColors);
}

int AlgorithmAggregator::runSplittingAlgorithm(Graph &interferenceGraph, int maxWebsToSplit, int numColors) {
    return splittingAlgorithm.execute(interferenceGraph, numColors, maxWebsToSplit);
}

int AlgorithmAggregator::runFreeAlgorithm(Graph &interferenceGraph, int numColors, int maxWebsToSplit) {
    return freeAlgorithm.execute(interferenceGraph, numColors, maxWebsToSplit);
}