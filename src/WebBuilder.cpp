#include "WebBuilder.h"
#include "../data_structures/UFDS.h"
#include <iostream>
#include <map>

WebBuilder::WebBuilder(std::string varName, std::vector<LiveRange> liveRanges) : varName(std::move(varName)), liveRanges(std::move(liveRanges)) {}

void WebBuilder::mergeLiveRanges(UFDS& ufds, const unsigned n) const {
    // Map each line to the index of the live range in the array liveRanges where it first appeared
    std::map<Line, int> lineToLiveRange;

    for (int i = 0; i < n; i++) { // for all live ranges
        for (Line line : this->liveRanges[i]) {

            if (lineToLiveRange.count(line)) { // if the current line was already seen in a previous live range
                ufds.linkSets(i, lineToLiveRange[line]); // merge the current live range of index i to the live range containing line

            } else { // if the current lineNum was never seen
                lineToLiveRange[line] = i;
            }
        }
    }
}

std::map<int, LiveRange> WebBuilder::getMergedLiveRanges(UFDS& ufds, const unsigned n) const {
    // Find all live ranges populating a map that makes the matching LiveRangeIndex: LiveRange
    std::map<int, LiveRange> indexToLiveRange; // Note: not all live range indexes will be keys of this map: only the ones that are highest parents

    for (int i = 0; i < n; i++) {
        int root = static_cast<int>(ufds.findSet(i)); // the index of the parent live range of live range i (can either be itself or other live range)
        for (Line line : this->liveRanges[i]) {
            // 'it' is an iterator for the inserted line / or for the already existing value (if not inserted) and 'inserted' is a boolean indicating if the line was inserted or not
            const auto [it, inserted] = indexToLiveRange[root].insert(line); // associate this line to the parent live range
            if (!inserted && it->type != read) {
                Line updated = *it; // copy of the iterator's value
                updated.type = read; // set its type to read / enforce read (nor '-' neither '+', because all possible combinations lead to the connection line having no '-' nor '+')
                indexToLiveRange[root].erase(it); // erase the old line (with the old type)
                indexToLiveRange[root].insert(updated); // insert the updated line (with type read)
            }
        }
    }
    return indexToLiveRange;
}

std::vector<Web> WebBuilder::buildWebs() const {
    const unsigned n = liveRanges.size();
    UFDS ufds(n); // in the beginning, all liveRanges are parents of themselves

    mergeLiveRanges(ufds, n);
    std::map<int, LiveRange> liveRangeIndex_LiveRange = getMergedLiveRanges(ufds, n);

    std::vector<Web> webs;
    // Populate the result (only the resultant mergedLiveRanges matter, not the indexes)
    for (const auto& [_, mergedLiveRange] : liveRangeIndex_LiveRange) {
        webs.push_back({this->varName, mergedLiveRange});
    }
    return webs;
}
