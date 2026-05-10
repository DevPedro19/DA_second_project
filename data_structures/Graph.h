// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#ifndef DA_SECOND_PROJECT_GRAPH_H
#define DA_SECOND_PROJECT_GRAPH_H

#include "allocation.h"

#include <algorithm>
#include <vector>

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/


class Vertex {
public:
    Vertex(Web in);

    Web getInfo() const;
    std::vector<Edge *> getAdj() const;
    std::vector<Edge *> getActiveAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getDegree() const;
    double getDist() const;
    Edge *getPath() const;
    std::vector<Edge *> getIncoming() const;

    void setColor(int color);
    void setQueueIndex(int index);
    void setInfo(Web info);
    void setVisited(bool visited);
    void setProcessing(bool processing);
    void setNum(int value);

    int getColor() const;
    std::set<int> getNeighborColors() const;
    int getNeighborDegreeSum() const; // adds complexity to the spilling algorithm
    int getQueueIndex() const;
    int getLow() const;
    void setLow(int value);
    int getNum() const;

    void setDist(double dist);
    void setPath(Edge *path);
    Edge * addEdge(Vertex *dest, double w);
    bool removeEdge(Web in);
    void removeOutgoingEdges();

    void disable();
    bool isActive() const;

protected:
    Web info;                // info node
    int color;               // color of the node
    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    std::vector<Edge *> adj;      // outgoing edges
    std::set<int> neighborColors; // the distinct colors of the vertex's neighbors

    // auxiliary fields
    bool active = true;
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    int low = -1, num = -1; // used by SCC Tarjan
    unsigned int degree{}; // used by topsort
    double dist = 0;
    Edge *path = nullptr;

    std::vector<Edge *> incoming; // incoming edges

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

    double flow{}; // for flow-related problems
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

    void resetColors();

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


inline Vertex::Vertex(Web in): info(in) {}
/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
inline Edge * Vertex::addEdge(Vertex *d, double w) {
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

inline bool Vertex::removeEdge(Web in) {
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
inline void Vertex::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}

inline Web Vertex::getInfo() const {
    return this->info;
}


inline int Vertex::getLow() const {
    return this->low;
}


inline void Vertex::setLow(int value) {
    this->low = value;
}


inline int Vertex::getNum() const {
    return this->num;
}


inline void Vertex::setColor(int color) {
    this->color = color;
}

inline int Vertex::getColor() const {
    return this->color;
}

inline std::set<int> Vertex::getNeighborColors() const {
    return this->neighborColors;
}

inline int Vertex::getQueueIndex() const {
    return this->queueIndex;
}

inline void Vertex::setQueueIndex(int index) {
    this->queueIndex = index;
}

inline int Vertex::getNeighborDegreeSum() const {
    int sum = 0;
    for (const Edge* edge : adj) {
        Vertex* neighbor = edge->getDest();

        if (neighbor->active) {
            sum += neighbor->getDegree();
        }
    }
    return sum;
}

inline void Vertex::setNum(int value) {
    this->num = value;
}


inline std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

// Time complexity: O(degree of the vertex)
inline std::vector<Edge*> Vertex::getActiveAdj() const {
    std::vector<Edge*> activeAdj;
    for (Edge* edge : adj) {
        if (edge->getDest()->isActive()) {
            activeAdj.push_back(edge);
        }
    }
    return activeAdj;
}

inline bool Vertex::isVisited() const {
    return this->visited;
}


inline bool Vertex::isProcessing() const {
    return this->processing;
}


inline unsigned int Vertex::getDegree() const {
    return this->adj.size();
}


inline double Vertex::getDist() const {
    return this->dist;
}


inline Edge *Vertex::getPath() const {
    return this->path;
}


inline std::vector<Edge *> Vertex::getIncoming() const {
    return this->incoming;
}


inline void Vertex::setInfo(Web in) {
    this->info = in;
}


inline void Vertex::setVisited(bool visited) {
    this->visited = visited;
}


inline void Vertex::setProcessing(bool processing) {
    this->processing = processing;
}

inline void Vertex::setDist(double dist) {
    this->dist = dist;
}


inline void Vertex::setPath(Edge *path) {
    this->path = path;
}


inline void Vertex::deleteEdge(Edge *edge) {
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

inline void Vertex::disable() {
    this->active = false;
}

inline bool Vertex::isActive() const {
    return active;
}

/********************** Edge  ****************************/


inline Edge::Edge(Vertex *orig, Vertex *dest, double w): orig(orig), dest(dest), weight(w) {}


inline Vertex * Edge::getDest() const {
    return this->dest;
}


inline double Edge::getWeight() const {
    return this->weight;
}


inline Vertex * Edge::getOrig() const {
    return this->orig;
}


inline Edge *Edge::getReverse() const {
    return this->reverse;
}


inline bool Edge::isSelected() const {
    return this->selected;
}


inline double Edge::getFlow() const {
    return flow;
}


inline void Edge::setSelected(bool selected) {
    this->selected = selected;
}


inline void Edge::setReverse(Edge *reverse) {
    this->reverse = reverse;
}


inline void Edge::setFlow(double flow) {
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


inline int Graph::getNumVertex() const {
    return vertexSet.size();
}


inline std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */

inline Vertex * Graph::findVertex(const Web &in) const {
    for (auto v : vertexSet)
        if (v->isActive() && v->getInfo() == in)
            return v;
    return nullptr;
}

/*
 * Finds the index of the vertex with a given content.
 */

inline int Graph::findVertexIdx(const Web &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getInfo() == in)
            return i;
    return -1;
}
/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

inline bool Graph::addVertex(const Web &in) {
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

inline bool Graph::removeVertex(const Web &in) {
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

inline bool Graph::addEdge(const Web &sourc, const Web &dest, double w) {
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

inline bool Graph::removeEdge(const Web &sourc, const Web &dest) {
    Vertex * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}


inline bool Graph::addBidirectionalEdge(const Web &sourc, const Web &dest, double w) {
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

inline void Graph::resetColors() {
    for (Vertex* vertex : vertexSet) {
        vertex->setColor(-1);
    }
}

inline Graph::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

#endif //DA_SECOND_PROJECT_GRAPH_H