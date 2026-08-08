/*#include "graph.hpp"

#include <iostream>

int main() {
    Graph network;

    network.addEdge(1,2);
    network.addEdge(2,3);
    network.addEdge(1,3);

     // duplicate edge
    network.addEdge(1,2);
    
    //self edge
    network.addEdge(3,3);
   

    //Removing edge
   // std::cout << "Before removing Edge\n";
    //network.display();

   // network.removeEdge(1,3);

    //std::cout << "After removing Edge\n";
    //network.display();



    std::cout << "Before removing Node\n";
    network.display();

    network.removeNode(1);

    std::cout << "After removing Node\n";
    network.display();

    return 0;
}*/


/*#include "graph.hpp"
#include <iostream>

int main() {

    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);

    std::cout << "Node 1 exists: "
              << network.hasNode(1) << "\n";

    std::cout << "Node 99 exists: "
              << network.hasNode(99) << "\n";

    std::cout << "Edge 1-2 exists: "
              << network.hasEdge(1, 2) << "\n";

    std::cout << "Edge 1-3 exists: "
              << network.hasEdge(1, 3) << "\n";

    return 0;
}*/

/*#include "graph.hpp"
#include <iostream>

int main() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    std::vector<int> result = network.bfs(1);

    std::cout << "BFS from node 1: ";

    for (int node : result) {
        std::cout << node << " ";
    }

    std::cout << '\n';

    return 0;
}*/


/*#include "graph.hpp"
#include <iostream>

int main() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    auto distances = network.bfsDistances(1);

    std::cout << "BFS distances from node 1:\n";

    for (const auto& [node, distance] : distances) {
        std::cout << "Node " << node
                  << " -> " << distance << " hops\n";
    }

    return 0;
}*/


/*#include "graph.hpp"
#include <iostream>

int main() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    auto path = network.shortestPath(1, 5);

    std::cout << "Shortest path from 1 to 5: ";

    for (int node : path) {
        std::cout << node << " ";
    }

    std::cout << '\n';

    return 0;
}*/




/*

#include "graph.hpp"
#include <iostream>

int main() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 4);
    network.addEdge(4, 5);
    network.addEdge(3, 5);

    std::cout << "Before failure:\n";

    auto pathBefore = network.resilientPath(1, 5);

    std::cout << "Route: ";

    for (int node : pathBefore) {
        std::cout << node << " ";
    }

    std::cout << "\n";

    // Simulate network link failure
    network.removeEdge(1, 3);

    std::cout << "\nAfter failure of link 1-3:\n";

    auto pathAfter = network.resilientPath(1, 5);

    if (pathAfter.empty()) {
        std::cout << "No route available\n";
    } else {
        std::cout << "Route: ";

        for (int node : pathAfter) {
            std::cout << node << " ";
        }

        std::cout << "\n";
    }

    return 0;
}*/

#include "graph.hpp"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

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
    std::cout << "10. Exit\n";
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

            // ==========================================
            // EXIT
            // ==========================================

            case 10:

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