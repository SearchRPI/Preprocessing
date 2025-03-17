#include "../includes/graph.h"

void Graph::clear() {}

Graph::Graph() {}

void Graph::readFromFile(std::string fileName) {}

void Graph::addNode(std::string node) {
  nodes.insert(node);
  adjacencyList[node] = {};
}

void Graph::addEdge(std::string source, std::string destination) {
  if (nodes.find(source) != nodes.end() &&
      nodes.find(destination) != nodes.end()) {
    adjacencyList[source].push_back(destination);
  }
}
