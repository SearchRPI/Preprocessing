#include "pagerank.h"

// Compute PageRank using iterative method.
void PageRank::computePageRank(Graph &graph, double d = 0.85, double tol = 1e-6,
                               int max_iter = 100) {
  // Get nodes from the graph. The keys of the nodes map are the page URLs.
  std::unordered_map<std::string, double> rank = graph.getNodes();

  // Ensure that every node has an initial rank (if not already set by graph)
  int N = graph.numberOfNodes();
  if (N == 0)
    return;

  // Set the initial rank of the nodes (We need a starting point)
  double initial_rank = 1.0 / N;
  for (auto &pair : rank) {
    pair.second = initial_rank;
  }

  // Get the edge structure. Our graph structure is defined as:
  // edges: key (source) -> unordered_map (destination -> link URL)
  std::unordered_map<std::string, std::unordered_map<std::string, std::string>>
      edges = graph.getEdges();

  // Precompute outdegree for each node.
  std::unordered_map<std::string, int> outDegree;

  // TODO: May not be correct as not entirely sure if we remove it and then add
  // it back or not.
  // Some nodes might not have
  // any outgoing edges. For those we'll have outDegree 0.
  for (auto const &nodePair : rank) {
    std::string node = nodePair.first;
    // If the node is in the edges map, then count its outgoing links
    if (edges.find(node) != edges.end()) {
      outDegree[node] = edges[node].size();
    } else {
      outDegree[node] = 0;
    }
  }

  // Iterative update of page ranks
  std::unordered_map<std::string, double> newRank;
  int iter = 0;
  while (iter < max_iter) {
    // Initialize newRank to 0 for each node.
    for (auto const &p : rank) {
      newRank[p.first] = 0.0;
    }

    // Compute the dangling mass (rank lost to pages with no outlinks, to be
    // redistributed uniformly)
    double dangling_mass = 0.0;
    for (auto const &p : rank) {
      if (outDegree[p.first] == 0) {
        dangling_mass += p.second;
      }
    }

    // For each node v, distribute its PageRank among all its outgoing links.
    // We are essentially computing: for each u, add p[v]/L(v) for every link
    // from v to u.
    for (auto const &p : rank) {
      std::string v = p.first;
      double curRank = p.second;
      // If v has outgoing edges, distribute its rank evenly
      if (outDegree[v] > 0) {
        double distributed = curRank / outDegree[v];
        // For every destination from v, add to that destination’s new rank
        for (auto const &dstPair : edges[v]) {
          std::string u = dstPair.first;
          newRank[u] += distributed;
        }
      }
    }

    // Now compute the new page rank for each page using the formula:
    // newRank(u) = d * (newRank(u) + (dangling_mass / N)) + (1 - d) / N
    double diff = 0.0; // Total difference between iterations for convergence.
    for (auto &p : newRank) {
      double oldRank = rank[p.first];
      p.second = d * (p.second + (dangling_mass / N)) + (1.0 - d) / N;
      diff += fabs(p.second - oldRank);
    }

    // Check convergence: if total difference is below tolerance, we are done.
    if (diff < tol) {
      break;
    }

    // Prepare rank for next iteration
    rank = newRank;
    iter++;
  }

  // Finally, update the graph's node values with the final PageRank values.
  for (auto const &p : rank) {
    graph.setNode(p.first, p.second);
  }

  std::cout << "PageRank converged after " << iter << " iterations."
            << std::endl;

  // Optional: output the computed PageRank for each node.
  for (auto const &p : rank) {
    std::cout << "Node: " << p.first << " PageRank: " << p.second << std::endl;
  }
}
