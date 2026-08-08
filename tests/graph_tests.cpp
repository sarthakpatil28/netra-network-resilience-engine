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





void testAlternateRouteAfterFailure() {
    Graph network;

    // Create a redundant network
    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 4);
    network.addEdge(4, 5);
    network.addEdge(3, 5);

    // Original shortest route
    auto originalPath = network.shortestPath(1, 5);

    assert(originalPath == std::vector<int>({1, 3, 5}));

    // Simulate failure of link 1-3
    network.removeEdge(1, 3);

    // NETRA should find the alternate route
    auto alternatePath = network.shortestPath(1, 5);

    assert(alternatePath == std::vector<int>({1, 2, 4, 5}));

    std::cout << "[PASS] Alternate Route After Failure\n";
}






void testResilientPath() {
    Graph network;

    // Create a network with two possible routes from 1 to 5
    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 4);
    network.addEdge(4, 5);
    network.addEdge(3, 5);

    // Check the original route
    auto originalPath = network.resilientPath(1, 5);

    assert(originalPath == std::vector<int>({1, 3, 5}));

    // Simulate failure of the current route
    network.removeEdge(1, 3);

    // NETRA should recover using the alternate route
    auto recoveredPath = network.resilientPath(1, 5);

    assert(recoveredPath == std::vector<int>({1, 2, 4, 5}));

    std::cout << "[PASS] Resilient Path Recovery\n";
}







void testNodeFailureRecovery() {
    Graph network;

    // Create two possible routes from 1 to 5
    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 4);
    network.addEdge(4, 5);
    network.addEdge(3, 5);

    // Verify the original route
    auto originalPath = network.resilientPath(1, 5);

    assert(originalPath == std::vector<int>({1, 3, 5}));

    // Simulate complete failure of node 3
    network.removeNode(3);

    // Node 3 should no longer exist
    assert(!network.hasNode(3));

    // NETRA should find the alternate route
    auto recoveredPath = network.resilientPath(1, 5);

    assert(recoveredPath == std::vector<int>({1, 2, 4, 5}));

    std::cout << "[PASS] Node Failure Recovery\n";
}






void testConnectedComponents() {
    Graph network;

    // First connected component
    network.addEdge(1, 2);
    network.addEdge(2, 3);

    // Second connected component
    network.addEdge(4, 5);

    // Third connected component
    network.addNode(6);

    int components = network.connectedComponents();

    assert(components == 3);

    std::cout << "[PASS] Connected Components\n";
}







void testConnectedNetwork() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);
    network.addEdge(3, 4);
    network.addEdge(4, 5);

    assert(network.isConnected());

    std::cout << "[PASS] Connected Network Detection\n";
}







void testDisconnectedNetwork() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);

    network.addEdge(4, 5);

    assert(!network.isConnected());

    std::cout << "[PASS] Disconnected Network Detection\n";
}






void testHealthyNetworkScore() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);
    network.addEdge(3, 4);
    network.addEdge(4, 5);

    double score = network.networkHealthScore(1);

    assert(score == 100.0);

    std::cout << "[PASS] Healthy Network Score\n";
}





void testPartialNetworkScore() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);

    network.addEdge(4, 5);

    double score = network.networkHealthScore(1);

    assert(score == 60.0);

    std::cout << "[PASS] Partial Network Score\n";
}





void testInvalidHealthScoreNode() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);

    double score = network.networkHealthScore(99);

    assert(score == 0.0);

    std::cout << "[PASS] Invalid Health Score Node\n";
}





void testZeroHealthImpact() {
    Graph network;

    double impact = network.healthImpact(100.0, 100.0);

    assert(impact == 0.0);

    std::cout << "[PASS] Zero Health Impact\n";
}






void testPartialHealthImpact() {
    Graph network;

    double impact = network.healthImpact(100.0, 60.0);

    assert(impact == 40.0);

    std::cout << "[PASS] Partial Health Impact\n";
}








void testCompleteHealthImpact() {
    Graph network;

    double impact = network.healthImpact(100.0, 0.0);

    assert(impact == 100.0);

    std::cout << "[PASS] Complete Health Impact\n";
}






void testFailureReport() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);
    network.addEdge(3, 4);
    network.addEdge(4, 5);

    FailureReport report = network.analyzeFailure(1);

    assert(report.healthBefore == 100.0);
    assert(report.healthAfter == 100.0);
    assert(report.healthImpact == 0.0);

    assert(report.componentsBefore == 1);
    assert(report.componentsAfter == 1);

    assert(report.connectedBefore);
    assert(report.connectedAfter);

    std::cout << "[PASS] Failure Report\n";
}






void testLinkFailureAnalysis() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);
    network.addEdge(4, 5);

    FailureReport report =
        network.analyzeLinkFailure(1, 1, 3);

    assert(report.healthBefore == 100.0);
    assert(report.healthAfter == 100.0);

    assert(report.healthImpact == 0.0);

    assert(report.componentsBefore == 1);
    assert(report.componentsAfter == 1);

    assert(report.connectedBefore);
    assert(report.connectedAfter);

    std::cout << "[PASS] Link Failure Analysis\n";
}





void testLowSeverity() {
    Graph network;

    FailureReport report{100.0, 100.0, 0.0, 1, 1, true, true};

    assert(network.classifyFailure(report) == FailureSeverity::LOW);

    std::cout << "[PASS] Low Failure Severity\n";
}


void testModerateSeverity() {
    Graph network;

    FailureReport report{100.0, 80.0, 20.0, 1, 1, true, true};

    assert(network.classifyFailure(report) == FailureSeverity::MODERATE);

    std::cout << "[PASS] Moderate Failure Severity\n";
}



void testHighSeverity() {
    Graph network;

    FailureReport report{100.0, 75.0, 25.0, 1, 2, true, false};

    assert(network.classifyFailure(report) == FailureSeverity::HIGH);

    std::cout << "[PASS] High Failure Severity\n";
}



void testCriticalSeverity() {
    Graph network;

    FailureReport report{100.0, 30.0, 70.0, 1, 3, true, false};

    assert(network.classifyFailure(report) == FailureSeverity::CRITICAL);

    std::cout << "[PASS] Critical Failure Severity\n";
}







void testNodeFailureAnalysis() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    FailureReport report =
        network.analyzeNodeFailure(1, 3);

    assert(report.healthBefore == 100.0);
    assert(report.healthAfter == 75.0);

    assert(report.healthImpact == 25.0);

    assert(report.componentsBefore == 1);
    assert(report.componentsAfter == 2);

    assert(report.connectedBefore);
    assert(!report.connectedAfter);

    std::cout << "[PASS] Node Failure Analysis\n";
}





void testSimulateLinkFailure() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);
    network.addEdge(4, 5);

    FailureEvent event{
        FailureType::LINK,
        1,
        3
    };

    FailureReport report =
        network.simulateFailure(1, event);

    assert(report.healthBefore == 100.0);
    assert(report.healthAfter == 100.0);
    assert(report.healthImpact == 0.0);

    assert(report.componentsBefore == 1);
    assert(report.componentsAfter == 1);

    assert(report.connectedBefore);
    assert(report.connectedAfter);

    assert(
        network.classifyFailure(report)
        == FailureSeverity::LOW
    );

    std::cout << "[PASS] Simulate Link Failure\n";
}





void testSimulateNodeFailure() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);

    FailureEvent event{
        FailureType::NODE,
        3,
        0
    };

    FailureReport report =
        network.simulateFailure(1, event);

    assert(report.healthBefore == 100.0);
    assert(report.healthAfter == 75.0);
    assert(report.healthImpact == 25.0);

    assert(report.componentsBefore == 1);
    assert(report.componentsAfter == 2);

    assert(report.connectedBefore);
    assert(!report.connectedAfter);

    assert(
        network.classifyFailure(report)
        == FailureSeverity::HIGH
    );

    std::cout << "[PASS] Simulate Node Failure\n";
}






void testRecoverFromLinkFailure() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);
    network.addEdge(4, 5);

    FailureEvent event{
        FailureType::LINK,
        1,
        3
    };

    RecoveryResult result =
        network.recoverFromFailure(1, 5, event);

    assert(result.recovered);

    assert(
        result.route ==
        std::vector<int>({1, 2, 4, 5})
    );

    std::cout << "[PASS] Recover From Link Failure\n";
}



void testFailedRecovery() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(2, 3);
    network.addEdge(3, 5);

    FailureEvent event{
        FailureType::NODE,
        3,
        0
    };

    RecoveryResult result =
        network.recoverFromFailure(1, 5, event);

    assert(!result.recovered);
    assert(result.route.empty());

    std::cout << "[PASS] Failed Recovery Detection\n";
}








void testRouteImpact() {
    Graph network;

    network.addEdge(1, 2);
    network.addEdge(1, 3);
    network.addEdge(2, 4);
    network.addEdge(3, 5);
    network.addEdge(4, 5);

    FailureEvent event{
        FailureType::LINK,
        1,
        3
    };

    RouteImpact impact =
        network.analyzeRouteImpact(1, 5, event);

    assert(impact.originalHops == 2);
    assert(impact.recoveryHops == 3);
    assert(impact.additionalHops == 1);
    assert(impact.routeChanged);

    std::cout << "[PASS] Route Impact Analysis\n";
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
    testAlternateRouteAfterFailure();
    testResilientPath();
    testNodeFailureRecovery();
    testConnectedComponents();
    testConnectedNetwork();
    testDisconnectedNetwork();  
    testHealthyNetworkScore();
    testPartialNetworkScore();
    testInvalidHealthScoreNode();

    testZeroHealthImpact();
    testPartialHealthImpact();
    testCompleteHealthImpact();
    testFailureReport();
    testLinkFailureAnalysis();
    testNodeFailureAnalysis();

    testLowSeverity();
    testModerateSeverity();
    testHighSeverity();
    testCriticalSeverity();
    testSimulateLinkFailure();
    testSimulateNodeFailure();

    testRecoverFromLinkFailure();
    testFailedRecovery();
    testRouteImpact();

    return 0;
}