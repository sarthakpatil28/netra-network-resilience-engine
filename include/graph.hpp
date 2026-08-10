#ifndef NETRA_GRAPH_HPP
#define NETRA_GRAPH_HPP

#include <unordered_map>
#include <vector>
#include <string>



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



enum class FailureType {
    LINK,
    NODE
};



struct FailureEvent {
    FailureType type;
    int source;
    int destination;
};



struct RecoveryResult {
    bool recovered;
    std::vector<int> route;
};




struct RouteImpact {
    int originalHops;
    int recoveryHops;
    int additionalHops;
    bool routeChanged;
    bool recovered;
};




struct ResilienceScore {
    double score;
    bool recovered;
    bool connected;
    FailureSeverity severity;
};




struct MultiFailureReport {
    int totalFailures;
    int failedLinks;
    int failedNodes;
    bool connectedAfter;
    FailureSeverity severity;
};

struct ComponentRisk {
    FailureType type;
    int source;
    int destination;
    double riskScore;
    FailureSeverity severity;
};



struct NetworkStatistics {
    int nodes;
    int links;
    int connectedComponents;
    bool connected;

    double averageDegree;
    int minimumDegree;
    int maximumDegree;

    double density;

    int mostConnectedNode;
    int mostConnectedNodeDegree;
};




class Graph {
private:
    std::unordered_map<int, std::vector<int>> adjacencyList;

    // Stores the weight/cost of each undirected edge.
    std::unordered_map<int,
        std::unordered_map<int, double>> edgeWeights;

public:
    void addNode(int node);
    void addEdge(int source, int destination);

    void addWeightedEdge(
        int source,
        int destination,
        double weight
    );

    double getEdgeWeight(int source, int destination) const;



    void removeNode(int node);
    void removeEdge(int source, int destination);

    bool hasNode(int node) const;
    bool hasEdge(int source, int destination) const;

    std::vector<int> bfs(int startNode) const;
    std::unordered_map<int, int> bfsDistances(int startNode) const;
    std::vector<int> shortestPath(int startNode, int targetNode) const;
    std::vector<int> resilientPath(int startNode, int destinationNode) const;
    std::vector<int> weightedShortestPath(
    int startNode,
    int targetNode
) const;

    int connectedComponents() const;
    bool isConnected() const;
    double networkHealthScore(int startNode) const;
    double healthImpact(double beforeScore, double afterScore) const;


    FailureReport analyzeFailure(int startNode) const;
    FailureReport analyzeLinkFailure(int startNode,int source,int destination) const;
    FailureReport analyzeNodeFailure(int startNode,int failedNode) const;

    FailureSeverity classifyFailure(const FailureReport& report) const;
    FailureReport simulateFailure(int startNode,const FailureEvent& event) const;

        RecoveryResult recoverFromFailure(
        int startNode,
        int destinationNode,
        const FailureEvent& event
    ) const;

        RouteImpact analyzeRouteImpact(
        int startNode,
        int destinationNode,
        const FailureEvent& event
    ) const;


    ResilienceScore calculateResilienceScore(
        const FailureReport& report,
        const RouteImpact& impact
    ) const;



    MultiFailureReport analyzeMultipleFailures(
        const std::vector<FailureEvent>& events
    ) const;

    std::vector<ComponentRisk> analyzeComponentRisk(
        int startNode
    ) const;

    bool loadFromFile(const std::string& filename);

    NetworkStatistics getNetworkStatistics() const;

    void display() const;
    void displayTopology() const;
};

#endif