#include "graph.h"

void Graph::clear() {
  numEdges = 0;
  edges.clear();
  nodes.clear();
}

Graph::Graph() {
  edges = {};
  nodes = {};
  numEdges = 0;
}

void Graph::readFromFile(std::string fileName) {}

bool Graph::setEdge(std::string src, std::string dst, std::string url) {
  bool inGraph = nodeInGraph(src) && nodeInGraph(dst);
  if (inGraph) {
    edges[src][dst] = url;
    numEdges++;
    return true;
  }
  return false;
}
