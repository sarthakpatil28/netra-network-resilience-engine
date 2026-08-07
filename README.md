# NETRA — Network Resilience Engine

NETRA is a modular C++ network simulation and self-healing routing engine designed to detect network abnormalities, analyze network topology, and dynamically recover communication paths.

## Project Vision

The goal of NETRA is to develop a software-defined network resilience system that can:

- Model communication networks as dynamic graphs
- Monitor network health parameters
- Detect node and link failures
- Identify abnormal network behavior
- Calculate optimal communication routes
- Dynamically reroute traffic around failures
- Integrate machine learning for anomaly detection
- Interface with real network hardware in later stages

## Current Development Stage

**Phase 0 — Project Foundation**

The current implementation focuses on establishing the software architecture, build system, testing framework, and development workflow.

## Technology Stack

- C++
- CMake
- Ninja
- Git
- GitHub
- GoogleTest
- Python (future ML layer)
- ESP32 (future hardware layer)

## Architecture

```text
Network Data
     |
     v
Network Model
     |
     v
Graph Engine
     |
     v
Routing Engine
     |
     v
Failure Detection
     |
     v
Anomaly Detection
     |
     v
Self-Healing Network