//
// Created by pedro on 5/15/2026.
//

#ifndef DA_SECOND_PROJECT_COLORINGALGORITHM_H
#define DA_SECOND_PROJECT_COLORINGALGORITHM_H

#include "../data_structures/Graph.h"

class Graph;

class ColoringAlgorithm {
public:
    virtual ~ColoringAlgorithm() = default;

    virtual int execute(Graph &interferenceGraph, int numColors) = 0;
};

#endif //DA_SECOND_PROJECT_COLORINGALGORITHM_H