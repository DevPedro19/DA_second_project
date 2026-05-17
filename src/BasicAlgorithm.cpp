#include "BasicAlgorithm.h"

#include <stack>

bool BasicAlgorithm::runAlgorithm(Graph &interferenceGraph, int &numColors) {
    std::stack<Vertex* > s;

    while (!interferenceGraph.getActiveVertexSet().empty()) {
        bool removedVertex = false;
        for (Vertex* vertex : interferenceGraph.getActiveVertexSet()) {
            // Only consider degree of active
            if (vertex->getActiveAdj().size() < numColors) {
                s.push(vertex);
                vertex->disable();
                removedVertex = true;
            }
        }
        if (!removedVertex) {
            return false; // no vertex with degree < numColors, so coloring is not possible
        }
    }

    int maxColor = -1;
    while (!s.empty()) {
        Vertex* vertex = s.top();
        s.pop();
        vertex->setActive();

        std::set<int> neighborColors = vertex->getNeighborColors();

        // find the minimum not used color
        int selectedColor = 0;
        int maxNeighborColor = neighborColors.empty() ? -1 : *neighborColors.rbegin(); // max color used by the neighbors, or -1 if no neighbor has a color
        for (selectedColor = 0; selectedColor <= maxNeighborColor; selectedColor++) {
            if (neighborColors.find(selectedColor) == neighborColors.end()) break; // if this color is not used
        } // if all colors are used from 0 to the maxColor, use a new color

        if (selectedColor > maxColor) maxColor = selectedColor; // update numColors

        vertex->setColor(selectedColor);

        for (Edge* edge : vertex->getAdj()) {
            Vertex* neighbor = edge->getDest();
            neighbor->addNeighborColor(selectedColor);
        }
    }
    numColors = maxColor + 1; // numColors is the number of colors used, which is maxColor + 1 since colors start from 0
    return true;
}

int BasicAlgorithm::execute(Graph &interferenceGraph, const int maxColors) {
    interferenceGraph.resetColors();

    // Basic algorithm modifies the variable regsUsed
    for (int colorsUsed = 1; colorsUsed <= std::min(maxColors, 3); colorsUsed++) {
        if (runAlgorithm(interferenceGraph, colorsUsed)) {
            if (colorsUsed <= maxColors) return colorsUsed;
            interferenceGraph.resetColors();
            return 0;
        }
        interferenceGraph.resetColors();
    }

    return 0; // should never happen
}
