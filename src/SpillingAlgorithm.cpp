#include "SpillingAlgorithm.h"

#include "../data_structures/MutablePriorityQueue.h"

SpillingAlgorithm::SpillingAlgorithm(ColoringAlgorithm* coloring_algorithm) : coloring_algorithm(coloring_algorithm) {}

// 1. Higher degree
// 2. Higher neighbor degree sum
// These criteria extends the definition of the "hardest node to color". Therefore, selecting the hardest node to color first potentially minimizes the number of colors needed.
bool SpillingAlgorithm::spillingComp(const Vertex& v1, const Vertex& v2) {
    if (v1.getDegree() == v2.getDegree()) {
        if (v1.getNeighborDegreeSum() == v2.getNeighborDegreeSum()) {
            // Promotes spilling of smaller webs, because they have less reads/writes associated
            return (v1.getInfo().getLastLineNum() - v1.getInfo().getFirstLineNum()) <
            (v2.getInfo().getLastLineNum() - v2.getInfo().getFirstLineNum());
        }
        return v1.getNeighborDegreeSum() > v2.getNeighborDegreeSum(); // extends on the definition of "difficult-to-color vertex"
    }
    return v1.getDegree() > v2.getDegree();
}

int SpillingAlgorithm::execute(Graph &interferenceGraph, const int maxWebsToSpill, const int numColors) const {
    MutablePriorityQueue<Vertex> pq(spillingComp);
    int regsUsed = 0;

    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive()) pq.insert(vertex);
    }

    for (int spilledRegs = 1; spilledRegs <= maxWebsToSpill; spilledRegs++) {
        if (pq.empty()) break; // no more registers to spill, but still cannot color the graph with numColors
        Vertex* spilledReg = pq.extractMin(); // spill a register
        spilledReg->disable(); // disable the register node in the graph

        // update the priority queue
        for (const Edge* edge : spilledReg->getActiveAdj()) {
            Vertex* neighbor = edge->getDest();
            pq.decreaseKey(neighbor);
        }

        regsUsed = coloring_algorithm->execute(interferenceGraph, numColors);
        if (regsUsed) break; // was possible with 'spilledRegs' spilled registers
    }

    return regsUsed;
}
