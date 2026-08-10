#ifndef NETRA_NETWORK_ADAPTER_HPP
#define NETRA_NETWORK_ADAPTER_HPP

#include <string>

#include "graph.hpp"

class NetworkAdapter {

public:

    static bool loadTopology(
        const std::string& filename,
        Graph& graph
    );

};

#endif