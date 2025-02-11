#include "graph.h"

Graph::Graph() {
  // graph is empty and initialized by default
  nodes = {};
  edges = {};
}

void Graph::addNode(Node node) {
  // Check if node exists and if it doesn't, add it with an empty set
  if (checkNodeInGraph(node)) {
    nodes.insert(node);
    graph[node.getVertice()] = {};
  }
}

bool Graph::checkNodeInGraph(Node node) {
  return (nodes.find(node) != nodes.end() &&
          graph.find(node.getVertice()) != graph.end());
}

int Graph::getNumEdges() { return edges.size(); }
