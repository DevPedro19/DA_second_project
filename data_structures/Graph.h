// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#ifndef DA_SECOND_PROJECT_GRAPH_H
#define DA_SECOND_PROJECT_GRAPH_H

#include <algorithm>

#include "allocation.h"

#include <iostream>
#include <vector>

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/


class Vertex {
public:
    Vertex(Web in);
    bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

    Web getInfo() const;
    std::vector<Edge *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setInfo(Web info);
    void setVisited(bool visited);
    void setProcessing(bool processing);

    int getLow() const;
    void setLow(int value);
    int getNum() const;
    void setNum(int value);

    void setIndegree(unsigned int indegree);
    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(Web in);
    void removeOutgoingEdges();

protected:
    Web info;                // info node
    std::vector<Edge *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    int low = -1, num = -1; // used by SCC Tarjan
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge *edge);
};

/********************** Edge  ****************************/


class Edge {
public:
    Edge(Vertex *orig, Vertex *dest, double w);

    Vertex * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex * getOrig() const;
    Edge *getReverse() const;
    double getFlow() const;

    void setSelected(bool selected);
    void setReverse(Edge *reverse);
    void setFlow(double flow);
protected:
    Vertex * dest; // destination vertex
    double weight; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Vertex *orig;
    Edge *reverse = nullptr;

    double flow; // for flow-related problems
};

/********************** Graph  ****************************/


class Graph {
public:
    /**
     * @brief Constructor of the Graph class, which initializes the vertexSet with the webs passed as a parameters in an array and creates the edges between the webs that interfere with each other.
     * @param webs An array of webs, which will be the vertices of the graph, and for which the edges will be created based on their interference.
     */
    explicit Graph(const std::vector<Web>& webs);

    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex *findVertex(const Web &in) const;
    /*
     *  Adds a vertex with a given content or info (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const Web &in);
    bool removeVertex(const Web &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const Web &sourc, const Web &dest, double w);
    bool removeEdge(const Web &source, const Web &dest);
    bool addBidirectionalEdge(const Web &sourc, const Web &dest, double w);

    int getNumVertex() const;
    std::vector<Vertex*> getVertexSet() const;

protected:

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const Web &in) const;

private:
    std::vector<Vertex *> vertexSet;    // vertex set

    /**
     * @brief Auxiliary function to create the edges between the vertices of the graph based on the interference of their corresponding webs. The algorithm used keeps an array of active webs, which are the ones that will interfere the current web in a given iteration through the vertexSet. The latter is initially sorted by the line number of the first line of the web.
     * @par Complexity
     * Time: O(V log V + k) where V is the number of vertices and k is the number of web interferences found (the number of edges that will be created). In the worst case, k can be O(V^2) if all webs interfere with each other.
     */
    void createEdges();
};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


/************************* Vertex  **************************/


Vertex::Vertex(Web in): info(in) {}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

Edge * Vertex::addEdge(Vertex *d, double w) {
    auto newEdge = new Edge(this, d, w);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

bool Vertex::removeEdge(Web in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */

void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}


bool Vertex::operator<(Vertex & vertex) const {
    return this->dist < vertex.dist;
}


Web Vertex::getInfo() const {
    return this->info;
}


int Vertex::getLow() const {
    return this->low;
}


void Vertex::setLow(int value) {
    this->low = value;
}


int Vertex::getNum() const {
    return this->num;
}


void Vertex::setNum(int value) {
    this->num = value;
}


std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}


bool Vertex::isVisited() const {
    return this->visited;
}


bool Vertex::isProcessing() const {
    return this->processing;
}


unsigned int Vertex::getIndegree() const {
    return this->indegree;
}


double Vertex::getDist() const {
    return this->dist;
}


Edge *Vertex::getPath() const {
    return this->path;
}


std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}


void Vertex::setInfo(Web in) {
    this->info = in;
}


void Vertex::setVisited(bool visited) {
    this->visited = visited;
}


void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}


void Vertex::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}


void Vertex::setDist(double dist) {
    this->dist = dist;
}


void Vertex::setPath(Edge *path) {
    this->path = path;
}


void Vertex::deleteEdge(Edge *edge) {
    Vertex *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

/********************** Edge  ****************************/


Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}


Vertex * Edge::getDest() const {
    return this->dest;
}


double Edge::getWeight() const {
    return this->weight;
}


Vertex * Edge::getOrig() const {
    return this->orig;
}


Edge *Edge::getReverse() const {
    return this->reverse;
}


bool Edge::isSelected() const {
    return this->selected;
}


double Edge::getFlow() const {
    return flow;
}


void Edge::setSelected(bool selected) {
    this->selected = selected;
}


void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}


void Edge::setFlow(double flow) {
    this->flow = flow;
}

/********************** Graph  ****************************/

inline void Graph::createEdges() {
    // Create a vector of all webs, sorted by starting line number
    std::sort(vertexSet.begin(), vertexSet.end(), [] (const Vertex* v1, const Vertex* v2) {;
        return v1->getInfo().getFirstLineNum() < v2->getInfo().getFirstLineNum();
    });

    std::set<Web> activeWebs; // A set to keep track of currently active webs (that will interfere with the current web being processed)

    for (const Vertex* vertex : vertexSet) {
        Web curWeb = vertex->getInfo();

        while (!activeWebs.empty() && activeWebs.begin()->getLastLineNum() <= curWeb.getFirstLineNum()) {
            // Remove webs that have ended, considering the beginning of the current web
            activeWebs.erase(activeWebs.begin());
        }

        // Iterate over activeWebs (which are the webs that are currently active in that line, meaning they will interfere)
        for (const Web& activeWeb : activeWebs) {
            this->addBidirectionalEdge(curWeb, activeWeb, 1);
        }
        activeWebs.insert(curWeb); // Add the current web to the active set, as its lines are now active
    }
}

inline Graph::Graph(const std::vector<Web>& webs) {
    for (const Web& web : webs) {
        this->addVertex(web);
    }
    createEdges(); // connect webs (vertices) that interfere with each other
}


int Graph::getNumVertex() const {
    return vertexSet.size();
}


std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

Vertex * Graph::findVertex(const Web &in) const {
    for (auto v : vertexSet)
        if (v->getInfo() == in)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */

int Graph::findVertexIdx(const Web &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addVertex(const Web &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */

bool Graph::removeVertex(const Web &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getInfo() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getInfo());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const Web &sourc, const Web &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, w);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */

bool Graph::removeEdge(const Web &sourc, const Web &dest) {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}


bool Graph::addBidirectionalEdge(const Web &sourc, const Web &dest, double w) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, w);
    auto e2 = v2->addEdge(v1, w);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}


Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

#endif //DA_SECOND_PROJECT_GRAPH_H