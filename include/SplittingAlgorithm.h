//
// Created by pedro on 5/11/2026.
//

#ifndef DA_SECOND_PROJECT_SPLITTINGALGORITHM_H
#define DA_SECOND_PROJECT_SPLITTINGALGORITHM_H
#include "BasicAlgorithm.h"

class SplittingAlgorithm {
public:
    SplittingAlgorithm(const BasicAlgorithm& basicAlgorithm);
    int execute(Graph &interferenceGraph, int numColors, int maxWebsToSplit);

private:
    static bool splittingComp(const Vertex& v1, const Vertex& v2);
    static std::pair<Line, Line> runIntersectionAlgorithm(const Graph& interferenceGraph, const Web& webToSplit, int maxColors);
    static std::pair<Web, Web> splitWeb( Web& webToSplit, const Line& xi, const Line& xf);

    BasicAlgorithm basicAlgorithm;
};


#endif //DA_SECOND_PROJECT_SPLITTINGALGORITHM_H