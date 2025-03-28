#include "../includes/pagerank.h"
#include <cmath>
#include <queue>
#include <unordered_set>

std::unordered_map<std::string, double> PageRank::computePageRank(
    Graph &graph, double c, double epsilon, int maxIter, double e,
    double updateThreshold,
    const std::unordered_map<std::string, double> &initialPageRank) {
  // Retrieve nodes and the forward adjacency list.
  std::unordered_set<std::string> nodes = graph.getNodes();
  std::unordered_map<std::string, std::vector<std::string>> forwardAdj =
      graph.getAdjacencyList();
  int N = nodes.size();
  if (N == 0)
    return {};

  // Consistent ordering.
  std::vector<std::string> nodeList(nodes.begin(), nodes.end());

  // Build reverse mapping (incoming list) and compute out-degrees.
  std::unordered_map<std::string, std::vector<std::string>> incoming;
  std::unordered_map<std::string, int> outDegree;
  for (const auto &node : nodeList) {
    incoming[node] = std::vector<std::string>();
    outDegree[node] = forwardAdj[node].size();
  }
  for (const auto &pair : forwardAdj) {
    const std::string &u = pair.first;
    for (const std::string &v : pair.second) {
      incoming[v].push_back(u);
    }
  }

  // Teleportation probability: if e is not provided, use uniform.
  if (e == -1) {
    e = 1.0 / N;
  }

  // Initialize PageRank vector. For nodes missing in the provided
  // vector (or in case of new nodes), fall back to uniform.
  std::unordered_map<std::string, double> pageRank;
  for (const std::string &node : nodeList) {
    if (initialPageRank.find(node) != initialPageRank.end()) {
      pageRank[node] = initialPageRank.at(node);
    } else {
      pageRank[node] = 1.0 / N;
    }
  }

  // We'll use a queue to track nodes that need re-evaluation.
  std::queue<std::string> dirtyQueue;
  std::unordered_set<std::string> inQueue;
  // Initially, add all nodes.
  for (const auto &node : nodeList) {
    dirtyQueue.push(node);
    inQueue.insert(node);
  }

  int iteration = 0;
  // We also keep track of the global dangling mass for nodes with zero
  // out-degree.
  auto computeDanglingMass = [&]() -> double {
    double danglingMass = 0.0;
    for (const auto &node : nodeList) {
      if (outDegree[node] == 0) {
        danglingMass += pageRank[node];
      }
    }
    return danglingMass / N;
  };

  // Iteratively update only the nodes that are “dirty.”
  while (!dirtyQueue.empty() && iteration < maxIter) {
    std::string u = dirtyQueue.front();
    dirtyQueue.pop();
    inQueue.erase(u);

    // Compute new PageRank for node u.
    double sum = 0.0;
    // Sum contributions from all in-neighbors that have outgoing links.
    for (const std::string &v : incoming[u]) {
      if (outDegree[v] > 0) {
        sum += pageRank[v] / double(outDegree[v]);
      }
    }
    // Get the dangling mass contribution.
    double danglingContribution = computeDanglingMass();
    // New value: note that dangling mass is a global term added uniformly.
    double newVal = c * (sum + danglingContribution) + (1.0 - c) * e;

    // If the change is significant, update and mark dependent nodes.
    if (fabs(newVal - pageRank[u]) > updateThreshold) {
      pageRank[u] = newVal;
      // For all nodes that depend on u (i.e. u is an in-neighbor),
      // add them to the dirty queue if not already present.
      for (const std::string &w : forwardAdj[u]) {
        if (inQueue.find(w) == inQueue.end()) {
          dirtyQueue.push(w);
          inQueue.insert(w);
        }
      }
      // In some cases, it may be worthwhile to also re-check u's own
      // in-neighbors.
      for (const std::string &w : incoming[u]) {
        if (inQueue.find(w) == inQueue.end()) {
          dirtyQueue.push(w);
          inQueue.insert(w);
        }
      }
    }
    iteration++;
  }

  // (Optional) A final pass to ensure that the global mass is correctly
  // distributed.
  double totalMass = 0.0;
  for (const auto &pair : pageRank) {
    totalMass += pair.second;
  }
  double massError = 1.0 - totalMass;
  if (fabs(massError) > epsilon) {
    for (auto &pair : pageRank) {
      pair.second += massError * e;
    }
  }

  // TODO: Update the node's page rank at the very end.

  // Print final PageRank scores.
  for (const std::string &node : nodeList) {
    std::cout << "PageRank for node " << node << ": " << pageRank[node]
              << std::endl;
  }
  std::cout << "\n";

  return pageRank;
}
