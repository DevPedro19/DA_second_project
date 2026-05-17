//
// Created by pedro on 5/11/2026.
//

#ifndef DA_SECOND_PROJECT_SPLITTINGALGORITHM_H
#define DA_SECOND_PROJECT_SPLITTINGALGORITHM_H
#include "BasicAlgorithm.h"
#include "HybridAlgorithm.h"
/**
 * @brief Implementation of the splitting algorithm, which is a heuristic algorithm that tries to find the
 * best vertex (web) to split (divide into two separate webs, reducing interference) and then colors the graph with the basic algorithm
 * @param interferenceGraph The interference graph to color.
 * @param maxWebsToSplit The maximum number of webs that can be split.
 * @param numColors The number of colors allowed for coloring the graph.
 * @return The number of colors used for coloring the graph, or 0 if
 * it is not possible to color the graph with the given maximum number of colors after splitting the specified number of webs
 */
class SplittingAlgorithm {
public:
    /** @brief Constructor for the SplittingAlgorithm class, which takes a pointer to a ColoringAlgorithm as a parameter.
     * This allows the SplittingAlgorithm to use any coloring algorithm that implements the ColoringAlgorithm interface,
     * making it more flexible and reusable. */
     explicit
    SplittingAlgorithm(ColoringAlgorithm* coloring_algorithm);

    int execute(Graph &interferenceGraph, int numColors, int maxWebsToSplit);

private:
    static bool splittingComp(const Vertex& v1, const Vertex& v2);
    static std::pair<Line, Line> runIntersectionAlgorithm(const Graph& interferenceGraph, const Web& webToSplit, int maxColors);
    static std::pair<Web, Web> splitWeb( Web& webToSplit, const Line& xi, const Line& xf);

    ColoringAlgorithm* coloring_algorithm;
};


#endif //DA_SECOND_PROJECT_SPLITTINGALGORITHM_H