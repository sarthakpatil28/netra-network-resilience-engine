

#include "graph.hpp"
#include "network_adapter.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>



void printIncidentReport(
    const FailureEvent& event,
    const std::vector<int>& originalRoute,
    const RecoveryResult& recovery,
    const RouteImpact& impact,
    const FailureReport& report,
    const ResilienceScore& resilience
) {
    std::cout << "\n";
    std::cout << "============================================================\n";
    std::cout << "                 NETRA INCIDENT REPORT\n";
    std::cout << "============================================================\n";

    std::cout << "Failure Type        : "
              << (event.type == FailureType::LINK ? "LINK FAILURE" : "NODE FAILURE")
              << "\n";

    if (event.type == FailureType::LINK) {
        std::cout << "Failed Component    : Link "
                  << event.source
                  << " - "
                  << event.destination
                  << "\n";
    } else {
        std::cout << "Failed Component    : Node "
                  << event.source
                  << "\n";
    }

    std::cout << "------------------------------------------------------------\n";

    std::cout << "ORIGINAL ROUTE\n";
    std::cout << "Route               : ";

    for (std::size_t i = 0; i < originalRoute.size(); ++i) {
        std::cout << originalRoute[i];

        if (i + 1 < originalRoute.size()) {
            std::cout << " -> ";
        }
    }

    std::cout << "\n";
    std::cout << "Hops                : "
              << impact.originalHops
              << "\n";

    std::cout << "------------------------------------------------------------\n";

    std::cout << "RECOVERY\n";

    std::cout << "Status              : "
              << (recovery.recovered ? "SUCCESS" : "FAILED")
              << "\n";

    if (recovery.recovered) {

        std::cout << "Recovery Route      : ";

        for (std::size_t i = 0; i < recovery.route.size(); ++i) {
            std::cout << recovery.route[i];

            if (i + 1 < recovery.route.size()) {
                std::cout << " -> ";
            }
        }

        std::cout << "\n";
    }

    std::cout << "Recovery Hops       : "
              << impact.recoveryHops
              << "\n";

    std::cout << "Additional Hops     : "
              << impact.additionalHops
              << "\n";

    std::cout << "Route Changed       : "
              << (impact.routeChanged ? "YES" : "NO")
              << "\n";

    std::cout << "------------------------------------------------------------\n";

    std::cout << "NETWORK IMPACT\n";

    std::cout << "Health Before      : "
              << report.healthBefore
              << "\n";

    std::cout << "Health After       : "
              << report.healthAfter
              << "\n";

    std::cout << "Health Impact      : "
              << report.healthImpact
              << "\n";

    std::cout << "Connected Before   : "
              << (report.connectedBefore ? "YES" : "NO")
              << "\n";

    std::cout << "Connected After    : "
              << (report.connectedAfter ? "YES" : "NO")
              << "\n";

    std::cout << "------------------------------------------------------------\n";

    std::cout << "RESILIENCE\n";

    std::cout << "Resilience Score   : "
              << resilience.score
              << "\n";

    std::cout << "Severity           : ";

            switch (resilience.severity) {
                case FailureSeverity::LOW:
                    std::cout << "LOW";
                    break;

                case FailureSeverity::MODERATE:
                    std::cout << "MODERATE";
                    break;

                case FailureSeverity::HIGH:
                    std::cout << "HIGH";
                    break;

                case FailureSeverity::CRITICAL:
                    std::cout << "CRITICAL";
                    break;
            }

            std::cout << "\n";

    std::cout << "Recovery           : "
              << (resilience.recovered ? "SUCCESS" : "FAILED")
              << "\n";

    std::cout << "Network Connected  : "
              << (resilience.connected ? "YES" : "NO")
              << "\n";

    std::cout << "============================================================\n";
}




void printMenu() {
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "              NETRA CLI\n";
    std::cout << "   Network Resilience & Threat Analysis\n";
    std::cout << "========================================\n";
    std::cout << "1. Add link\n";
    std::cout << "2. Remove link\n";
    std::cout << "3. Remove node\n";
    std::cout << "4. Show network\n";
    std::cout << "5. Find shortest path\n";
    std::cout << "6. Find resilient path\n";
    std::cout << "7. Analyze link failure\n";
    std::cout << "8. Analyze node failure\n";
    std::cout << "9. Analyze multiple failures\n";
    std::cout << "10. Simulate failure & analyze recovery\n";
    std::cout << "11. Network Health Dashboard\n";
    std::cout << "12. Component Risk Analysis\n";
    std::cout << "13. Load Network From File\n";
    std::cout << "14. Network Statistics\n";
    std::cout << "15. Network Topology\n";
    std::cout << "16. Find weighted shortest path\n";
    std::cout << "17. Exit\n";
    std::cout << "========================================\n";
    std::cout << "Enter choice: ";
}

std::string severityToString(FailureSeverity severity) {
    switch (severity) {
        case FailureSeverity::LOW:
            return "LOW";

        case FailureSeverity::MODERATE:
            return "MODERATE";

        case FailureSeverity::HIGH:
            return "HIGH";

        case FailureSeverity::CRITICAL:
            return "CRITICAL";
    }

    return "UNKNOWN";
}

void printFailureReport(const FailureReport& report) {

    std::cout << "\n========== FAILURE REPORT ==========\n";

    std::cout << "Health before : "
              << report.healthBefore << "\n";

    std::cout << "Health after  : "
              << report.healthAfter << "\n";

    std::cout << "Health impact : "
              << report.healthImpact << "\n";

    std::cout << "Components before : "
              << report.componentsBefore << "\n";

    std::cout << "Components after  : "
              << report.componentsAfter << "\n";

    std::cout << "Connected before : "
              << (report.connectedBefore ? "YES" : "NO")
              << "\n";

    std::cout << "Connected after  : "
              << (report.connectedAfter ? "YES" : "NO")
              << "\n";

    std::cout << "====================================\n";
}

int main() {

    Graph network;

    while (true) {

        printMenu();

        int choice;
        std::cin >> choice;

        if (!std::cin) {

            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n'
            );

            std::cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {

            // ==========================================
            // ADD LINK
            // ==========================================

            case 1: {

                int source;
                int destination;

                std::cout << "Enter source node: ";
                std::cin >> source;

                std::cout << "Enter destination node: ";
                std::cin >> destination;

                network.addEdge(source, destination);

                std::cout << "Link added.\n";

                break;
            }

            // ==========================================
            // REMOVE LINK
            // ==========================================

            case 2: {

                int source;
                int destination;

                std::cout << "Enter source node: ";
                std::cin >> source;

                std::cout << "Enter destination node: ";
                std::cin >> destination;

                network.removeEdge(source, destination);

                std::cout << "Link removed.\n";

                break;
            }

            // ==========================================
            // REMOVE NODE
            // ==========================================

            case 3: {

                int node;

                std::cout << "Enter node to remove: ";
                std::cin >> node;

                network.removeNode(node);

                std::cout << "Node removed.\n";

                break;
            }

            // ==========================================
            // SHOW NETWORK
            // ==========================================

            case 4: {

                std::cout << "\nCurrent network:\n";

                network.display();

                break;
            }

            // ==========================================
            // SHORTEST PATH
            // ==========================================

            case 5: {

                int source;
                int destination;

                std::cout << "Enter source node: ";
                std::cin >> source;

                std::cout << "Enter destination node: ";
                std::cin >> destination;

                auto path =
                    network.shortestPath(source, destination);

                if (path.empty()) {

                    std::cout << "No path available.\n";

                } else {

                    std::cout << "Shortest path: ";

                    for (int node : path) {
                        std::cout << node << " ";
                    }

                    std::cout << "\n";
                }

                break;
            }

            // ==========================================
            // RESILIENT PATH
            // ==========================================

            case 6: {

                int source;
                int destination;

                std::cout << "Enter source node: ";
                std::cin >> source;

                std::cout << "Enter destination node: ";
                std::cin >> destination;

                auto path =
                    network.resilientPath(source, destination);

                if (path.empty()) {

                    std::cout
                        << "No resilient route available.\n";

                } else {

                    std::cout << "Resilient path: ";

                    for (int node : path) {
                        std::cout << node << " ";
                    }

                    std::cout << "\n";
                }

                break;
            }

            // ==========================================
            // LINK FAILURE
            // ==========================================

            case 7: {

                int startNode;
                int source;
                int destination;

                std::cout << "Enter analysis start node: ";
                std::cin >> startNode;

                std::cout << "Enter failed link source: ";
                std::cin >> source;

                std::cout << "Enter failed link destination: ";
                std::cin >> destination;

                FailureEvent event{
                    FailureType::LINK,
                    source,
                    destination
                };

                auto report =
                    network.simulateFailure(
                        startNode,
                        event
                    );

                printFailureReport(report);

                auto severity =
                    network.classifyFailure(report);

                std::cout << "Failure severity: "
                          << severityToString(severity)
                          << "\n";

                break;
            }

            // ==========================================
            // NODE FAILURE
            // ==========================================

            case 8: {

                int startNode;
                int failedNode;

                std::cout << "Enter analysis start node: ";
                std::cin >> startNode;

                std::cout << "Enter failed node: ";
                std::cin >> failedNode;

                FailureEvent event{
                    FailureType::NODE,
                    failedNode,
                    0
                };

                auto report =
                    network.simulateFailure(
                        startNode,
                        event
                    );

                printFailureReport(report);

                auto severity =
                    network.classifyFailure(report);

                std::cout << "Failure severity: "
                          << severityToString(severity)
                          << "\n";

                break;
            }

            // ==========================================
            // MULTIPLE FAILURES
            // ==========================================

            case 9: {

                int count;

                std::cout << "Enter number of failures: ";
                std::cin >> count;

                if (count <= 0) {

                    std::cout
                        << "Number of failures must be positive.\n";

                    break;
                }

                std::vector<FailureEvent> events;

                for (int i = 0; i < count; ++i) {

                    int type;

                    std::cout << "\nFailure "
                              << (i + 1)
                              << "\n";

                    std::cout
                        << "1. Link failure\n";

                    std::cout
                        << "2. Node failure\n";

                    std::cout
                        << "Enter failure type: ";

                    std::cin >> type;

                    if (type == 1) {

                        int source;
                        int destination;

                        std::cout
                            << "Enter link source: ";

                        std::cin >> source;

                        std::cout
                            << "Enter link destination: ";

                        std::cin >> destination;

                        events.push_back({
                            FailureType::LINK,
                            source,
                            destination
                        });

                    } else if (type == 2) {

                        int node;

                        std::cout
                            << "Enter failed node: ";

                        std::cin >> node;

                        events.push_back({
                            FailureType::NODE,
                            node,
                            0
                        });

                    } else {

                        std::cout
                            << "Invalid failure type.\n";

                        --i;
                    }
                }

                auto report =
                    network.analyzeMultipleFailures(events);

                std::cout
                    << "\n====== MULTIPLE FAILURE REPORT ======\n";

                std::cout
                    << "Total failures : "
                    << report.totalFailures
                    << "\n";

                std::cout
                    << "Failed links   : "
                    << report.failedLinks
                    << "\n";

                std::cout
                    << "Failed nodes   : "
                    << report.failedNodes
                    << "\n";

                std::cout
                    << "Connected after failures : "
                    << (report.connectedAfter
                            ? "YES"
                            : "NO")
                    << "\n";

                std::cout
                    << "Combined severity : "
                    << severityToString(report.severity)
                    << "\n";

                std::cout
                    << "=====================================\n";

                break;
            }


            case 10: {

                int startNode;
                int destinationNode;
                int failureType;

                std::cout << "Enter source node: ";
                std::cin >> startNode;

                std::cout << "Enter destination node: ";
                std::cin >> destinationNode;

                std::cout << "\nFailure type:\n";
                std::cout << "1. Link failure\n";
                std::cout << "2. Node failure\n";
                std::cout << "Enter failure type: ";
                std::cin >> failureType;

                FailureEvent event{};

                if (failureType == 1) {

                    int source;
                    int destination;

                    std::cout << "Enter failed link source: ";
                    std::cin >> source;

                    std::cout << "Enter failed link destination: ";
                    std::cin >> destination;

                    event = {
                        FailureType::LINK,
                        source,
                        destination
                    };

                }
                else if (failureType == 2) {

                    int failedNode;

                    std::cout << "Enter failed node: ";
                    std::cin >> failedNode;

                    event = {
                        FailureType::NODE,
                        failedNode,
                        0
                    };

                }
                else {

                    std::cout << "Invalid failure type.\n";
                    break;
                }

                // ------------------------------------------
                // Original route
                // ------------------------------------------

                auto originalRoute =
                    network.shortestPath(
                        startNode,
                        destinationNode
                    );

                if (originalRoute.empty()) {

                    std::cout
                        << "No original route exists between the selected nodes.\n";

                    break;
                }

                // ------------------------------------------
                // Failure simulation
                // ------------------------------------------

                auto report =
                    network.simulateFailure(
                        startNode,
                        event
                    );

                // ------------------------------------------
                // Recovery analysis
                // ------------------------------------------

                auto recovery =
                    network.recoverFromFailure(
                        startNode,
                        destinationNode,
                        event
                    );

                // ------------------------------------------
                // Route impact
                // ------------------------------------------

                auto impact =
                    network.analyzeRouteImpact(
                        startNode,
                        destinationNode,
                        event
                    );

                // ------------------------------------------
                // Resilience score
                // ------------------------------------------

                auto resilience =
                    network.calculateResilienceScore(
                        report,
                        impact
                    );

                printIncidentReport(
                    event,
                    originalRoute,
                    recovery,
                    impact,
                    report,
                    resilience
                );

                break;
            }



             case 11: {

                        int startNode;

                        std::cout << "\nEnter node for health analysis: ";
                        std::cin >> startNode;

                        if (!network.hasNode(startNode)) {
                            std::cout << "Invalid node.\n";
                            break;
                        }

                        double health =
                            network.networkHealthScore(startNode);

                        bool connected =
                            network.isConnected();

                        int components =
                            network.connectedComponents();

                        std::cout << "\n";
                        std::cout << "============================================================\n";
                        std::cout << "                 NETRA NETWORK HEALTH\n";
                        std::cout << "============================================================\n";

                        std::cout << "Analysis Start Node  : "
                                << startNode
                                << "\n";

                        std::cout << "Network Status       : "
                                << (health >= 80.0 ? "HEALTHY" :
                                    health >= 50.0 ? "DEGRADED" :
                                                    "CRITICAL")
                                << "\n";

                        std::cout << "Network Health       : "
                                << health
                                << "%\n";

                        std::cout << "Connected            : "
                                << (connected ? "YES" : "NO")
                                << "\n";

                        std::cout << "Connected Components : "
                                << components
                                << "\n";

                        std::cout << "============================================================\n";

                        break;
                    }




                    case 12: {

                            int startNode;

                            std::cout
                                << "\nEnter analysis start node: ";

                            std::cin >> startNode;

                            auto risks =
                                network.analyzeComponentRisk(startNode);

                            if (risks.empty()) {

                                std::cout
                                    << "\nNo component risk data available.\n";

                                break;
                            }

                            std::cout
                                << "\n"
                                << "============================================================\n"
                                << "              NETRA COMPONENT RISK ANALYSIS\n"
                                << "============================================================\n";

                            std::cout
                                << "Analysis Start Node : "
                                << startNode
                                << "\n\n";

                            std::cout
                                << "Component"
                                << "\t\tType"
                                << "\t\tRisk Score"
                                << "\tSeverity\n";

                            std::cout
                                << "------------------------------------------------------------\n";

                            for (const auto& risk : risks) {

                                if (risk.type == FailureType::NODE) {

                                    std::cout
                                        << "Node "
                                        << risk.source
                                        << "\t\tNODE"
                                        << "\t\t"
                                        << risk.riskScore
                                        << "%"
                                        << "\t\t"
                                        << severityToString(risk.severity)
                                        << "\n";

                                } else {

                                    std::cout
                                        << "Link "
                                        << risk.source
                                        << " - "
                                        << risk.destination
                                        << "\t\tLINK"
                                        << "\t\t"
                                        << risk.riskScore
                                        << "%"
                                        << "\t\t"
                                        << severityToString(risk.severity)
                                        << "\n";
                                }
                            }

                            const auto& highestRisk = risks.front();

                            std::cout
                                << "\n------------------------------------------------------------\n"
                                << "MOST CRITICAL COMPONENT\n"
                                << "------------------------------------------------------------\n";

                            if (highestRisk.type == FailureType::NODE) {

                                std::cout
                                    << "Component : Node "
                                    << highestRisk.source
                                    << "\n";

                            } else {

                                std::cout
                                    << "Component : Link "
                                    << highestRisk.source
                                    << " - "
                                    << highestRisk.destination
                                    << "\n";
                            }

                            std::cout
                                << "Risk Score : "
                                << highestRisk.riskScore
                                << "%\n"
                                << "Severity   : "
                                << severityToString(highestRisk.severity)
                                << "\n";

                            std::cout
                                << "============================================================\n";

                            break;
                        }






                case 13: {

                    std::string filename;

                    std::cout << "\nEnter network file: ";
                    std::cin >> filename;

                    if (NetworkAdapter::loadTopology(filename, network)) {

                        std::cout
                            << "\nNetwork loaded successfully.\n";

                        std::cout
                            << "----------------------------------------\n";

                        network.display();

                        std::cout
                            << "----------------------------------------\n";

                        std::cout
                            << "Connected : "
                            << (network.isConnected() ? "YES" : "NO")
                            << "\n";

                        std::cout
                            << "Components: "
                            << network.connectedComponents()
                            << "\n";

                    } else {

                        std::cout
                            << "\nError: Could not load network file.\n";
                    }

                    break;
                }




                case 14: {

                    NetworkStatistics stats =
                        network.getNetworkStatistics();

                    std::cout
                        << "\n";
                    std::cout
                        << "============================================================\n";
                    std::cout
                        << "              NETRA NETWORK STATISTICS\n";
                    std::cout
                        << "============================================================\n";

                    std::cout
                        << "Nodes                 : "
                        << stats.nodes
                        << "\n";

                    std::cout
                        << "Links                 : "
                        << stats.links
                        << "\n";

                    std::cout
                        << "Connected Components  : "
                        << stats.connectedComponents
                        << "\n";

                    std::cout
                        << "Connected             : "
                        << (stats.connected ? "YES" : "NO")
                        << "\n";

                    std::cout
                        << "Average Degree        : "
                        << stats.averageDegree
                        << "\n";

                    std::cout
                        << "Minimum Degree        : "
                        << stats.minimumDegree
                        << "\n";

                    std::cout
                        << "Maximum Degree        : "
                        << stats.maximumDegree
                        << "\n";

                    std::cout
                        << "Network Density       : "
                        << stats.density * 100
                        << "%\n";

                    std::cout
                        << "Most Connected Node   : "
                        << stats.mostConnectedNode
                        << "\n";

                    std::cout
                        << "Node Degree           : "
                        << stats.mostConnectedNodeDegree
                        << "\n";

                    std::cout
                        << "============================================================\n";

                    break;
                }


                case 15: {

                    network.displayTopology();

                    break;
                }

                case 16: {

                    int startNode;
                    int destinationNode;

                    std::cout << "\nEnter start node: ";
                    std::cin >> startNode;

                    std::cout << "Enter destination node: ";
                    std::cin >> destinationNode;

                    std::vector<int> path =
                        network.weightedShortestPath(
                            startNode,
                            destinationNode
                        );

                    if (path.empty()) {

                        std::cout
                            << "\nNo weighted path exists between "
                            << startNode
                            << " and "
                            << destinationNode
                            << ".\n";

                    } else {

                        std::cout
                            << "\n========== WEIGHTED SHORTEST PATH ==========\n";

                        std::cout
                            << "Start       : "
                            << startNode
                            << "\n";

                        std::cout
                            << "Destination : "
                            << destinationNode
                            << "\n";

                        std::cout
                            << "Path        : ";

                        for (size_t i = 0; i < path.size(); ++i) {

                            std::cout << path[i];

                            if (i + 1 < path.size()) {
                                std::cout << " -> ";
                            }
                        }

                        std::cout << "\n";

                        double totalWeight = 0.0;

                        for (size_t i = 0;
                            i + 1 < path.size();
                            ++i) {

                            double weight =
                                network.getEdgeWeight(
                                    path[i],
                                    path[i + 1]
                                );

                            if (weight < 0.0) {
                                weight = 1.0;
                            }

                            totalWeight += weight;
                        }

                        std::cout
                            << "Total Weight: "
                            << totalWeight
                            << "\n";

                        std::cout
                            << "============================================\n";
                    }

                    break;
                }




            // ==========================================
            // EXIT
            // ==========================================

            case 17:

                std::cout
                    << "Exiting NETRA.\n";

                return 0;

            default:

                std::cout
                    << "Invalid choice.\n";

                break;
        }
    }
}