#ifndef DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H
#define DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H
#include "BasicAlgorithm.h"
#include "SpillingAlgorithm.h"

class AlgorithmAggregator {
public:
    AlgorithmAggregator();
    int runBasicAlgorithm(Graph& interferenceGraph, int& numColors) const;
    int runSpillingAlgorithm(Graph &interferenceGraph, int maxRegsToSpill, int numColors);

private:
    BasicAlgorithm basicAlgorithm;
    SpillingAlgorithm spillingAlgorithm;
};

#endif //DA_SECOND_PROJECT_ALGORITHMAGGREGATOR_H
