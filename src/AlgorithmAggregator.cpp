#include "AlgorithmAggregator.h"

AlgorithmAggregator::AlgorithmAggregator()
    : spillingAlgorithm(&basicAlgorithm), // The spilling algorithm uses the basic algorithm for coloring
      splittingAlgorithm(&basicAlgorithm), // The splitting algorithm uses the basic algorithm for coloring
      freeAlgorithm(&hybridAlgorithm) {} // The free algorithm uses the hybrid algorithm for coloring

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