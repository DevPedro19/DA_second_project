#ifndef DA_SECOND_PROJECT_SPILLINGALGORITHM_H
#define DA_SECOND_PROJECT_SPILLINGALGORITHM_H

#include "GraphColoringAlgorithm.h"

class SpillingAlgorithm : public GraphColoringAlgorithm {
public:
    bool execute(Graph &interferenceGraph, int &numColors) override;
};

#endif //DA_SECOND_PROJECT_SPILLINGALGORITHM_H
