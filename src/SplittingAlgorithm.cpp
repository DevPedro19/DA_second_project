//
// Created by pedro on 5/11/2026.
//

#include "SplittingAlgorithm.h"
#include <algorithm>

#include "HybridAlgorithm.h"
#include "../data_structures/MutablePriorityQueue.h"

SplittingAlgorithm::SplittingAlgorithm(ColoringAlgorithm* coloring_algorithm) : coloring_algorithm(coloring_algorithm) {}
// 1. Higher degree
// 2. Higher neighbor degree sum
// This criteria extends the definition of the "hardest node to color". Therefore, selecting the hardest node to color first potentially minimizes the number of colors needed.
bool SplittingAlgorithm::splittingComp(const Vertex& v1, const Vertex& v2) {
    if (v1.getDegree() == v2.getDegree()) {
        if (v1.getNeighborDegreeSum() == v2.getNeighborDegreeSum()) {
            // Promotes splitting instead of spilling
            return (v1.getInfo().getLastLineNum() - v1.getInfo().getFirstLineNum()) >
            (v2.getInfo().getLastLineNum() - v2.getInfo().getFirstLineNum());
        }
        return v1.getNeighborDegreeSum() > v2.getNeighborDegreeSum(); // extends on the definition of "difficult-to-color vertex"
    }
    return v1.getDegree() > v2.getDegree();
}

bool aux(const std::pair<Line,int> &a, const std::pair<Line,int> &b) {
    if (a.first == b.first) {
        return a.second < b.second; // To avoid false interference points
    }
    return a.first < b.first;
}

std::pair<Line, Line> SplittingAlgorithm::runIntersectionAlgorithm(const Graph& interferenceGraph, const Web& webToSplit, int maxColors) {
    std::vector activeWebs = {webToSplit}; // The web to split is active
    const Vertex* webToSplitVertex = interferenceGraph.findVertex(webToSplit);

    // activeWebs will contain all webs that interfere with webToSplit
    for (const auto edge : webToSplitVertex->getActiveAdj()) {
        Web neighbor = edge->getDest()->getInfo();
        activeWebs.push_back(neighbor);
    }

    std::vector<std::pair<Line,int>> breakPoints;
    for (auto& web : activeWebs) {
        breakPoints.emplace_back(web.getFirstLine(), 1); // represents a new active web
        breakPoints.emplace_back(web.getLastLine(), -1); // represents the end of an active web
    }


    std::sort(breakPoints.begin(), breakPoints.end(), aux);
    int count = 0; int prev = 0;
    Line xi = {-1, active}, xf = {-1, active};
    for (auto point : breakPoints) {
        count += point.second; // one more or one less active web

        if (count > maxColors && xi.lineNum == -1) xi = point.first; // first line number where intersections exceed max colors
        // xi != -1  guarantees that a start existed before
        else if (count <= maxColors && prev > maxColors  && xi.lineNum != -1) { // Most recent point where the intersections do not exceed max color
            xf = point.first;
        }
        prev = count;
    }

    xi = std::max(xi, webToSplit.getFirstLine());
    xf = std::min(xf, webToSplit.getLastLine());
    return {xi, xf};
}


std::pair<Web, Web> SplittingAlgorithm::splitWeb(Web& webToSplit, const Line& xi, const Line& xf) {
    Web splitWeb1 = webToSplit;
    splitWeb1.setLastLine(xi); // The first part of the split web will end at the line before the intersection point

    Web splitWeb2 = webToSplit;
    splitWeb2.setFirstLine(xf); // The second part of the split web will start at the line after the intersection point

    return {splitWeb1, splitWeb2};
}

int SplittingAlgorithm::execute(Graph &interferenceGraph, int numColors, int maxWebsToSplit) {
    int colorsUsed = 0;
    std::vector<Web> websToSplit;
    int splitWebs;

    for (splitWebs = 1; splitWebs <= maxWebsToSplit; splitWebs++) {
        MutablePriorityQueue<Vertex> pq(splittingComp);
        std::vector<Web> webs = interferenceGraph.getWebs();
        for (Vertex* vertex : interferenceGraph.getVertexSet()) {
            if (vertex->isActive()) pq.insert(vertex);
        }
        Web webToSplit = pq.extractMin()->getInfo(); // split a web
        websToSplit.push_back(webToSplit);
        auto [xi, xf] = runIntersectionAlgorithm(interferenceGraph, webToSplit, numColors);
        auto [splitWeb1, splitWeb2] = splitWeb(webToSplit, xi, xf);

        // Save the web that was split to output
        Graph::addSplitWebsToMap(webToSplit,{{xi,xf},{splitWeb1, splitWeb2}});

        webs.erase(std::find(webs.begin(), webs.end(), webToSplit));
        if (!splitWeb1.getWeb().empty()) webs.push_back(splitWeb1);
        if (!splitWeb2.getWeb().empty()) webs.push_back(splitWeb2);

        interferenceGraph.rebuildGraph(webs); // rebuild the graph with the new webs
        if ((colorsUsed = coloring_algorithm->execute(interferenceGraph, numColors))) {
            break;
        }
    }
    return colorsUsed;
}
