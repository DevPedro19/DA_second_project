#ifndef DA_SECOND_PROJECT_SPLITTINGALGORITHM_H
#define DA_SECOND_PROJECT_SPLITTINGALGORITHM_H

#include "BasicAlgorithm.h"

/**
 * @brief Class that represents the Splitting algorithm.
 * @details The splitting algorithm is used when the graph cannot be colored with the given `numColors` from the execution plan. It will split a web into two new webs in order to reduce the number of registers (colors) needed.
 */
class SplittingAlgorithm {
public:
    /**
     * @brief Constructs the Splitting algorithm using a `basicAlgorithm` instance.
     * @param basicAlgorithm The basic algorithm instance. It is used to see if the splitting was effective in reducing the number of colors needed to color the graph, it tests if the spilled graph is colorable with `numColors` colors.
     */
    SplittingAlgorithm(const BasicAlgorithm& basicAlgorithm);

    /**
     * @brief The main splitting algorithm.
     * @details The algorithm works as follows:
     * 1. It creates a priority queue of the active vertices in the graph, ordered by the splitting criteria the `splitting comp` function. The queue helps to select the best vertice (web) to be split.
     * 2. Inserts all active vertices to the queue.
     * 3. Iterates from 1 to the `maxWebsToSplit` parameter, in each iteration it:
     *   a. Extracts the vertex with the highest priority (the one that is the best candidate for splitting) from the queue and splits it into two new webs.
     *   b. Constructs a new interference graph with the new webs and updates the edges accordingly.
     *   c. Executes the basic algorithm on the modified graph to check if it can be colored with `numColors` colors. If it can, it returns the number of colors used. If it cannot, it continues to the next iteration to split another vertex.
     * 4. If after splitting up to `maxWebsToSplit` vertices the graph still cannot be colored with `numColors` colors, it returns 0 to indicate failure.
     * @param interferenceGraph The interference graph to be spilled and colored.
     * @param numColors The maximum number of colors (registers) the graph can be colored.
     * @param maxWebsToSplit The maximum number of webs (vertices) that can be split.
     * @return The number of registers the graph can be colored. If 0 it means the graph still cannot be colored.
     */
    int execute(Graph &interferenceGraph, int numColors, int maxWebsToSplit) const;

private:
    /**
     * @brief Comparison function for the priority queue used in the splitting algorithm.
     * @details It defines the splitting criteria for selecting which vertex to split first. The criteria are as follows:
     * 1. Higher degree: vertices with more neighbors are more difficult to color, so they are prioritized for splitting.
     * 2. Higher neighbor degree sum: if two vertices have the same degree, the one whose neighbors have a higher total degree is prioritized for splitting, as it is likely to cause more conflicts if not split.
     * 3. Longer live range: if two vertices have the same degree and the same neighbor degree sum, the one with the longer live range is prioritized since it has the most number of accesses, and therefore the most number of reads/writes associated, so it is more likely to be beneficial to split it.
     * @param v1 First vertex.
     * @param v2 Second vertex.
     * @return True if v1 should be split before v2, false otherwise.
     */
    static bool splittingComp(const Vertex& v1, const Vertex& v2);

    /**
     * @brief Algorithm that finds the points were the given web must be split.
     * @details It works as follows:
     * 1. It creates a list of active webs that contains the web to split and all its neighbors in the interference graph, the webs that interfere with the current Web.
     * 2. It creates a list of break points to help manage where webs start and end. For each web in the active webs, it adds its first line as a break point with value 1 (representing a new active web) and its last line as a break point with value -1 (representing the end of an active web).
     * 3. It sorts the break points by line number, and in case of a tie, it prioritizes the start of a web over the end of a web to avoid false interference points.
     * 4. It iterates through the break points, keeping track of the number of active webs at each point. It identifies the first line number (xi) where the number of active webs exceeds `maxColors`, and the most recent line number (xf) where the number of active webs does not exceed `maxColors` after xi. These two line numbers represent the points where the web should be split to potentially reduce the number of colors needed.
     * @param interferenceGraph The interference graph to be spilled and colored.
     * @param webToSplit The instance of the web to be split.
     * @param maxColors The maximum number of colors (registers). This variable is used to find the xi and xf. Once the number of active webs surpasses `maxColors` with will initialize xi and once it goes back to `maxColors` or less it will update xf until the end of the break points.
     * @return The lines were the `webToSplit` should be split.
     */
    static std::pair<Line, Line> runIntersectionAlgorithm(const Graph& interferenceGraph, const Web& webToSplit, int maxColors);

    /**
     * @brief Algorithm that splits a web into two new webs given the lines where it should be split.
     * @param webToSplit Web that is going to be split.
     * @param xi First line were it should be split.
     * @param xf Last line were it should be split.
     * @return A pair of the two new Webs created from the resulting split.
     */
    static std::pair<Web, Web> splitWeb(const Web& webToSplit, const Line& xi, const Line& xf);

    /**
     * @brief Instance of the basic algorithm.
     */
    BasicAlgorithm basicAlgorithm;
};


#endif //DA_SECOND_PROJECT_SPLITTINGALGORITHM_H