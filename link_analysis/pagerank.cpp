#include "pagerank.h" // Include your Graph header file

using namespace std;

void PageRank::computePageRank(Graph &graph, double damping = 0.85,
                               double tol = 1e-6, int maxIter = 100) {
  // Retrieve the nodes and edges from the Graph.
  unordered_map<string, double> nodes = graph.getNodes();
  auto edges = graph.getEdges();
  // Number of nodes.
  int N = graph.numberOfNodes();
  if (N == 0)
    return;

  // Teleportation probability (rank source) is uniform.
  double teleportVal = (1.0 - damping) / N;

  // Initialize rank vector for every node to uniform probability:
  unordered_map<string, double> rank;
  for (const auto &entry : nodes) {
    rank[entry.first] = 1.0 / N;
  }

  // Precompute the outdegree for all nodes.
  unordered_map<string, int> outdegree;
  for (const auto &nodeEntry : nodes) {
    string src = nodeEntry.first;
    if (edges.find(src) != edges.end()) {
      outdegree[src] = edges[src].size();
    } else {
      // Dangling node.
      outdegree[src] = 0;
    }
  }

  // Iterative update.
  for (int iter = 0; iter < maxIter; iter++) {
    // newRank will store the updated rank values.
    unordered_map<string, double> newRank;
    // Initially assign no score.
    for (const auto &nodeEntry : nodes) {
      newRank[nodeEntry.first] = 0.0;
    }

    // For each node v, distribute its rank among all nodes that v links to.
    for (const auto &nodeEntry : nodes) {
      string src = nodeEntry.first;
      double currRank = rank[src];
      // Check how many outlinks the node has.
      int deg = outdegree[src];
      if (deg > 0) {
        // Distribute rank to each destination that src links to.
        for (const auto &dstEntry : edges[src]) {
          string dst = dstEntry.first;
          newRank[dst] += currRank / deg;
        }
      } else {
        // Dangling node: it contributes uniformly to all nodes.
        double distributed = currRank / N;
        for (auto &nr : newRank) {
          nr.second += distributed;
        }
      }
    }

    // Apply damping and add teleportation factor.
    double diff = 0.0;
    for (auto &nr : newRank) {
      nr.second = damping * nr.second + teleportVal;
      diff += fabs(nr.second - rank[nr.first]);
    }

    // For debugging, you can print the iteration
    // cout << "Iteration " << iter + 1 << " diff: " << diff << endl;

    // Check for convergence (L1 norm)
    if (diff < tol) {
      cout << "PageRank converged after " << iter + 1 << " iterations." << endl;
      // Set the computed rank values back in the Graph.
      for (auto &entry : newRank) {
        graph.setNode(entry.first, entry.second);
      }
      return;
    }

    rank = newRank;
  }

  cout << "Warning: PageRank did not converge in the maximum iterations."
       << endl;
  // Update Graph with the last iteration's rank.
  for (auto &entry : rank) {
    graph.setNode(entry.first, entry.second);
  }
}
