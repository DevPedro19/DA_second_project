//
// Created by guilhermecunha on 04/05/26.
//

#ifndef DA_SECOND_PROJECT_WEBBUILDER_H
#define DA_SECOND_PROJECT_WEBBUILDER_H

#include "../data_structures/UFDS.h"
#include "allocation.h"
#include <map>
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
     */
    [[nodiscard]] std::vector<Web> buildWebs() const;

private:
    /**
     * @brief Establishes the hierarchy of the liveRanges, ie, what are the parent live ranges, by using the UFDS data structure to merge the live ranges that have at least one line in common.
     * @param ufds The UFDS data structure used to merge the live ranges that have at least one line in common.
     * @param n The number of live ranges in the array liveRanges.
     */
    void mergeLiveRanges(UFDS& ufds, unsigned n) const;

    /**
     * @brief Finds all merged live ranges for each (highest) parent live range.
     * @param ufds  The UFDS data structure used to find the parent live range of each live range and to associate the lines of each child live range to its parent live range.
     * @param n The number of live ranges in the array liveRanges.
     * @return A map associating the index of each (highest) parent live range to its merged live range, which is the union of all its child live ranges (including itself).
     */
    std::map<int, LiveRange> getMergedLiveRanges(UFDS& ufds, unsigned n) const;

    /**
     * @brief The name of the variable for which to build the webs.
     */
    std::string varName;

    /**
     * @brief An array of live ranges relative to the same variable, which may or may not be fully merged.
     */
    std::vector<LiveRange> liveRanges;  // variable's liveRanges
};

#endif //DA_SECOND_PROJECT_WEBBUILDER_H
