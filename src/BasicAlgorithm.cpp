#include "BasicAlgorithm.h"

#include <stack>

bool BasicAlgorithm::runAlgorithm(Graph &interferenceGraph, int &numColors) {
    std::stack<Vertex*> s;
    std::vector<Vertex*> disabledVertices;
    // Loop runs until all vertices are removed
    while (!interferenceGraph.getActiveVertexSet().empty()) {
        bool removedVertex = false; // boolean flag to check whether at least one vertex was removed in this iteration
        for (Vertex* vertex : interferenceGraph.getActiveVertexSet()) {
            // Only consider degree of active
            if (vertex->getActiveAdj().size() < numColors) {
                s.push(vertex);
                vertex->disable();
                disabledVertices.push_back(vertex);
                removedVertex = true;
            }
        }
        // If no vertex was removed in this iteration, it means that all remaining vertices have degree >= numColors,
        // so coloring is not possible, returning false
        if (!removedVertex) {
            for (auto vertex : disabledVertices) {
                vertex->setActive();
            }
            return false;
        }
    }

    int maxColor = -1;
    while (!s.empty()) {
        // Get the last vertex added to the stack
        Vertex* vertex = s.top();
        s.pop();
        vertex->setActive();

        // Get the colors used by the neighbors of the vertex
        std::set<int> neighborColors = vertex->getNeighborColors();

        // Find the minimum not used color
        int selectedColor = 0;
        int maxNeighborColor = neighborColors.empty() ? -1 : *neighborColors.rbegin(); // max color used by the neighbors, or -1 if no neighbor has a color
        for (selectedColor = 0; selectedColor <= maxNeighborColor; selectedColor++) {
            if (neighborColors.find(selectedColor) == neighborColors.end()) break; // if this color is not used
        } // if all colors are used from 0 to the maxColor, use a new color

        if (selectedColor > maxColor) maxColor = selectedColor; // update numColors

        // Set the color of the vertex and update the neighbor colors
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
    for (int colorsUsed = 1; colorsUsed <= maxColors; colorsUsed++) {
        if (runAlgorithm(interferenceGraph, colorsUsed)) {
            if (colorsUsed <= maxColors) return colorsUsed;
            interferenceGraph.resetColors();
            return 0;
        }
        interferenceGraph.resetColors();
    }

    return 0; // should never happen
}
