#ifndef NETRA_GRAPH_HPP
#define NETRA_GRAPH_HPP

#include <unordered_map>
#include <vector>

class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

public:
    void addNode(int node);
    void addEdge(int source, int destination);

    void removeNode(int node);
    void removeEdge(int source, int destination);

    bool hasNode(int node) const;
    bool hasEdge(int source, int destination) const;

    std::vector<int> bfs(int startNode) const;

    void display() const;
};

#endif