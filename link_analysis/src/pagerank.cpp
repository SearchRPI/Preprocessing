#include "../includes/pagerank.h"

void PageRank::computePageRank(Graph &graph, double c, double epsilon,
                               int maxIterations) {
  // Retrieve nodes and the forward adjacency list.
  // -----------------------------------------------------------------------
  // Step 0: Initialization
  // R0 ← S, where S is a uniform initial score.
  std::unordered_set<std::string> nodes = graph.getNodes();
  std::unordered_map<std::string, std::vector<std::string>> forwardAdj =
      graph.getAdjacencyList();
  int N = nodes.size();

  // Return early if graph is empty.
  if (N == 0) {
    return;
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

  // Define a teleportation (or personalization) vector E (uniform by default).
  std::unordered_map<std::string, double> E;
  for (const auto &node : nodeList) {
    E[node] = 1.0 / N;
  }

  // Initialize PageRank vector R0 = S with a uniform distribution.
  std::unordered_map<std::string, double> pageRank;
  std::unordered_map<std::string, double> newPageRank;
  for (const std::string &node : nodeList) {
    pageRank[node] = 1.0 / N;
    newPageRank[node] = 0.0;
  }

  // delta will track the difference between successive iterations.
  double delta = std::numeric_limits<double>::max();
  int iteration = 0;

  // Main iterative loop: while δ > ε: (until convergence)
  // -----------------------------------------------------------------------
  while (delta > epsilon && iteration < maxIterations) {
    // ---- Step 1: R(i+1) ← A R(i)  ----
    // Reset newPageRank to zero for the current iteration.
    for (const std::string &node : nodeList) {
      newPageRank[node] = 0.0;
    }

    // Compute newPageRank by multiplying the score vector with matrix A.
    // For each node u, sum the contributions from all pages v ∈ B(u)
    // where B(u) is the set of in-neighbors of u, and each contribution is
    // R(i)(v)/N(v), only if v has outgoing links.
    for (const std::string &u : nodeList) {
      double sum = 0.0;
      for (const std::string &v : incoming[u]) {
        if (outDegree[v] > 0) {
          sum += pageRank[v] / static_cast<double>(outDegree[v]);
        }
      }
      newPageRank[u] = c * sum;
    }

    // ---- Step 2: d ← ||R(i)||₁ - ||R(i+1)||₁ ----
    // After applying matrix A, the total mass (L1 norm) of newPageRank can be
    // less than 1 due to dangling nodes or sinks. Compute the difference d
    // between 1.0 and the L1 norm of newPageRank.
    double totalMass = 0.0;
    for (const auto &pair : newPageRank) {
      totalMass += pair.second;
    }
    double d = 1.0 - totalMass;

    // ---- Step 3: R(i+1) ← R(i+1) + dE  ----
    // Add the missing mass d distributed according to the teleportation vector
    // E.
    for (const std::string &node : nodeList) {
      newPageRank[node] += d * E[node];
    }

    // ---- Step 4: δ ← ||R(i+1) - R(i)||₁ ----
    // Compute the L1 norm difference between the new PageRank scores and the
    // previous scores.
    delta = 0.0;
    for (const std::string &node : nodeList) {
      delta += fabs(newPageRank[node] - pageRank[node]);
    }

    // Update R(i) for the next iteration.
    pageRank = newPageRank;
    iteration++;
  }

  // Output the final PageRank scores.
  for (const std::string &node : nodeList) {
    std::cout << "PageRank for node " << node << ": " << pageRank[node]
              << std::endl;
  }
  std::cout << "\n";
}
