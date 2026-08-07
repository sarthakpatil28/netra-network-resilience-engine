#include "graph.hpp"

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
   /* std::cout << "Before removing Edge\n";
    network.display();

    network.removeEdge(1,3);

    std::cout << "After removing Edge\n";
    network.display();*/



    std::cout << "Before removing Node\n";
    network.display();

    network.removeNode(1);

    std::cout << "After removing Node\n";
    network.display();

    return 0;
}