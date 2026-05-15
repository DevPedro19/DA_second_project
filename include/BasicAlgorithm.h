#ifndef DA_SECOND_PROJECT_BASICALGORITHM_H
#define DA_SECOND_PROJECT_BASICALGORITHM_H

#include "ColoringAlgorithm.h"

class BasicAlgorithm : public ColoringAlgorithm {
public:
    int execute(Graph &interferenceGraph, int maxColors) override;
private:
    static bool runAlgorithm(Graph &interferenceGraph, int& numColors);
};

#endif //DA_SECOND_PROJECT_BASICALGORITHM_H
