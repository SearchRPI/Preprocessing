#include "../includes/pagerank.h"
#include <unordered_set>

using namespace std;

void PageRank::computePageRank(Graph &graph, double alpha, double epsilon,
                               int maxIterations) {
  unordered_map<std::string, double> pageRank;
  unordered_map<std::string, double> newPageRank;

  unordered_set<std::string> nodes = graph.getNodes();
  unordered_map<std::string, std::vector<std::string>> adjacencyList =
      graph.getAdjacencyList();

  // Initialize PageRank scores
  for (std::string node : nodes) {
    pageRank[node] = 1.0 / nodes.size();
  }

  double delta = 1.0;
  int iteration = 0;

  while (delta > epsilon && iteration < maxIterations) {
    // Calculate new PageRank scores
    for (std::string node : nodes) {
      newPageRank[node] = 0.0;
    }

    for (std::string node : nodes) {
      if (!adjacencyList[node].empty()) {
        for (std::string neighbor : adjacencyList[node]) {
          newPageRank[neighbor] +=
              alpha * pageRank[node] / adjacencyList[node].size();
        }
      } else {
        for (std::string otherNode : nodes) {
          newPageRank[otherNode] += alpha * pageRank[node] / nodes.size();
        }
      }
    }

    // Add random surfer component
    for (std::string node : nodes) {
      newPageRank[node] += (1 - alpha) / nodes.size();
    }

    // Calculate delta
    double norm1 = 0.0;
    for (std::string node : nodes) {
      norm1 += abs(pageRank[node]);
    }

    double norm2 = 0.0;
    for (std::string node : nodes) {
      norm2 += abs(newPageRank[node]);
    }

    double d = abs(norm1 - norm2);

    // Normalize new PageRank scores
    for (std::string node : nodes) {
      newPageRank[node] = newPageRank[node] + d / nodes.size();
    }

    // Calculate delta
    delta = 0.0;
    for (std::string node : nodes) {
      delta += abs(newPageRank[node] - pageRank[node]);
    }

    pageRank = newPageRank;
    iteration++;
  }

  // Print PageRank scores
  for (std::string node : nodes) {
    cout << "PageRank of node " << node << ": " << pageRank[node] << endl;
  }
}
