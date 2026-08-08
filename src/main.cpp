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
}