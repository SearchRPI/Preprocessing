#include <string>
#include <unordered_map>
#include <unordered_set>

/**
 * Each edge is representing links (URLs)
 */
struct Edge {
  std::string link;
  std::string from;
  std::string to;
};

struct EdgeHash {
public:
  size_t operator()(const Edge e) const {
    // Compute individual hashes for each string member.
    std::size_t h1 = std::hash<std::string>{}(e.link);
    std::size_t h2 = std::hash<std::string>{}(e.from);
    std::size_t h3 = std::hash<std::string>{}(e.to);

    // Combine the hashes.
    std::size_t seed = h1;
    seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
  }
};

/**
 * Each node is a page of a URL/website
 */
struct Node {
  std::string vertice;
};

struct NodeHash {
public:
  size_t operator()(const Node n) const {
    return std::hash<std::string>{}(n.vertice);
  }
};

class Graph {
public:
  Graph() {
    // graph is empty and initialized by default
    nodes = {};
    edges = {};
  }

  void addEdge() {}

  void addNode(Node node) {
    // Check if node exists and if it doesn't, add it with an empty set
    if (checkNodeInGraph(node)) {
      nodes.insert(node);
      graph[node.vertice] = {};
    }
  }

  /**
   * @brief Returns whether the given node is inside of the graph
   *
   * @param node The node that we are searching for in the graph
   * @return Whether the node is in the egraph
   */
  bool checkNodeInGraph(Node node) {
    return (nodes.find(node) != nodes.end() &&
            graph.find(node.vertice) != graph.end());
  }

private:
  std::unordered_map<std::string, std::unordered_set<Edge>> graph;
  std::unordered_set<Node, NodeHash> nodes;
  std::unordered_set<Edge, EdgeHash> edges;
};
