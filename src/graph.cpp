#include "graph.hpp" //this belongs to graph class
#include <iostream>
#include <algorithm>

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



void Graph::display() const{
    for(const auto& pair : adjacencyList){ // loop to go through every entry in out adjacencyList
       std::cout << pair.first << " -> "; // printing first node

       for(int neighbour : pair.second){ // going thorugh every neighbouring node
        std::cout << neighbour << " "; // printing neighouring nodes
       }
    
    std::cout << "\n";
    }
}