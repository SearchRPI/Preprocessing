#ifndef GRAPH_H
#define GRAPH_H

#include <cmath>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph {
public:
  Graph();

  /**
   * @brief Clears the graph, resets/clear the values of the graph.
   */
  void clear();

  /**
   * @brief Reads from a file that will be used to create the graph
   */
  void readFromFile(std::string fileName);

  void addNode(std::string node);

  void addEdge(std::string source, std::string destination);

  std::unordered_set<std::string> getNodes() { return nodes; }
  std::unordered_map<std::string, std::vector<std::string>> getAdjacencyList() {
    return adjacencyList;
  }

private:
  std::unordered_map<std::string, std::vector<std::string>> adjacencyList;
  std::unordered_set<std::string> nodes;
};

#endif
