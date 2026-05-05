/*
 * UFDS.h
 * A simple implementation of Union-Find Disjoint Set (UFDS), required by Kruskal's algorithm.
 *
 * Created on: 25/01/2022
 *      Author: Gonçalo Leão
 */

#ifndef DA_SECOND_PROJECT_UFDS_H
#define DA_SECOND_PROJECT_UFDS_H

#include <vector>

/**
 * @brief The UFDS class implements the Union-Find Disjoint Set (UFDS) data structure, which is used to keep track of a set of elements partitioned into a number of disjoint subsets.
 */
class UFDS {
public:
    /**
     * @brief Constructor of the class, which initializes the path and rank vectors. In the beginning, all live ranges are in their own cluster and all ranks are 0.
     * @param N Number of live ranges (or number of clusters in the beginning)
     */
    explicit UFDS(unsigned int N);

    /**
     * @brief Returns the index of the parent live range of live range i (can either be itself or other live range). It also updates path[i] to point directly to the root of the tree / cluster, which is a path compression technique that optimizes future calls to findSet for this live range and all its children live ranges.
     * @param i
     * @return
     */
    unsigned long findSet(unsigned int i);

    /**
     * @brief Verifies if two live ranges i and j are in the same cluster.
     * @param i The index of the first live range
     * @param j The index of the second live range
     * @return Returns true if live ranges i and j are in the same cluster (i.e., have the same parent live range), and false otherwise.
     */
    bool isSameSet(unsigned int i, unsigned int j);

    /**
     * @brief Merges the clusters of live ranges i and j, by identifying the bigger and smaller clusters using the rank[] array, and then "moves" the elements of the smaller cluster to the bigger cluster (updates path[i] or path[j]). If both clusters have the same rank, it doesn't matter which one becomes the parent cluster, but in this case we need to update its rank by 1 (because we are adding a new level to the tree).
     * @param i The index of the first live range
     * @param j The index of the second live range
     */
    void linkSets(unsigned int i, unsigned int j);
private:
    /**
     * @brief path[i] is the index of the parent live range of live range i (can either be itself or other live range). It is used to identify which cluster a live range belongs to and to perform path compression in findSet function.
     */
    std::vector<unsigned int> path;

    /**
    * @brief rank[i] is the rank of the cluster whose root is live range i. It indicates the maximum height of the tree representing the cluster. It is used to identify which cluster is bigger and which is smaller when merging two clusters in linkSets function, helping optimize the merging process.
    */
    std::vector<unsigned int> rank;
};

#endif //DA_SECOND_PROJECT_UFDS_H