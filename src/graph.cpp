#include "graph.hpp" //this belongs to graph class
#include <iostream>
#include <algorithm>
#include <queue>
#include <unordered_set>

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






void Graph::display() const{
    for(const auto& pair : adjacencyList){ // loop to go through every entry in out adjacencyList
       std::cout << pair.first << " -> "; // printing first node

       for(int neighbour : pair.second){ // going thorugh every neighbouring node
        std::cout << neighbour << " "; // printing neighouring nodes
       }
    
    std::cout << "\n";
    }
}