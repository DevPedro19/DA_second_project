//
// Created by guilhermecunha on 04/05/26.
//

#ifndef DA_SECOND_PROJECT_WEBBUILDER_H
#define DA_SECOND_PROJECT_WEBBUILDER_H

#include <map>

#include "../data_structures/UFDS.h"
#include "allocation.h"
#include <vector>

/**
 * @brief The WebBuilder class is responsible for building the webs for a given variable and its associated live ranges.
 */
class WebBuilder {
public:
    /**
     * @brief Constructor of the class, which initializes the varName and liveRanges attributes.
     * @param varName The name of the variable for which to build the webs.
     * @param liveRanges An array of live ranges relative to the same variable, which may or may not be fully merged.
     */
    WebBuilder(std::string varName, std::vector<LiveRange> liveRanges);

    /**
     * @brief High-level function that builds the webs for the variable varName, by first merging the live ranges of the array liveRanges and then populating the result with the merged live ranges.
     * @return A vector of webs for the variable varName, which may contain more than just one web if the liveRanges are not fully merged into one live range.
     * @par Complexity
     * Time: O(L * log L) where L is the total number of lines in all live ranges. The mergeLiveRanges and getMergedLiveRanges functions both have a time complexity of O(L * log L), which dominates. The creation of the UFDS data structure has a time complexity of O(n), where n is the number of live ranges. The final for loop iterates through the merged live ranges, which in the worst case can be O(n) if all live ranges are disjoint, and performs constant time operations (O(1)) to push back the webs in the result vector. Therefore, the overall time complexity of this function is O(L * log L).
     * Space: O(L) because of the lineToLiveRange map used in mergeLiveRanges and the indexToLiveRange map returned in getMergedLiveRanges, which can both have space complexity of O(L).
     */
    [[nodiscard]] std::vector<Web> buildWebs() const;

private:
    /**
     * @brief Establishes the hierarchy of the liveRanges, ie, what are the parent live ranges, by using the UFDS data structure to merge the live ranges that have at least one line in common.
     * @param ufds The UFDS data structure used to merge the live ranges that have at least one line in common.
     * @param n The number of live ranges in the array liveRanges.
     * @par Complexity
     * Time: O(L * log L) where L is the total number of lines in all live ranges. The for loops iterates through all lines of all live ranges (O(L)) and for each one performs logarithmic operations (O(log L)) with the map lineToLiveRange, which has at most L entries (.count(line) and insertion in the map). The linkSets operation of the UFDS has an amortized time complexity of O(α(n)), where α is the inverse Ackermann function, which grows very slowly and can be considered almost constant for all practical purposes (O(1)). Therefore, the overall time complexity of this function is O(L * log L).
     * Space: O(L) because of lineToLiveRange map.
     */
    void mergeLiveRanges(UFDS& ufds, unsigned n) const;

    /**
     * @brief Finds all merged live ranges for each (highest) parent live range.
     * @param ufds  The UFDS data structure used to find the parent live range of each live range and to associate the lines of each child live range to its parent live range.
     * @param n The number of live ranges in the array liveRanges.
     * @return A map associating the index of each (highest) parent live range to its merged live range, which is the union of all its child live ranges (including itself).
     * @par Complexity
     * Time: O(L * log L) where L is the total number of lines in all live ranges. The for loops iterates through all lines of all live ranges (O(L)) and for each one performs insertions in LiveRanges (which are sets) and searches in indexToLiveRange (which is a map). These are logarithmic operations (O(log L)). Erase and insertion in the map indexToLiveRange can also be performed (O(log L)). Therefore, the overall time complexity of this function is O(L * log L).
     * Space: O(L) because of indexToLiveRange map.
     */
    std::map<int, LiveRange> getMergedLiveRanges(UFDS& ufds, unsigned n) const;

    /**
     * @brief The name of the variable for which to build the webs.
     */
    std::string varName;

    /**
     * @brief An array of live ranges relative to the same variable, which may or may not be fully merged.
     */
    std::vector<LiveRange> liveRanges;
};

#endif //DA_SECOND_PROJECT_WEBBUILDER_H
