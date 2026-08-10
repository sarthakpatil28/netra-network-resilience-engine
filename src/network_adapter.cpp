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

        if (!(ss >> source >> destination)) {
            return false;
        }

        if (source <= 0 || destination <= 0) {
            return false;
        }

        if (source == destination) {
            return false;
        }

        double weight = 1.0;

        if (ss >> weight) {

            if (weight <= 0.0) {
                return false;
            }

            std::string extra;

            if (ss >> extra) {
                return false;
            }

            tempGraph.addWeightedEdge(
                source,
                destination,
                weight
            );

        } else {

            tempGraph.addEdge(
                source,
                destination
            );
        }

        hasData = true;
    }

    if (!hasData) {
        return false;
    }

    graph = tempGraph;

    return true;
}