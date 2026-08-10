# NETRA — Network Resilience & Self-Healing Routing Engine

NETRA is a C++20-based network simulation and resilience engine that models communication networks using graphs, finds optimal routes, simulates failures, analyzes their impact, and identifies recovery paths.

## Features

- Dynamic node and link management
- Undirected graph representation using adjacency lists
- Duplicate-edge and self-loop prevention
- BFS traversal and distance calculation
- Unweighted shortest-path routing
- Weighted shortest-path routing using Dijkstra's algorithm
- Resilient and alternate path discovery
- Link and node failure simulation
- Failure impact and severity analysis
- Failure recovery analysis
- Network health scoring
- Resilience scoring
- Multiple and mixed failure analysis
- Component risk analysis
- Network statistics
- Unique-link network topology display
- Loading weighted and unweighted networks from files
- Interactive command-line interface
- Automated test suite

## Architecture

```text
Network Input
     |
     v
Network Adapter
     |
     v
Graph Engine
     |
     +---- Routing Engine
     |       +-- BFS
     |       +-- Shortest Path
     |       +-- Weighted Path
     |       +-- Resilient Path
     |
     +---- Failure Engine
     |       +-- Link Failure
     |       +-- Node Failure
     |       +-- Multiple Failures
     |
     +---- Analysis Engine
     |       +-- Health Score
     |       +-- Resilience Score
     |       +-- Risk Analysis
     |
     +---- Recovery Engine
     |
     v
NETRA CLI