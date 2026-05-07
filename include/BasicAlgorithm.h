//
// Created by guilhermecunha on 06/05/26.
//

#ifndef DA_SECOND_PROJECT_BASICALGORITHM_H
#define DA_SECOND_PROJECT_BASICALGORITHM_H

#include "GraphColoringAlgorithm.h"
#include "../data_structures/Graph.h"

class BasicAlgorithm : public GraphColoringAlgorithm {
public:
    bool execute(Graph& interferenceGraph, int numColors) override;
};

#endif //DA_SECOND_PROJECT_BASICALGORITHM_H
