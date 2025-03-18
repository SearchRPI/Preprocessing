#include "../includes/pagerank.h"
#include <unordered_set>
#include <vector>

using namespace std;

void PageRank::computePageRank(Graph &graph, double alpha, double epsilon,
                               int maxIterations) {

  // Retrieve nodes and the adjacency list from the graph.
  unordered_set nodes = graph.getNodes();
  unordered_map<string, vector<string>> adjList = graph.getAdjacencyList();
  int N = nodes.size();

  // If the graph is empty return an empty map.
  if (N == 0) {
    return;
  }

  // Create a vector of nodes for consistent ordering.
  vector nodeList(nodes.begin(), nodes.end());

  // Initialize PageRank and newPageRank maps.
  unordered_map<string, double> pageRank;
  unordered_map<string, double> newPageRank;
  // Teleportation/personalization vector (uniform by default)
  unordered_map<string, double> p;
  // Dangling weights. By default, if no custom dangling vector is provided,
  // we use the personalization vector.
  unordered_map<string, double> danglingWeights;

  for (const string &node : nodeList) {
    pageRank[node] = 1.0 / N;
    newPageRank[node] = 0.0;
    p[node] = 1.0 / N;
    danglingWeights[node] = 1.0 / N; // default dangling weight = uniform
  }

  double delta = std::numeric_limits<double>::max();
  int iteration = 0;

  while (delta > epsilon && iteration < maxIterations) {
    // Reset newPageRank for this iteration.
    for (const string &node : nodeList) {
      newPageRank[node] = 0.0;
    }

    // Sum contribution from dangling nodes.
    double danglingSum = 0.0;

    // Each node distributes its rank.
    for (const string &node : nodeList) {
      // If the node has outgoing links, distribute its PageRank.
      if (!adjList[node].empty()) {
        double share = pageRank[node] / adjList[node].size();
        // Add contribution to each neighbor.
        for (const string &nbr : adjList[node]) {
          newPageRank[nbr] += alpha * share;
        }
      } else {
        // Dangling node; add its rank to the dangling sum.
        danglingSum += pageRank[node];
      }
    }

    // Distribute the dangling sum to every node using the dangling weights.
    for (const string &node : nodeList) {
      newPageRank[node] += alpha * danglingSum * danglingWeights[node];
    }

    // Add the teleportation (random surfer) component.
    for (const string &node : nodeList) {
      newPageRank[node] += (1.0 - alpha) * p[node];
    }

    // Compute convergence delta as the L1 norm difference.
    delta = 0.0;
    for (const string &node : nodeList) {
      delta += fabs(newPageRank[node] - pageRank[node]);
    }

    // Prepare for next iteration.
    pageRank = newPageRank;
    iteration++;
  }

  // Optionally output the PageRank results.
  for (const string &node : nodeList) {
    cout << "PageRank of node " << node << ": " << pageRank[node] << endl;
  }
}
