#include "network_adapter.hpp"

#include <fstream>
#include <sstream>
#include <string>

bool NetworkAdapter::loadTopology(
    const std::string& filename,
    Graph& graph
) {

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

        // Source and destination must exist.
        if (!(ss >> source >> destination)) {
            return false;
        }

        // Nodes must be positive.
        if (source <= 0 || destination <= 0) {
            return false;
        }

        // Reject self-loops.
        if (source == destination) {
            return false;
        }

        double weight;

        // Format: source destination
        if (!(ss >> weight)) {

            tempGraph.addEdge(
                source,
                destination
            );

            hasData = true;
            continue;
        }

        // Weight must be positive.
        if (weight <= 0.0) {
            return false;
        }

        double capacity;

        // Format: source destination weight
        if (!(ss >> capacity)) {

            tempGraph.addWeightedEdge(
                source,
                destination,
                weight
            );

            hasData = true;
            continue;
        }

        // Capacity must be positive.
        if (capacity <= 0.0) {
            return false;
        }

        // No fourth value allowed.
        std::string extra;

        if (ss >> extra) {
            return false;
        }

        // Format:
        // source destination weight capacity
        tempGraph.addWeightedEdgeWithCapacity(
            source,
            destination,
            weight,
            capacity
        );

        hasData = true;
    }

    if (!hasData) {
        return false;
    }

    graph = tempGraph;

    return true;
}