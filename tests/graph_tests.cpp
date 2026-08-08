#include "graph.hpp"//access to graph class
#include <cassert>//assert()
#include <iostream>
#include <vector>


void testAddNode() {

    Graph network;

    network.addNode(1);

    assert(network.hasNode(1));

    std::cout << "[PASS] Add Node\n";
}



void testAddEdge() {

    Graph network;

    network.addEdge(1, 2);

    assert(network.hasEdge(1, 2));
    assert(network.hasEdge(2, 1));

    std::cout << "[PASS] Add Edge\n";
}



void testDuplicateEdge() {

    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 2);

    assert(network.hasEdge(1, 2));
    assert(network.hasEdge(2, 1));

    std::cout << "[PASS] Duplicate Edge Prevention\n";
}



void testSelfLoop() {

    Graph network;

    network.addEdge(3, 3);

    assert(!network.hasEdge(3, 3));

    std::cout << "[PASS] Self Loop Prevention\n";
}


void testRemoveEdge() {

    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);

    assert(network.hasEdge(1, 2));

    network.removeEdge(1, 2);

    assert(!network.hasEdge(1, 2));
    assert(!network.hasEdge(2, 1));

    std::cout << "[PASS] Remove Edge\n";
}



void testRemoveNode() {

    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);
    network.addEdge(2, 4);

    assert(network.hasNode(2));
    assert(network.hasEdge(1, 2));
    assert(network.hasEdge(2, 3));
    assert(network.hasEdge(2, 4));

    network.removeNode(2);

    assert(!network.hasNode(2));

    assert(!network.hasEdge(1, 2));
    assert(!network.hasEdge(2, 3));
    assert(!network.hasEdge(2, 4));

    std::cout << "[PASS] Remove Node\n";
}



void testNonExistentNode() {

    Graph network;

    assert(!network.hasNode(99));

    network.removeNode(99);

    assert(!network.hasNode(99));

    std::cout << "[PASS] Non-existent Node Handling\n";
}



void testNonExistentEdge() {

    Graph network;

    network.addEdge(1, 2);

    network.removeEdge(1, 3);

    assert(network.hasEdge(1, 2));

    std::cout << "[PASS] Non-existent Edge Handling\n";
}




void testBFS() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    std::vector<int> expected = {1, 2, 3, 4, 5};
    std::vector<int> actual = network.bfs(1);

    assert(actual == expected);

    std::cout << "[PASS] BFS Traversal\n";
}



void testBFSDistances() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    auto distances = network.bfsDistances(1);

    assert(distances.at(1) == 0);
    assert(distances.at(2) == 1);
    assert(distances.at(3) == 1);
    assert(distances.at(4) == 2);
    assert(distances.at(5) == 2);

    std::cout << "[PASS] BFS Distances\n";
}



void testShortestPath() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    auto pathTo5 = network.shortestPath(1, 5);
    assert(pathTo5 == std::vector<int>({1, 3, 5}));

    auto pathTo4 = network.shortestPath(1, 4);
    assert(pathTo4 == std::vector<int>({1, 2, 4}));

    auto pathToSelf = network.shortestPath(1, 1);
    assert(pathToSelf == std::vector<int>({1}));

    auto pathToMissing = network.shortestPath(1, 99);
    assert(pathToMissing.empty());

    std::cout << "[PASS] Shortest Path\n";
}



int main() {

    testAddNode();
    testAddEdge();
    testDuplicateEdge();
    testSelfLoop();
    testRemoveEdge();
    testRemoveNode();
    testNonExistentNode();
    testNonExistentEdge();
    testBFS();
    testBFSDistances();
    testShortestPath();

    return 0;
}