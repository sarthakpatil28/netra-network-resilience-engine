# NETRA — Network Resilience & Self-Healing Routing Engine

NETRA is a C++20-based network simulation and resilience engine designed to model communication networks, discover routes, simulate network failures, measure their impact, analyze component risk, and evaluate recovery and traffic conditions.

The project combines graph-based routing, failure analysis, resilience measurement, recovery analysis, and traffic monitoring into a single interactive command-line application.

---

## Key Capabilities

### Graph & Network Management
- Dynamic node and link management
- Undirected graph representation using adjacency lists
- Duplicate-edge prevention
- Self-loop prevention
- Network connectivity analysis
- Connected component detection
- Node degree and network density analysis

### Routing
- BFS traversal
- Unweighted shortest-path routing
- Weighted shortest-path routing using Dijkstra's algorithm
- Resilient path discovery
- Alternate route discovery

### Failure Analysis
- Link failure simulation
- Node failure simulation
- Multiple failure analysis
- Mixed link and node failure analysis
- Failure impact measurement
- Failure severity classification
- Network health evaluation
- Resilience scoring

### Recovery
- Failure and recovery simulation
- Original route analysis
- Recovery route discovery
- Recovery success evaluation
- Route-change analysis
- Post-failure connectivity analysis

### Traffic Analysis
- Interactive traffic-flow management
- Traffic flow addition and removal
- Link utilization calculation
- Link overload detection
- Traffic capacity monitoring
- Traffic dashboard

### Network Analysis
- Network health dashboard
- Component risk analysis
- Network statistics
- Network topology display
- Weighted network analysis

### Input & Testing
- Weighted network file loading
- Unweighted network file loading
- Interactive CLI
- Automated test suite

---

## System Architecture

```text
                         NETWORK INPUT
                              |
                              v
                     +------------------+
                     | Network Adapter  |
                     +------------------+
                              |
                              v
                     +------------------+
                     |   Graph Engine   |
                     +------------------+
                              |
          +-------------------+-------------------+
          |                   |                   |
          v                   v                   v
   Routing Engine       Failure Engine      Traffic Engine
          |                   |                   |
   +------+-------+     +-----+------+      +-----+------+
   |      |       |     |     |      |      |     |      |
   v      v       v     v     v      v      v     v      v
  BFS  Weighted Resilient Link  Node Multiple Flow Util. Overload
       Path     Path     Failure Failure Failure Mgmt.       Detection
                                              |
                                              v
                                       Traffic Dashboard

          +-------------------+-------------------+
                              |
                              v
                     Analysis Engine
                              |
              +---------------+---------------+
              |               |               |
              v               v               v
         Health Score   Resilience Score   Risk Analysis
                              |
                              v
                      Recovery Engine
                              |
                              v
                         NETRA CLI