// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#ifndef DA_SECOND_PROJECT_GRAPH_H
#define DA_SECOND_PROJECT_GRAPH_H

#include "allocation.h"

#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <map>

class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/
/**
 * @brief This class represents the vertices of the graph, which consists of a web.
 */
class Vertex {
public:
    /**
     * @brief Constructor of the Vertex class.
     * @param in The web that the vertex will represent.
     */
    explicit Vertex(Web in);

    /**
     *  @brief Function to get the web that the vertex represents.
     * @return The web that the vertex represents.
     */
    [[nodiscard]] Web getInfo() const;

    /**
     * @brief This function returns the list of outgoing edges of the vertex.
     * @return The list of outgoing edges of the vertex.
     */
    [[nodiscard]] std::vector<Edge *> getAdj() const;

    /**
     * @brief Function similar to the getAdj but filters webs that the spilled algorithm deactivated.
     * @return The list of outgoing edges of active vertex.
     * @par Complexity
     * Time: O(E)
     */
    [[nodiscard]] std::vector<Edge *> getActiveAdj() const;

    /**
     * @brief Function to get the degree of the vertex, which is the number of outgoing edges.
     * @return The degree of the vertex.
     */
    [[nodiscard]] unsigned int getDegree() const;

    /**
     * @brief Function to set the color of the vertex.
     * @param newColor The color to be assigned to the vertex.
     */
    void setColor(int newColor);

    /**
     * @brief Function that gets the color of the vertex
     * @return Returns the color of the vertex.
     */
    [[nodiscard]] int getColor() const;

    /**
     * @brief Function to set the index of the vertex in the mutable priority queue.
     * @param index The index the Vertex should be set to.
     */
    void setQueueIndex(int index);

    /**
     * @brief Function to get the index of the vertex in the mutable priority queue.
     * @return The idex of the vertex in the queue
     */
    [[nodiscard]] int getQueueIndex() const;

    /**
     * @brief Function to get the colors of the neighbors of the vertex.
     * @return The set of neighbor colors.
     */
    [[nodiscard]] std::set<int> getNeighborColors() const;

    /**
     * @brief Function that adds a given color to the set of neighbor colors.
     * @param newColor Color to add to the set.
     */
    void addColor(int newColor);

    /**
     * @brief Function that sums the degree of the neighbors of the vertex that are active.
     * @return Return the sum of active neighbor degrees.
     * @par Complexity
     * Time: O(E)
     */
    [[nodiscard]] int getNeighborDegreeSum() const;

    /**
     * @brief Function to add an outgoing edge to the vertex (this), with a given destination vertex (dest).
     * @param dest The destination vertex of the edge to be added.
     * @return Returns the edge that was added.
     */
    Edge* addEdge(Vertex *dest);

    /**
     * @brief Function to remove the edge from the vertex (this) to a given destination vertex (in).
     * @param in The destination vertex of the edge to be removed.
     * @return Returns true if the edge was successfully removed, and false if such edge does not exist.
     */
    bool removeEdge(const Web& in);

    /**
     * @brief This function removes all outgoing edges of the vertex.
     * It's used to remove all edges of a vertex when that vertex is removed from the graph.
     */
    void removeOutgoingEdges();

    /**
     * @brtief Function to set the vertex to not active and color -1. Which means the vertex, the web, was spilled and went to memory
     */
    void disable();

    /**
     * @brief Function to see if the vertex is active, which means it was not spilled and is still in the graph.
     * @return Returns true if the vertex is active, and false if it is not active (spilled).
     */
    [[nodiscard]] bool isActive() const;

protected:
    /**
     * @brief The information, the Web the vertex represents
     */
    Web info;

    /**
     * @brief The color of the vertex, if the color is -1 it means the vertex is in memory or not yet colored.
     */
    int color{};

    /**
     * @brief The index the vertex occupies in the mutable priority queue
     */
    int queueIndex = 0;

    /**
     * @brief The list of outgoing edges of the vertex.
     */
    std::vector<Edge *> adj;

    /**
     * @brief Set that has all the colors of the neighbors. It is used to simplify the coloring algorithm, since it can find out quickly which colors are already used by the neighbors and which are not, without having to iterate through all the neighbors and check their colors.
     */
    std::set<int> neighborColors;

    /**
     * @brief Boolean to indicate whether the vertex was spilled or not.
     */
    bool active = true;

    /**
     * @brief List of the incoming  edges of the vertex.
     */
    std::vector<Edge *> incoming;

    /**
     * @brief Private auxiliary function to delete a given edge of the vertex.
     * @param edge The edge to be deleted.
     */
    void deleteEdge(const Edge *edge) const;
};

/********************** Edge  ****************************/

/**
 * @brief This class repsents the Edges fo the graph, which consists of the origin vertex, origin vertex and the weight of the edge.
 */
class Edge {
public:
    /**
     * @brief Constructor of the Edge class.
     * @param orig The origin vertex of the edge.
     * @param dest The destination vertex of the edge.
     */
    Edge(Vertex *orig, Vertex *dest);

    /**
     * @brief Function to get the destination vertex of the edge.
     * @return The destination vertex of the edge.
     */
    [[nodiscard]] Vertex * getDest() const;

    /**
     * @brief Function to ge the origin vertex of the edge.
     * @return The origin vertex of the edge.
     */
    [[nodiscard]] Vertex * getOrig() const;

    void setReverse(Edge *reverseEdge);

protected:
    /**
     * @brief The destination vertex of the edge.
     */
    Vertex * dest;

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    /**
     * @brief The origin vertex of the edge.
     */
    Vertex *orig;


    Edge *reverse = nullptr;
};

/********************** Graph  ****************************/

/**
 * @brief Class that represents the graph, which consists of a set of vertices and edges. The vertices represent the webs and the edges represent the interference between the webs. The graph is initialized with an array of webs, which are used to create the vertices and the edges between them based on their interference.
 */
class Graph {
public:
    /**
     * @brief Constructor of the Graph class, which initializes the vertexSet with the webs passed as a parameters in an array and creates the edges between the webs that interfere with each other.
     * @param webs An array of webs, which will be the vertices of the graph, and for which the edges will be created based on their interference.
     */
    explicit Graph(const std::vector<Web>& webs);

    /**
     * @brief Destructor for Graph class.
     */
    ~Graph();

    /**
    * @brief Auxiliary function to find a vertex with a given the content.
    * @param in The content of the vertex to be found.
    * @return Returns a pointer to the vertex with the given content, or nullptr if such vertex does not exist in the graph.
    */
    [[nodiscard]] Vertex *findVertex(const Web &in) const;

    /**
     * @brief Function that Adds a vertex with a given content or info (in) to a graph (this).
     * @param in The Web, vertex, to be added to the Graph
     * @return Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(const Web &in);

    /**
     * @brief Function that removes a vertex with a given content (in) from a graph (this), and all outgoing and incoming edges.
     * @param in The Web, vertex, to be removed.
     * @return Return true if the vertex was successfully removed, and false if it wasn't.
     */
    bool removeVertex(const Web &in);

    /**
     * @brief Function that adds an edge between the source and destination.
     * @param source The source vertex of the edge.
     * @param dest The destination vertex of the edge
     * @return Returns true if successful, and false if it wasn't.
     */
    [[nodiscard]] bool addEdge(const Web &source, const Web &dest) const;

    /**
     * @brief Function to remove an edge from source to destination.
     * @param source The source vertex of the edge.
     * @param dest The destination vertex of the edge.
     * @return Returns true if the edge was successfully removed, and false if it wasn't.
     */
    [[nodiscard]] bool removeEdge(const Web &source, const Web &dest) const;

    /**
     * @brief Function that creates a bidirectional edge between the source and destination vertices.
     * @param source The source vertex of the edge.
     * @param dest The destination vertex of the edge.
     * @return Returns true if the edge was successfully added, and false if it wasn't.
     */
    [[nodiscard]] bool addBidirectionalEdge(const Web &source, const Web &dest) const;

    /**
     * @brief Function that goes through all nodes and colors them all to -1.
     * @par Complexity
     * Time: O(V)
     */
    void resetColors();

    /**
     * @brief Function to get the number of vertices in the graph.
     * @return The vector of vertices in the graph.
     */
    [[nodiscard]] std::vector<Vertex*> getVertexSet() const;

    /**
     * @brief Function that the returns the vector of webs in the graph.
     * @return The vector of webs in the graph.
     */
    [[nodiscard]] std::vector<Web> getWebs() const;

    /**
     * @brief Function that returns the number of spilled webs in the graph, which are the vertices that are not active and have color -1, that is, the vertices that wen to memory.
     * @return The number of spilled webs in the graph.
     */
    [[nodiscard]] int getSpilledWebsNumber() const;

    /**
     * @brief A map that keeps track of where each web were split (first) and the webs that it created (second). This map is used to help correctly display the output of the splitting algorithm, since it allows to know which webs were created from each original web and where they were split.
     */
    inline static std::map<Web, std::pair<std::pair<Line, Line>, std::pair<Web, Web>>> splitWebsMap;

    /**
     * @brief A function that returns the map that keeps track of where each web were split and the webs that it created.
     * @return The map that has that information.
     *
     */
    static std::map<Web, std::pair<std::pair<Line, Line>, std::pair<Web, Web>>> getSplitWebsMap();

    /**
     * @brief Function that adds the information of were it was split and the webs it created in the splitWebsMap.
     * @param web The web that was split.
     * @param splitWebs A pair were the first is a pair of were the web was split, and the second the pair of webs it created.
     */
    static void addSplitWebsToMap(const Web& web, const std::pair<std::pair<Line, Line>, std::pair<Web, Web>>& splitWebs);

private:
    /**
     * @brief A vector that has all the vertices of the graph.
     */
    std::vector<Vertex *> vertexSet;

    /**
     * @brief Original webs passed to the class constructor, from which the vertexSet is initialized and the edges are created based on their interference. This is attribute is useful for the splitting algorithm.
     */
    std::vector<Web> webs;

    /**
     * @brief Auxiliary function to create the edges between the vertices of the graph based on the interference of their corresponding webs. The algorithm used keeps an array of active webs, which are the ones that will interfere the current web in a given iteration through the vertexSet. The latter is initially sorted by the line number of the first line of the web.
     * @par Complexity
     * Time: O(V log V + k) where V is the number of vertices and k is the number of web interferences found (the number of edges that will be created). In the worst case, k can be O(V^2) if all webs interfere with each other.
     */
    void createEdges();
};

/************************* Vertex  **************************/

inline Vertex::Vertex(Web in): info(std::move(in)) {}

inline Edge * Vertex::addEdge(Vertex *d) {
    const auto newEdge = new Edge(this, d);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

inline bool Vertex::removeEdge(const Web& in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge *edge = *it;
        Vertex *dest = edge->getDest();
        if (dest->getInfo() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true;
        }
        else {
            ++it;
        }
    }
    return removedEdge;
}

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

inline void Vertex::setColor(const int newColor) {
    this->color = newColor;
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

inline void Vertex::setQueueIndex(const int index) {
    this->queueIndex = index;
}

inline int Vertex::getNeighborDegreeSum() const {
    int sum = 0;
    for (const Edge* edge : adj) {
        if (const Vertex* neighbor = edge->getDest(); neighbor->active) {
            sum += static_cast<int>(neighbor->getDegree());
        }
    }
    return sum;
}

inline void Vertex::addColor(const int newColor) {
    this->neighborColors.insert(newColor);
}

inline std::vector<Edge*> Vertex::getAdj() const {
    return this->adj;
}

inline std::vector<Edge*> Vertex::getActiveAdj() const {
    std::vector<Edge*> activeAdj;
    for (Edge* edge : adj) {
        if (edge->getDest()->isActive()) {
            activeAdj.push_back(edge);
        }
    }
    return activeAdj;
}

inline unsigned int Vertex::getDegree() const {
    return this->adj.size();
}

inline void Vertex::deleteEdge(const Edge *edge) const {
    Vertex *dest = edge->getDest();
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getInfo() == info) {
            it = dest->incoming.erase(it);
        }
        else {
            ++it;
        }
    }
    delete edge;
}

inline void Vertex::disable() {
    this->active = false;
    this->color = -1;
}

inline bool Vertex::isActive() const {
    return active;
}

/********************** Edge  ****************************/


inline Edge::Edge(Vertex *orig, Vertex *dest) : dest(dest), orig(orig) {}

inline Vertex * Edge::getDest() const {
    return this->dest;
}

inline Vertex * Edge::getOrig() const {
    return this->orig;
}

inline void Edge::setReverse(Edge *reverseEdge) {
    this->reverse = reverseEdge;
}

/********************** Graph  ****************************/


inline int Graph::getSpilledWebsNumber() const {
    int spilled = 0;
    for (const Vertex* vertex : vertexSet) {
        if (!vertex->isActive() && vertex->getColor() == -1) spilled++;
    }
    return spilled;
}

inline std::map<Web, std::pair<std::pair<Line, Line>, std::pair<Web, Web>>> Graph::getSplitWebsMap() {
    return splitWebsMap;
}

inline void Graph::addSplitWebsToMap(const Web& web, const std::pair<std::pair<Line, Line>, std::pair<Web, Web>>& splitWebs) {
    splitWebsMap[web] = splitWebs;
}

inline void Graph::createEdges() {
    // Create a vector of all webs, sorted by starting line number
    std::sort(vertexSet.begin(), vertexSet.end(), [] (const Vertex* v1, const Vertex* v2) {;
        return v1->getInfo().getFirstLineNum() < v2->getInfo().getFirstLineNum();
    });

    std::set<Web> activeWebs;

    for (const Vertex* vertex : vertexSet) {
        Web curWeb = vertex->getInfo();

        auto iter = activeWebs.begin();
        while (iter != activeWebs.end()) {
            if (curWeb.getFirstLineNum() >= iter->getLastLineNum()) {
                iter = activeWebs.erase(iter);
            } else {
                this->addBidirectionalEdge(curWeb, *iter);
                ++iter;
            }
        }
        activeWebs.insert(curWeb);
    }
}

inline Graph::Graph(const std::vector<Web>& webs) {
    this->webs = webs;
    for (const Web& web : webs) {
        this->addVertex(web);
    }
    createEdges(); // connect webs (vertices) that interfere with each other
}

inline std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

inline std::vector<Web> Graph::getWebs() const {
    return webs;
}

inline Vertex * Graph::findVertex(const Web &in) const {
    for (auto v : vertexSet)
        if (v->isActive() && v->getInfo() == in)
            return v;
    return nullptr;
}

inline bool Graph::addVertex(const Web &in) {
    if (findVertex(in) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(in));
    return true;
}

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

inline bool Graph::addEdge(const Web &source, const Web &dest) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2);
    return true;
}


inline bool Graph::removeEdge(const Web &source, const Web &dest) const {
    Vertex * srcVertex = findVertex(source);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}


inline bool Graph::addBidirectionalEdge(const Web &source, const Web &dest) const {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2);
    auto e2 = v2->addEdge(v1);
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
    // First, remove all outgoing edges from each vertex
    // This also cleans up incoming edges of other vertices
    for (const auto v : vertexSet) {
        v->removeOutgoingEdges();
    }
    // Then delete all vertex pointers
    for (const auto v : vertexSet) {
        delete v;
    }
    vertexSet.clear();
}

#endif //DA_SECOND_PROJECT_GRAPH_H