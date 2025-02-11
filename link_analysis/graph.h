#include <string>
#include <unordered_map>
#include <unordered_set>

#include "edge.h"
#include "node.h"

class Graph {
public:
  Graph();

  /**
   * @brief Adds an edge to the graph
   *
   * @param from The node that is the start of the edge.
   * @param to The node that is end of the edge.
   * @param edgeName The edge name of the edge between the two nodes. This is
   * the URL
   */
  void addEdge(Node from, Node to, std::string edgeName);

  /**
   * @brief Adds a node into the graph
   *
   * @param node The node that is being added to the graph
   */
  void addNode(Node node);

  /**
   * @brief Returns whether the given node is inside of the graph
   *
   * @param node The node that we are searching for in the graph
   * @return Whether the node is in the egraph
   */
  bool checkNodeInGraph(Node node);

  /**
   * @brief Returns the total number of edges in the graph.
   *
   * @return The total number of edges in the graph.
   */
  int getNumEdges();

private:
  std::unordered_map<std::string, std::unordered_set<Edge>> graph;
  std::unordered_set<Node, Node::NodeHash> nodes;
  std::unordered_set<Edge, Edge::EdgeHash> edges;
};
