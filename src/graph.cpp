#include "graph.hpp" //this belongs to graph class
#include "network_adapter.hpp"
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>
#include <fstream>
#include <limits>
#include <functional>
#include <sstream>

void Graph::addNode(int node){
    if(adjacencyList.find(node) == adjacencyList.end()){//checking if the node already exists
        adjacencyList[node] = {}; //creating empty node
    }   
}



void Graph::addEdge(int source, int destination) {
   if(source == destination){
    return;
   }

    addNode(source);//checks if node alreay exist and if not then makes it to make the connection between them
    addNode(destination);

    if(std::find(adjacencyList[source].begin(),  adjacencyList[source].end(),  destination) !=  adjacencyList[source].end()){
        return;
    }

    adjacencyList[source].push_back(destination); //push_back means adding an element to the end of the vector which is a dynamic array
    adjacencyList[destination].push_back(source);
}



void Graph::addWeightedEdge(
                int source,
                int destination,
                double weight
            ) {
                // Reject self-loops.
                if (source == destination) {
                    return;
                }

                // Reject invalid weights.
                if (weight <= 0.0) {
                    return;
                }

                // Reuse existing graph logic.
                addEdge(source, destination);

                // Store the weight in both directions
                // because the graph is undirected.
                edgeWeights[source][destination] = weight;
                edgeWeights[destination][source] = weight;
            }




void Graph::removeEdge(int source, int destination) {

    // Check whether both nodes exist
    if (adjacencyList.find(source) == adjacencyList.end() ||
        adjacencyList.find(destination) == adjacencyList.end()) {
        return;
    }

    // Find destination in source's neighbour list
    auto sourceIt = std::find(
        adjacencyList[source].begin(),
        adjacencyList[source].end(),
        destination
    );

    // Remove destination from source's list
    if (sourceIt != adjacencyList[source].end()) {
        adjacencyList[source].erase(sourceIt);
    }

    // Find source in destination's neighbour list
    auto destinationIt = std::find(
        adjacencyList[destination].begin(),
        adjacencyList[destination].end(),
        source
    );

    // Remove source from destination's list
    if (destinationIt != adjacencyList[destination].end()) {
        adjacencyList[destination].erase(destinationIt);
    }
}




void Graph::removeNode(int node) {

    // Check if the node exists
    auto nodeIt = adjacencyList.find(node);

    if (nodeIt == adjacencyList.end()) {
        return;
    }

    // Make a copy of the node's neighbours
    auto neighbours = adjacencyList[node];

    // Remove this node from every neighbour's list
    for (int neighbour : neighbours) {

        auto neighbourIt = std::find(
            adjacencyList[neighbour].begin(),
            adjacencyList[neighbour].end(),
            node
        );

        if (neighbourIt != adjacencyList[neighbour].end()) {
            adjacencyList[neighbour].erase(neighbourIt);
        }
    }

    // Finally remove the node itself
    adjacencyList.erase(node);
}


//Checking if the node is present 
bool Graph::hasNode(int node) const {
    return adjacencyList.find(node) != adjacencyList.end();
}


//Checking if the edge/connection is present
bool Graph::hasEdge(int source, int destination) const {

    auto nodeIt = adjacencyList.find(source);

    if (nodeIt == adjacencyList.end()) {
        return false;
    }

    const auto& neighbours = nodeIt->second;//here & means dont make a copy search the existing vector

    return std::find(
        neighbours.begin(),
        neighbours.end(),
        destination
    ) != neighbours.end();
}




std::vector<int> Graph::bfs(int startNode) const {
    std::vector<int> result;

    if (!hasNode(startNode)) {
        return result;
    }

    std::queue<int> queue;
    std::unordered_set<int> visited;

    queue.push(startNode);
    visited.insert(startNode);

    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();

        result.push_back(currentNode);

        for (int neighbour : adjacencyList.at(currentNode)) {
            if (visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                queue.push(neighbour);
            }
        }
    }

    return result;
}




std::unordered_map<int, int> Graph::bfsDistances(int startNode) const {
    std::unordered_map<int, int> distances;
    std::queue<int> queue;

    if (!hasNode(startNode)) {
        return distances;
    }

    distances[startNode] = 0;
    queue.push(startNode);

    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();

        for (int neighbour : adjacencyList.at(currentNode)) {
            if (distances.find(neighbour) == distances.end()) {
                distances[neighbour] = distances[currentNode] + 1;
                queue.push(neighbour);
            }
        }
    }

    return distances;
}





std::vector<int> Graph::shortestPath(int startNode, int targetNode) const {
    std::vector<int> path;

    if (!hasNode(startNode) || !hasNode(targetNode)) { //checking if the nodes exist
        return path;
    }

    std::queue<int> queue;
    std::unordered_set<int> visited;
    std::unordered_map<int, int> parent;

    queue.push(startNode);
    visited.insert(startNode);

    while (!queue.empty()) {
        int currentNode = queue.front();
        queue.pop();

        if (currentNode == targetNode) {
            break;
        }

        for (int neighbour : adjacencyList.at(currentNode)) {
            if (visited.find(neighbour) == visited.end()) {
                visited.insert(neighbour);
                parent[neighbour] = currentNode;
                queue.push(neighbour);
            }
        }
    }

    if (startNode != targetNode &&
        parent.find(targetNode) == parent.end()) {
        return path;
    }

    int currentNode = targetNode;

    while (currentNode != startNode) {
        path.push_back(currentNode);
        currentNode = parent.at(currentNode);
    }

    path.push_back(startNode);

    std::reverse(path.begin(), path.end());

    return path;
}



std::vector<int> Graph::weightedShortestPath(
                    int startNode,
                    int targetNode
                ) const {

                    std::vector<int> path;

                    if (!hasNode(startNode) || !hasNode(targetNode)) {
                        return path;
                    }

                    const double INF =
                        std::numeric_limits<double>::infinity();

                    std::unordered_map<int, double> distance;
                    std::unordered_map<int, int> previous;

                    for (const auto& [node, neighbors] : adjacencyList) {
                        distance[node] = INF;
                    }

                    distance[startNode] = 0.0;

                    using State = std::pair<double, int>;

                    std::priority_queue<
                        State,
                        std::vector<State>,
                        std::greater<State>
                    > pq;

                    pq.push({0.0, startNode});

                    while (!pq.empty()) {

                        auto [currentDistance, currentNode] =
                            pq.top();

                        pq.pop();

                        if (currentDistance >
                            distance[currentNode]) {
                            continue;
                        }

                        if (currentNode == targetNode) {
                            break;
                        }

                        for (int neighbor :
                            adjacencyList.at(currentNode)) {

                            double weight =
                                getEdgeWeight(
                                    currentNode,
                                    neighbor
                                );

                            // If an edge has no explicit weight,
                            // treat it as weight 1.
                            if (weight < 0.0) {
                                weight = 1.0;
                            }

                            double newDistance =
                                currentDistance + weight;

                            if (newDistance <
                                distance[neighbor]) {

                                distance[neighbor] =
                                    newDistance;

                                previous[neighbor] =
                                    currentNode;

                                pq.push({
                                    newDistance,
                                    neighbor
                                });
                            }
                        }
                    }

                    // No path exists.
                    if (distance[targetNode] == INF) {
                        return path;
                    }

                    // Reconstruct path.
                    int current = targetNode;

                    while (true) {

                        path.push_back(current);

                        if (current == startNode) {
                            break;
                        }

                        auto it = previous.find(current);

                        if (it == previous.end()) {
                            path.clear();
                            return path;
                        }

                        current = it->second;
                    }

                    std::reverse(
                        path.begin(),
                        path.end()
                    );

                    return path;
                }




std::vector<int> Graph::resilientPath(int startNode,int destinationNode) const {

    std::vector<int> path = shortestPath(startNode, destinationNode);

    if (path.empty()) {
        return {};
    }

    // Verify that every consecutive pair is still connected.
    for (size_t i = 0; i + 1 < path.size(); ++i) {
        if (!hasEdge(path[i], path[i + 1])) {
            return {};
        }
    }

    return path;
}





void Graph::display() const{
    for(const auto& pair : adjacencyList){ // loop to go through every entry in out adjacencyList
       std::cout << pair.first << " -> "; // printing first node

       for(int neighbour : pair.second){ // going thorugh every neighbouring node
        std::cout << neighbour << " "; // printing neighouring nodes
       }
    
    std::cout << "\n";
    }
}

void Graph::displayTopology() const {

    std::cout << "\nNodes : "
              << adjacencyList.size()
              << "\n";

    int linkCount = 0;

    for (const auto& [source, neighbors] : adjacencyList) {
        for (int destination : neighbors) {

            // Undirected graph:
            // print each link only once.
            if (source < destination) {
                linkCount++;
            }
        }
    }

    std::cout << "Links : "
              << linkCount
              << "\n\n";

    if (adjacencyList.empty()) {
        std::cout << "Network is empty.\n";
        return;
    }

    std::cout << "Connected : "
          << (isConnected() ? "YES" : "NO")
          << "\n";

    std::cout << "Components : "
            << connectedComponents()
            << "\n\n";

    std::cout << "## Adjacency Topology\n\n";

    for (const auto& [source, neighbors] : adjacencyList) {

        for (int destination : neighbors) {

            // Skip the reverse copy of an undirected edge.
            if (source >= destination) {
                continue;
            }

            double weight =
                getEdgeWeight(source, destination);

            std::cout << "["
                      << source
                      << "] --(";

            if (weight > 0.0) {
                std::cout << weight;
            } else {
                std::cout << "1";
            }

            std::cout << ")-- ["
                      << destination
                      << "]\n";
        }
    }
}




int Graph::connectedComponents() const {
    std::unordered_set<int> visited;
    int components = 0;

    for (const auto& [node, neighbors] : adjacencyList) {
        if (visited.find(node) != visited.end()) {
            continue;
        }

        components++;

        std::vector<int> queue;
        queue.push_back(node);

        visited.insert(node);

        size_t index = 0;

        while (index < queue.size()) {
            int current = queue[index];
            index++;

            for (int neighbor : adjacencyList.at(current)) {
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    queue.push_back(neighbor);
                }
            }
        }
    }

    return components;
}







bool Graph::isConnected() const {
    if (adjacencyList.empty()) {
        return true;
    }

    int startNode = adjacencyList.begin()->first;

    std::vector<int> visited = bfs(startNode);

    return visited.size() == adjacencyList.size();
}





double Graph::networkHealthScore(int startNode) const {
    if (!hasNode(startNode)) {
        return 0.0;
    }

    std::vector<int> reachable = bfs(startNode);

    if (adjacencyList.empty()) {
        return 0.0;
    }

    double score =
        (static_cast<double>(reachable.size()) /
         static_cast<double>(adjacencyList.size())) * 100.0;

    return score;
}






double Graph::healthImpact(double beforeScore, double afterScore) const {
    return beforeScore - afterScore;
}




FailureReport Graph::analyzeFailure(int startNode) const {
    FailureReport report{};

    report.healthBefore = networkHealthScore(startNode);
    report.healthAfter = report.healthBefore;

    report.healthImpact = 0.0;

    report.componentsBefore = connectedComponents();
    report.componentsAfter = report.componentsBefore;

    report.connectedBefore = isConnected();
    report.connectedAfter = report.connectedBefore;

    return report;
}







FailureReport Graph::analyzeLinkFailure(
    int startNode,
    int source,
    int destination
) const {

    FailureReport report{};

    report.healthBefore = networkHealthScore(startNode);
    report.componentsBefore = connectedComponents();
    report.connectedBefore = isConnected();

    Graph failedNetwork = *this;

    failedNetwork.removeEdge(source, destination);

    report.healthAfter =
        failedNetwork.networkHealthScore(startNode);

    report.componentsAfter =
        failedNetwork.connectedComponents();

    report.connectedAfter =
        failedNetwork.isConnected();

    report.healthImpact =
        healthImpact(report.healthBefore, report.healthAfter);

    return report;
}






FailureReport Graph::analyzeNodeFailure(
    int startNode,
    int failedNode
) const {

    FailureReport report{};

    report.healthBefore = networkHealthScore(startNode);
    report.componentsBefore = connectedComponents();
    report.connectedBefore = isConnected();

    Graph failedNetwork = *this;

    failedNetwork.removeNode(failedNode);

    report.healthAfter =
        failedNetwork.networkHealthScore(startNode);

    report.componentsAfter =
        failedNetwork.connectedComponents();

    report.connectedAfter =
        failedNetwork.isConnected();

    report.healthImpact =
        healthImpact(report.healthBefore, report.healthAfter);

    return report;
}







FailureSeverity Graph::classifyFailure(
    const FailureReport& report
) const {

    if (report.healthImpact <= 0.0 &&
        report.connectedAfter) {
        return FailureSeverity::LOW;
    }

    if (report.connectedAfter &&
        report.healthImpact <= 25.0) {
        return FailureSeverity::MODERATE;
    }

    if (!report.connectedAfter &&
        report.healthImpact <= 50.0) {
        return FailureSeverity::HIGH;
    }

    return FailureSeverity::CRITICAL;
}





FailureReport Graph::simulateFailure(
    int startNode,
    const FailureEvent& event
) const {

    if (event.type == FailureType::LINK) {
        return analyzeLinkFailure(
            startNode,
            event.source,
            event.destination
        );
    }

    if (event.type == FailureType::NODE) {
        return analyzeNodeFailure(
            startNode,
            event.source
        );
    }

    return analyzeFailure(startNode);
}






RecoveryResult Graph::recoverFromFailure(
    int startNode,
    int destinationNode,
    const FailureEvent& event
) const {

    Graph failedNetwork = *this;

    if (event.type == FailureType::LINK) {
        failedNetwork.removeEdge(
            event.source,
            event.destination
        );
    }
    else if (event.type == FailureType::NODE) {
        failedNetwork.removeNode(event.source);
    }

    std::vector<int> route =
        failedNetwork.shortestPath(
            startNode,
            destinationNode
        );

    if (route.empty()) {
        return {false, {}};
    }

    return {true, route};
}








RouteImpact Graph::analyzeRouteImpact(
    int startNode,
    int destinationNode,
    const FailureEvent& event
) const {

    std::vector<int> originalRoute =
        shortestPath(startNode, destinationNode);

    RecoveryResult recovery =
        recoverFromFailure(
            startNode,
            destinationNode,
            event
        );

    if (originalRoute.empty()) {
        return {0, 0, 0, false, false};
    }

    if (!recovery.recovered) {
            return {
            static_cast<int>(originalRoute.size()) - 1,
            0,
            0,
            true,
            false
        };
    }

    int originalHops =
        static_cast<int>(originalRoute.size()) - 1;

    int recoveryHops =
        static_cast<int>(recovery.route.size()) - 1;

    int additionalHops =
        recoveryHops - originalHops;

    bool routeChanged =
        originalRoute != recovery.route;

        return {
            originalHops,
            recoveryHops,
            additionalHops,
            routeChanged,
            true
        };
}





ResilienceScore Graph::calculateResilienceScore(
    const FailureReport& report,
    const RouteImpact& impact
) const {

    double score = 100.0;

    score -= report.healthImpact * 0.5;

    if (!report.connectedAfter) {
        score -= 30.0;
    }

    if (!impact.recovered) {
        score -= 40.0;
    }
    else if (impact.additionalHops > 0) {
        score -= impact.additionalHops * 5.0;
    }

    if (score < 0.0) {
        score = 0.0;
    }

    if (score > 100.0) {
        score = 100.0;
    }

    return {
        score,
        impact.recovered,
        report.connectedAfter,
        classifyFailure(report)
    };
}







MultiFailureReport Graph::analyzeMultipleFailures(
    const std::vector<FailureEvent>& events
) const {

    MultiFailureReport report{
        static_cast<int>(events.size()),
        0,
        0,
        true,
        FailureSeverity::LOW
    };
    Graph simulated = *this;

    for (const auto& event : events) {

        if (event.type == FailureType::LINK) {
            ++report.failedLinks;

            if (simulated.hasEdge(event.source, event.destination)) {
                simulated.removeEdge(
                    event.source,
                    event.destination
                );
            }
        }
        else if (event.type == FailureType::NODE) {
            ++report.failedNodes;

           if (simulated.hasNode(event.source)) {
                simulated.removeNode(event.source);
            }
        }
    }

    report.connectedAfter =
        simulated.isConnected();


    if (!report.connectedAfter) {
    report.severity = FailureSeverity::CRITICAL;
    }
    else if (report.failedNodes >= 2 || report.totalFailures >= 4) {
        report.severity = FailureSeverity::HIGH;
    }
    else if (report.totalFailures >= 2) {
        report.severity = FailureSeverity::MODERATE;
    }
    else {
        report.severity = FailureSeverity::LOW;
    }



    return report;
}






    

std::vector<ComponentRisk>
Graph::analyzeComponentRisk(
    int startNode
) const {

    std::vector<ComponentRisk> risks;

    if (!hasNode(startNode)) {
        return risks;
    }

    /*
     * Component Risk Model
     *
     * Risk is based on:
     *
     * 1. Connectivity impact
     * 2. Reachability / health impact
     * 3. Loss of alternate paths
     *
     * A component that does not disconnect the network can
     * still be important if its removal reduces redundancy.
     */

    int originalComponents = connectedComponents();
    int originalNodes =
        static_cast<int>(adjacencyList.size());

    /*
     * ---------------------------------------------------------
     * NODE FAILURE ANALYSIS
     * ---------------------------------------------------------
     */

    for (const auto& [node, neighbors] : adjacencyList) {

        // Do not analyze the observation/start node.
        if (node == startNode) {
            continue;
        }

        Graph failedNetwork = *this;
        failedNetwork.removeNode(node);

        int failedComponents =
            failedNetwork.connectedComponents();

        double healthBefore =
            networkHealthScore(startNode);

        double healthAfter =
            failedNetwork.networkHealthScore(startNode);

        double healthLoss =
            healthBefore - healthAfter;

        /*
         * Connectivity impact.
         *
         * If the number of connected components increases,
         * the component was structurally important.
         */
        double connectivityRisk = 0.0;

        if (failedComponents > originalComponents) {

            int increase =
                failedComponents - originalComponents;

            connectivityRisk =
                std::min(
                    100.0,
                    static_cast<double>(increase) * 50.0
                );
        }

        /*
         * Reachability impact.
         */
        double healthRisk =
            std::max(0.0, healthLoss);

        /*
         * Degree-based importance.
         *
         * Higher-degree nodes participate in more links
         * and therefore have greater potential impact.
         */
        double degreeRisk = 0.0;

        if (originalNodes > 1) {

            degreeRisk =
                (static_cast<double>(neighbors.size()) /
                 static_cast<double>(originalNodes - 1))
                * 30.0;
        }

        /*
         * Combined risk.
         */
        double riskScore =
            std::min(
                100.0,
                healthRisk * 0.50 +
                connectivityRisk * 0.35 +
                degreeRisk * 0.15
            );

        FailureEvent event{
            FailureType::NODE,
            node,
            -1
        };

        FailureReport report =
            simulateFailure(
                startNode,
                event
            );

        /*
         * If the node actually disconnects the network,
         * ensure it receives at least HIGH severity.
         */
        FailureSeverity severity =
            classifyFailure(report);

        if (failedComponents > originalComponents &&
            severity == FailureSeverity::LOW) {

            severity = FailureSeverity::HIGH;
        }

        risks.push_back({
            FailureType::NODE,
            node,
            -1,
            riskScore,
            severity
        });
    }


    /*
     * ---------------------------------------------------------
     * LINK FAILURE ANALYSIS
     * ---------------------------------------------------------
     */

    for (const auto& [source, neighbors] : adjacencyList) {

        for (int destination : neighbors) {

            /*
             * Undirected graph:
             * analyze each link only once.
             */
            if (source >= destination) {
                continue;
            }

            Graph failedNetwork = *this;

            failedNetwork.removeEdge(
                source,
                destination
            );

            int failedComponents =
                failedNetwork.connectedComponents();

            double healthBefore =
                networkHealthScore(startNode);

            double healthAfter =
                failedNetwork.networkHealthScore(startNode);

            double healthLoss =
                healthBefore - healthAfter;

            /*
             * Connectivity risk.
             */
            double connectivityRisk = 0.0;

            if (failedComponents > originalComponents) {

                int increase =
                    failedComponents - originalComponents;

                connectivityRisk =
                    std::min(
                        100.0,
                        static_cast<double>(increase) * 70.0
                    );
            }

            /*
             * Health/reachability risk.
             */
            double healthRisk =
                std::max(0.0, healthLoss);

            /*
             * Link redundancy analysis.
             *
             * Temporarily remove the link and check whether
             * its endpoints still have alternative connectivity.
             */
            std::vector<int> alternatePath =
                failedNetwork.shortestPath(
                    source,
                    destination
                );

            double redundancyRisk = 0.0;

            if (alternatePath.empty()) {

                // No alternate path -> very important link.
                redundancyRisk = 100.0;

            } else {

                /*
                 * An alternate path exists.
                 * Longer alternate paths imply weaker redundancy.
                 */
                int alternateHops =
                    static_cast<int>(
                        alternatePath.size()
                    ) - 1;

                if (alternateHops <= 1) {
                    redundancyRisk = 5.0;
                }
                else if (alternateHops == 2) {
                    redundancyRisk = 15.0;
                }
                else if (alternateHops == 3) {
                    redundancyRisk = 25.0;
                }
                else {
                    redundancyRisk =
                        std::min(
                            60.0,
                            25.0 +
                            alternateHops * 5.0
                        );
                }
            }

            /*
             * Combined link risk.
             */
            double riskScore =
                std::min(
                    100.0,
                    healthRisk * 0.45 +
                    connectivityRisk * 0.40 +
                    redundancyRisk * 0.15
                );

            FailureEvent event{
                FailureType::LINK,
                source,
                destination
            };

            FailureReport report =
                simulateFailure(
                    startNode,
                    event
                );

            FailureSeverity severity =
                classifyFailure(report);

            if (failedComponents > originalComponents &&
                severity == FailureSeverity::LOW) {

                severity = FailureSeverity::HIGH;
            }

            risks.push_back({
                FailureType::LINK,
                source,
                destination,
                riskScore,
                severity
            });
        }
    }


    /*
     * Highest-risk components first.
     */
    std::sort(
        risks.begin(),
        risks.end(),
        [](const ComponentRisk& a,
           const ComponentRisk& b) {

            if (a.riskScore != b.riskScore) {
                return a.riskScore > b.riskScore;
            }

            /*
             * If two components have equal risk,
             * keep NODE before LINK for readability.
             */
            if (a.type != b.type) {
                return a.type == FailureType::NODE;
            }

            return a.source < b.source;
        }
    );

    return risks;
}  




bool Graph::loadFromFile(const std::string& filename) {

    std::ifstream file(filename);

    if (!file.is_open()) {
        return false;
    }

    Graph tempGraph;

    std::string line;
    bool hasData = false;

    while (std::getline(file, line)) {

        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);

        int source;
        int destination;

        // Source must be an integer
        if (!(ss >> source)) {
            return false;
        }

        // Destination must be an integer
        if (!(ss >> destination)) {
            return false;
        }

       
        // Node IDs must be positive.
        if (source <= 0 || destination <= 0) {
            return false;
        }

        // Reject self-loop
        if (source == destination) {
            return false;
        }



        hasData = true;

        // Read the remainder of the line
        std::string remaining;

        if (ss >> remaining) {

            // The third token must be a valid positive number.
            try {

                size_t position = 0;

                double weight =
                    std::stod(remaining, &position);

                // Make sure the entire token was numeric.
                if (position != remaining.size()) {
                    return false;
                }

                if (weight <= 0.0) {
                    return false;
                }

                tempGraph.addWeightedEdge(
                    source,
                    destination,
                    weight
                );

            }
            catch (...) {
                return false;
            }

            // No fourth token allowed.
            std::string extra;

            if (ss >> extra) {
                return false;
            }

        } else {

            // Only source + destination.
            tempGraph.addEdge(
                source,
                destination
            );
        }
    }

    if (!hasData) {
        return false;
    }

    adjacencyList = tempGraph.adjacencyList;
    edgeWeights = tempGraph.edgeWeights;

    return true;
}







NetworkStatistics Graph::getNetworkStatistics() const {

    NetworkStatistics stats{};

    // Number of nodes
    stats.nodes = static_cast<int>(adjacencyList.size());

    // Empty network
    if (stats.nodes == 0) {
        stats.links = 0;
        stats.connectedComponents = 0;
        stats.connected = false;
        stats.averageDegree = 0.0;
        stats.minimumDegree = 0;
        stats.maximumDegree = 0;
        stats.density = 0.0;
        stats.mostConnectedNode = -1;
        stats.mostConnectedNodeDegree = 0;

        return stats;
    }

    // Calculate degree information
    int totalDegree = 0;

    stats.minimumDegree = std::numeric_limits<int>::max();
    stats.maximumDegree = 0;
    stats.mostConnectedNode = -1;
    stats.mostConnectedNodeDegree = 0;

    for (const auto& [node, neighbors] : adjacencyList) {

        int degree =
            static_cast<int>(neighbors.size());

        totalDegree += degree;

        stats.minimumDegree =
            std::min(stats.minimumDegree, degree);

        stats.maximumDegree =
            std::max(stats.maximumDegree, degree);

        if (degree > stats.mostConnectedNodeDegree) {
            stats.mostConnectedNodeDegree = degree;
            stats.mostConnectedNode = node;
        }
    }

    // Every undirected edge appears twice
    // in the adjacency list.
    stats.links = totalDegree / 2;

    stats.averageDegree =
        static_cast<double>(totalDegree) /
        stats.nodes;

    // Undirected graph density:
    //
    // density = 2E / (V(V-1))
    //
    if (stats.nodes > 1) {
        stats.density =
            (2.0 * stats.links) /
            (static_cast<double>(stats.nodes) *
             (stats.nodes - 1));
    } else {
        stats.density = 0.0;
    }

    stats.connectedComponents =
        connectedComponents();

    stats.connected =
        isConnected();

    return stats;
}




double Graph::getEdgeWeight(
    int source,
    int destination
) const {
    auto sourceIt = edgeWeights.find(source);

    if (sourceIt == edgeWeights.end()) {
        return -1.0;
    }

    auto destinationIt =
        sourceIt->second.find(destination);

    if (destinationIt == sourceIt->second.end()) {
        return -1.0;
    }

    return destinationIt->second;
}