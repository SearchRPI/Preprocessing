#include <string>
#include <unordered_map>
#include <unordered_set>

class Graph {
public:
  Graph();

  /**
   * @brief Returns the total number of nodes in the graph
   *
   * @return The total number of nodes inside of the graph
   */
  int numberOfNodes() { return nodes.size(); }

  /**
   * @brief Gets the pagerank value of a specific node (document)
   *
   * @param url The document/page that we want to look at
   * @return The page rank value (double) of the node/document
   */
  double nodeVal(std::string url) { return nodes[url]; }

  /**
   * @brief Determines whether node is in the graph
   *
   * @param url The node that we want to look for
   * @return Whether the node exists in the graph
   */
  bool nodeInGraph(std::string url) { return nodes.find(url) != nodes.end(); }

  /**
   * @brief Determines whether edge is in the graph
   *
   * @param edgeName The edge that we want to look for
   * @return Whether the edge exists in the graph
   */
  bool edgesInGraph(std::string edgeName) {
    return edges.find(edgeName) != edges.end();
  }

  /**
   * @brief Set a node's page rank value.
   *
   * @param url The node we want to set the value to
   * @param val The value of the node that we want it to have
   */
  void setNode(std::string url, double val) { nodes[url] = val; }

  /**
   * @brief Set and add edge to the graph
   *
   * @param src The source node
   * @param dst The destination node
   * @param url The URL that links the two nodes together
   * @return Whether setting of the edge is successful
   */
  bool setEdge(std::string src, std::string dst, std::string url);

  /**
   * @brief Returns the link URL that connects the two nodes/documents
   *
   * @param source The starting node that we started at
   * @param destination The ending node that is connected by the starting node
   * @return The URL link that connects to the source and destination node.
   */
  std::string edgeLink(std::string source, std::string destination) {
    return edges[source][destination];
  }

  /**
   * @brief Returns the total number of edges in the graph.
   *
   * @return The total number of edges in the graph.
   */
  int numberOfEdges() { return numEdges; };

  /**
   * @brief Clears the graph, resets/clear the values of the graph.
   */
  void clear();

  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
  getEdges() {
    return edges;
  }

  std::unordered_map<std::string, double> getNodes() { return nodes; }

  /**
   * @brief Reads from a file that will be used to create the graph
   */
  void readFromFile(std::string fileName);

private:
  /**
   * key: source node
   * value: key-value
   *    key: destination
   *    value: url that connects the source and destination
   */
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
      edges{};

  std::unordered_map<std::string, double> nodes{};
  int numEdges;
};
