#include "SpillingAlgorithm.h"

#include "../data_structures/MutablePriorityQueue.h"

SpillingAlgorithm::SpillingAlgorithm(const BasicAlgorithm &basicAlgorithm) : basicAlgorithm(basicAlgorithm) {}

// 1. Higher degree
// 2. Higher neighbor degree sum
// This criteria extends the definition of the "hardest node to color". Therefore, selecting the hardest node to color first potentially minimizes the number of colors needed.
bool SpillingAlgorithm::spillingComp(const Vertex& v1, const Vertex& v2) {
    if (v1.getDegree() == v2.getDegree()) {
        return v1.getNeighborDegreeSum() > v2.getNeighborDegreeSum(); // extends on the definition of "difficult-to-color vertex"
    }
    return v1.getDegree() > v2.getDegree();
}

// TODO: Describe the rationale you used in your algorithm implementation for the selection of which web(s) to spill
int SpillingAlgorithm::execute(Graph &interferenceGraph, int maxRegsToSpill, int numColors) {
    MutablePriorityQueue<Vertex> pq(spillingComp);
    int regsUsed = 0;

    for (Vertex* vertex : interferenceGraph.getVertexSet()) {
        if (vertex->isActive()) pq.insert(vertex);
    }

    for (int spilledRegs = 1; spilledRegs <= maxRegsToSpill; spilledRegs++) {
        Vertex* spilledReg = pq.extractMin(); // spill a register
        spilledReg->disable(); // disable the register node in the graph

        // update the priority queue
        for (Edge* edge : spilledReg->getActiveAdj()) {
            Vertex* neighbor = edge->getDest();
            pq.decreaseKey(neighbor);
        }

        regsUsed = this->basicAlgorithm.execute(interferenceGraph, numColors);
        if (regsUsed) break; // was possible with 'spilledRegs' spilled registers
    }

    return regsUsed;
}
