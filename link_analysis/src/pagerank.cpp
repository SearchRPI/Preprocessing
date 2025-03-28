#include "../includes/pagerank.h"

std::unordered_map<std::string, double> PageRank::computePageRank(
    Graph &graph, double c, double epsilon, int maxIterations, double e,
    const std::unordered_map<std::string, double> &initialPageRank) {
  // Retrieve nodes and the forward adjacency list.
  // -----------------------------------------------------------------------
  // Step 0: Initialization and setup
  std::unordered_set<std::string> nodes = graph.getNodes();
  std::unordered_map<std::string, std::vector<std::string>> forwardAdj =
      graph.getAdjacencyList();
  int N = nodes.size();

  // Return empty if graph is empty.
  if (N == 0) {
    return {};
  }

  // Create a vector to ensure consistent node ordering.
  std::vector<std::string> nodeList(nodes.begin(), nodes.end());

  // Build the reverse mapping (incoming links list) and compute out-degrees.
  std::unordered_map<std::string, std::vector<std::string>> incoming;
  std::unordered_map<std::string, int> outDegree;
  for (const auto &node : nodeList) {
    incoming[node] =
        std::vector<std::string>(); // Initialize empty incoming list.
    outDegree[node] = forwardAdj[node].size(); // Out-degree for each node.
  }
  // For every edge (u -> v) in the forward graph, add u to the incoming list of
  // v.
  for (const auto &pair : forwardAdj) {
    const std::string &u = pair.first;
    for (const std::string &v : pair.second) {
      incoming[v].push_back(u);
    }
  }

  // Define a teleportation probability if user does not specify one (uniform by
  // default).
  if (e == -1) {
    e = 1.0 / N;
  }

  // Initialize PageRank vector.
  std::unordered_map<std::string, double> pageRank;
  std::unordered_map<std::string, double> newPageRank;
  // If an initial PageRank was provided (from a previous computation), use it.
  // Otherwise, initialize uniformly.
  if (!initialPageRank.empty()) {
    for (const std::string &node : nodeList) {
      if (initialPageRank.find(node) != initialPageRank.end()) {
        pageRank[node] = initialPageRank.at(node);
      } else {
        // In case a new node was added, initialize uniformly.
        pageRank[node] = 1.0 / N;
      }
      newPageRank[node] = 0.0;
    }
  } else {
    for (const std::string &node : nodeList) {
      pageRank[node] = 1.0 / N;
      newPageRank[node] = 0.0;
    }
  }

  // delta will track the difference between successive iterations.
  double delta = std::numeric_limits<double>::max();
  int iteration = 0;

  // Main iterative loop: while δ > ε and iterations remain.
  while (delta > epsilon && iteration < maxIterations) {
    // ---- Step 1: Compute contributions to newPageRank ----
    // Reset newPageRank for the current iteration.
    for (const std::string &node : nodeList) {
      newPageRank[node] = 0.0;
    }

    // For each node u, accumulate contributions from all in-neighbors.
    for (const std::string &u : nodeList) {
      double sum = 0.0;
      for (const std::string &v : incoming[u]) {
        if (outDegree[v] > 0) {
          sum += pageRank[v] / static_cast<double>(outDegree[v]);
        }
      }
      newPageRank[u] = c * sum;
    }

    // ---- Step 2: Adjust for dangling nodes ----
    double totalMass = 0.0;
    for (const auto &pair : newPageRank) {
      totalMass += pair.second;
    }
    double d = 1.0 - totalMass;

    // Add the missing mass d distributed according to the teleportation vector
    // E.
    for (const std::string &node : nodeList) {
      newPageRank[node] += d * e;
    }

    // ---- Step 3: Check for convergence ----
    delta = 0.0;
    for (const std::string &node : nodeList) {
      delta += fabs(newPageRank[node] - pageRank[node]);
    }

    // Update pageRank for the next iteration.
    pageRank = newPageRank;
    iteration++;
  }

  // Output the final PageRank scores.
  for (const std::string &node : nodeList) {
    std::cout << "PageRank for node " << node << ": " << pageRank[node]
              << std::endl;
  }
  std::cout << "\n";

  return pageRank;
}
