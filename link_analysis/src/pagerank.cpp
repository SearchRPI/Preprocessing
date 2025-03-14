#include "../includes/pagerank.h"
#include <cmath>

// Helper function to compute the L1 norm of a vector.
double l1norm(const std::unordered_map<std::string, double> &vec) {
  double norm = 0.0;
  for (auto const &p : vec) {
    norm += fabs(p.second);
  }
  return norm;
}

// Multiply the “matrix” A (encoded in the Graph edges) by vector R.
// Here, A is defined so that for each node v, each outgoing link from v
// distributes R(v) evenly.
std::unordered_map<std::string, double>
multiplyA(Graph &graph, const std::unordered_map<std::string, double> &R) {
  std::unordered_map<std::string, double> result;
  // Initialize result for each node.
  auto nodes = graph.getNodes();
  for (auto const &p : nodes) {
    result[p.first] = 0.0;
  }
  // Get the edge map (source -> {destination -> link})
  auto edges = graph.getEdges();
  // Distribute rank for each node v along its outgoing links.
  for (auto const &p : R) {
    const std::string &v = p.first;
    double rank_v = p.second;
    // Find the outdegree (number of links) for node v.
    double outdeg = 0.0;
    if (edges.find(v) != edges.end())
      outdeg = edges.at(v).size();
    if (outdeg > 0) {
      double distributed = rank_v / outdeg;
      for (auto const &dst : edges.at(v)) {
        const std::string &u = dst.first;
        result[u] += distributed;
      }
    }
  }
  return result;
}

// Compute PageRank exactly as described in the algorithm documentation.
void PageRank::computePageRank(Graph &graph, double d = 0.85, double tol = 1e-6,
                               int max_iter = 1000) {
  // Let S be any starting vector over pages.
  // Here, we choose S = uniform distribution.
  int N = graph.numberOfNodes();
  if (N == 0)
    return;

  // Initialize S and E as uniform.
  std::unordered_map<std::string, double> R; // R0
  std::unordered_map<std::string, double> E;
  double uniform_val = 1.0 / N;
  auto nodes = graph.getNodes();
  for (const auto &p : nodes) {
    R[p.first] = uniform_val;
    E[p.first] = uniform_val;
  }

  int iter = 0;
  double diff = std::numeric_limits<double>::max();

  // TODO: Does not deal with dangling links
  while (diff > tol && iter < max_iter) {
    // Step 1: R_next = A * R.
    std::unordered_map<std::string, double> R_next = multiplyA(graph, R);

    // Step 2: Compute d = ||R||₁ − ||R_next||₁.
    double norm_R = l1norm(R);
    double norm_R_next = l1norm(R_next);
    double delta_mass = norm_R - norm_R_next;

    // Step 3: Add d * E to R_next.
    for (auto &p : R_next) {
      p.second += delta_mass * E[p.first];
    }

    // Step 4: Compute convergence difference δ = ||R_next − R||₁.
    diff = 0.0;
    for (const auto &p : R) {
      diff += fabs(R_next[p.first] - p.second);
    }

    // Update for the next iteration.
    R = R_next;
    iter++;
  }

  // Update the graph with computed PageRank values.
  for (const auto &p : R) {
    graph.setNode(p.first, p.second);
  }

  std::cout << "PageRank converged after " << iter << " iterations with diff "
            << diff << std::endl;

  // Optionally print the PageRank for each node.
  for (const auto &p : R) {
    std::cout << "Node: " << p.first << " PageRank: " << p.second << std::endl;
  }
}
