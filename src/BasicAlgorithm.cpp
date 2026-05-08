#include "BasicAlgorithm.h"
#include "../data_structures/MutablePriorityQueue.h"
#include "../data_structures/Graph.h"


bool comp(const Vertex& v1, const Vertex& v2) {
    if (v1.getNeighborColors().size() == v2.getNeighborColors().size()) {
        return v1.getDegree() > v2.getDegree();
    }
    return v1.getNeighborColors().size() > v2.getNeighborColors().size();
}

// Alternating colors 0 and 1
bool dfs_coloring(Vertex* vertex, int color) {
    vertex->setColor(color);

    for (const Edge* edge : vertex->getActiveAdj()) {
        Vertex* neighbor = edge->getDest();

        if (neighbor->getColor() == -1) { // not visited
            if (!dfs_coloring(neighbor, 1 - color)) {
                return false;
            }

        } else if (neighbor->getColor() == color) { // cannot be bipartite graph, as two adjacent vertices have the same color
            return false;
        }
    }
    return true;
}


bool BasicAlgorithm::execute(Graph &interferenceGraph, int& numColors) {

    //TODO: create functions for each algorithm
    if (numColors == 1) {
        for (Vertex* vertex : interferenceGraph.getVertexSet()) {
            if (vertex->isActive() && !vertex->getActiveAdj().empty()) {
                return false;
            }
            vertex->setColor(0);
        }
        return true;
    }

    if (numColors == 2) {

        for (Vertex* vertex : interferenceGraph.getVertexSet()) {
            if (vertex->isActive() && vertex->getColor() == -1) { // not visited and active
                if (!dfs_coloring(vertex, 0)) { // start with color 0
                    return false;
                }
            }
        }

        return true;
                
    }

    if (numColors >= 3) { // DSATUR algorithm

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
        return true; // DSatur finds the minimum number of colors needed to color the graph, independently of the numColors passed
    }

    return false; // numColors cannot be < 1
}
