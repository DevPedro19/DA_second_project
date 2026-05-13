#ifndef DA_SECOND_PROJECT_SPILLINGALGORITHM_H
#define DA_SECOND_PROJECT_SPILLINGALGORITHM_H

#include "BasicAlgorithm.h"
#include "../data_structures/Graph.h"

class SpillingAlgorithm {
public:
    explicit SpillingAlgorithm(const BasicAlgorithm& basicAlgorithm);
    int execute(Graph &interferenceGraph, int maxWebsToSpill, int numColors);

private:
    static bool spillingComp(const Vertex& v1, const Vertex& v2);

    BasicAlgorithm basicAlgorithm;
};

#endif //DA_SECOND_PROJECT_SPILLINGALGORITHM_H
