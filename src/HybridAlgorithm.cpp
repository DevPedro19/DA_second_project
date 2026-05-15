#include "../include/HybridAlgorithm.h"
#include "../data_structures/MutablePriorityQueue.h"

bool HybridAlgorithm::graphHasNoEdges(const Graph &interferenceGraph) {
    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive()) {
            if (!vertex->getActiveAdj().empty()) {
                return false;
            }
            vertex->setColor(0);
        }
    }
    return true;
}

bool HybridAlgorithm::dfsColoring(Vertex* vertex, int color) {
    vertex->setColor(color);

    for (const Edge* edge : vertex->getActiveAdj()) {
        Vertex* neighbor = edge->getDest();

        if (neighbor->getColor() == -1) { // not visited
            if (!dfsColoring(neighbor, 1 - color)) {
                return false;
            }

        } else if (neighbor->getColor() == color) { // cannot be bipartite graph, as two adjacent vertices have the same color
            return false;
        }
    }
    return true;
}

bool HybridAlgorithm::isGraphBipartite(const Graph &interferenceGraph) {
    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive() && vertex->getColor() == -1) { // not visited and active
            if (!dfsColoring(vertex, 0)) { // start with color 0
                return false;
            }
        }
    }
    return true;
}

bool HybridAlgorithm::DSaturComp(const Vertex& v1, const Vertex& v2) {
    if (v1.getNeighborColors().size() == v2.getNeighborColors().size()) {
        return v1.getDegree() > v2.getDegree();
    }
    return v1.getNeighborColors().size() > v2.getNeighborColors().size();
}

bool HybridAlgorithm::DSatur(const Graph &interferenceGraph, int& numColors) {
    MutablePriorityQueue<Vertex> pq(DSaturComp);

    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive()) pq.insert(vertex);
    }

    int maxColor = -1;
    while (!pq.empty()) {
        Vertex* saturated = pq.extractMin();

        std::set<int> neighborColors = saturated->getNeighborColors();

        // find the minimum not used color
        int selectedColor = 0;
        int maxNeighborColor = neighborColors.empty() ? -1 : *neighborColors.rbegin(); // max color used by the neighbors, or -1 if no neighbor has a color
        for (selectedColor = 0; selectedColor <= maxNeighborColor; selectedColor++) {

            if (neighborColors.find(selectedColor) == neighborColors.end()) break; // if this color is not used
        } // if all colors are used from 0 to the maxColor, use a new color

        if (selectedColor > maxColor) maxColor = selectedColor; // update maxColor

        saturated->setColor(selectedColor);

        for (Edge* edge : saturated->getActiveAdj()) {
            Vertex* neighbor = edge->getDest();
            if (neighbor->getColor() == -1) {
                neighbor->addNeighborColor(selectedColor);
                pq.decreaseKey(neighbor); // update heap entry after updating the neighbor colors
            }
        }
    }

    numColors = maxColor + 1; // maxColor is 0-based
    return true; // DSatur algorithm always finds the minimum number of colors needed to color the graph, independently of the numColors passed
}

bool HybridAlgorithm::runAlgorithm(const Graph &interferenceGraph, int& numColors) {

    if (numColors == 1) {
        return graphHasNoEdges(interferenceGraph);
    }

    if (numColors == 2) {
        return isGraphBipartite(interferenceGraph);
    }

    if (numColors >= 3) {
        return DSatur(interferenceGraph, numColors);
    }
    return false; // numColors cannot be < 1
}

int HybridAlgorithm::execute(Graph &interferenceGraph, const int maxColors) {
    interferenceGraph.resetColors();

    // DSatur algorithm modifies the variable regsUsed, because it finds the minimum number of colors after just one run
    for (int colorsUsed = 1; colorsUsed <= std::min(maxColors, 3); colorsUsed++) {
        if (runAlgorithm(interferenceGraph, colorsUsed)) { // DSatur will always return true
            if (colorsUsed <= maxColors) return colorsUsed;
            interferenceGraph.resetColors();
            return 0;
        }
        interferenceGraph.resetColors();
    }

    return 0; // should never happen
}


