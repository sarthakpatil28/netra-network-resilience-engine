#ifndef NETRA_GRAPH_HPP
#define NETRA_GRAPH_HPP

#include <unordered_map>
#include <vector>




struct FailureReport {
    double healthBefore;
    double healthAfter;
    double healthImpact;
    int componentsBefore;
    int componentsAfter;
    bool connectedBefore;
    bool connectedAfter;
};



enum class FailureSeverity {
    LOW,
    MODERATE,
    HIGH,
    CRITICAL
};



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
    std::unordered_map<int, int> bfsDistances(int startNode) const;
    std::vector<int> shortestPath(int startNode, int targetNode) const;
    std::vector<int> resilientPath(int startNode, int destinationNode) const;


    int connectedComponents() const;
    bool isConnected() const;
    double networkHealthScore(int startNode) const;
    double healthImpact(double beforeScore, double afterScore) const;


    FailureReport analyzeFailure(int startNode) const;
    FailureReport analyzeLinkFailure(int startNode,int source,int destination) const;
    FailureReport analyzeNodeFailure(int startNode,int failedNode) const;

    FailureSeverity classifyFailure(const FailureReport& report) const;


    void display() const;
};

#endif