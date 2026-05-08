#include "BasicAlgorithm.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "../data_structures/Graph.h"

bool graphHasNoEdges(const Graph &interferenceGraph) {
    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive() && !vertex->getActiveAdj().empty()) {
            return false;
        }
        vertex->setColor(0);
    }
    return true;
}

// Alternating colors 0 and 1
bool dfsColoring(Vertex* vertex, int color) {
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

bool isGraphBipartite(const Graph &interferenceGraph) {
    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive() && vertex->getColor() == -1) { // not visited and active
            if (!dfsColoring(vertex, 0)) { // start with color 0
                return false;
            }
        }
    }
    return true;
}

bool comp(const Vertex& v1, const Vertex& v2) {
    if (v1.getNeighborColors().size() == v2.getNeighborColors().size()) {
        return v1.getDegree() > v2.getDegree();
    }
    return v1.getNeighborColors().size() > v2.getNeighborColors().size();
}

bool DSatur(const Graph &interferenceGraph, int& numColors) {
    MutablePriorityQueue<Vertex> pq(comp);

    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive()) pq.insert(vertex);
    }

    int maxColor = -1;
    while (!pq.empty()) {
        Vertex* saturated = pq.extractMin();

        std::set<int> neighborColors = saturated->getNeighborColors();

        // find the minimum not used color
        int selectedColor;
        for (selectedColor = 0; selectedColor < *neighborColors.rbegin(); selectedColor++) {

            if (neighborColors.find(selectedColor) == neighborColors.end()) break; // if this color is not used
        } // if all colors are used from 0 to the maxColor, use a new color

        if (selectedColor > maxColor) maxColor = selectedColor; // update maxColor

        saturated->setColor(selectedColor);

        for (Edge* edge : saturated->getActiveAdj()) {
            Vertex* neighbor = edge->getDest();
            neighbor->getNeighborColors().insert(selectedColor);
            pq.decreaseKey(neighbor); // update heap entry after updating the neighbor colors
        }
    }

    numColors = maxColor + 1; // maxColor is 0-based
    return true; // DSatur algorithm always finds the minimum number of colors needed to color the graph, independently of the numColors passed
}


bool BasicAlgorithm::execute(Graph &interferenceGraph, int& numColors) {

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
