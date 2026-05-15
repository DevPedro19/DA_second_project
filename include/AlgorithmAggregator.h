#ifndef DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H
#define DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H

#include "BasicAlgorithm.h"
#include "HybridAlgorithm.h"
#include "SpillingAlgorithm.h"
#include "SplittingAlgorithm.h"

class AlgorithmAggregator {
public:
    AlgorithmAggregator();

    int runBasicAlgorithm(Graph& interferenceGraph, int& numColors);
    int runSpillingAlgorithm(Graph &interferenceGraph, int maxRegsToSpill, int numColors);
    int runSplittingAlgorithm(Graph &interferenceGraph, int maxWebsToSplit, int numColors);
    int runFreeAlgorithm(Graph &interferenceGraph, int numColors, int maxWebsToSplit);

private:
    BasicAlgorithm basicAlgorithm;
    HybridAlgorithm hybridAlgorithm;

    SpillingAlgorithm spillingAlgorithm;
    SplittingAlgorithm splittingAlgorithm;
    SplittingAlgorithm freeAlgorithm;
};

#endif //DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H