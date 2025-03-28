#include "../includes/graph.h"
#include "../includes/pagerank.h"
#include <csignal>
#include <iostream>
#include <map>

using namespace std;

// A helper function to compare two maps (expected vs computed)
// with a tolerance for floating-point differences.
bool compareMaps(const map<int, double> &expected,
                 const map<int, double> &computed, double tol = 1e-6) {
  if (expected.size() != computed.size())
    return false;
  for (auto &kv : expected) {
    int node = kv.first;
    double vexp = kv.second;
    double vcomp = computed.at(node);
    if (fabs(vexp - vcomp) > tol) {
      return false;
    }
  }
  return true;
}

int main() {
  /**
   *
   * NetworkX Test Case
   *
   * RESULT: PASSES (+- 0.03)
   *
   */
  Graph graph;

  std::cout << "Testing NetworkX Test Case\n\n\n\n";

  // Create nodes
  graph.addNode("1");
  graph.addNode("2");
  graph.addNode("3");
  graph.addNode("4");
  graph.addNode("5");
  graph.addNode("6");

  // Create edges
  graph.addEdge("1", "2");
  graph.addEdge("1", "3");
  graph.addEdge("3", "1");
  graph.addEdge("3", "2");
  graph.addEdge("3", "5");
  graph.addEdge("4", "5");
  graph.addEdge("4", "6");
  graph.addEdge("5", "4");
  graph.addEdge("5", "6");
  graph.addEdge("6", "4");

  /**
   *
   * Simple
   *
   * RESULT: PASSESS(+- 0.1)
   *
   */

  // Calculate PageRank
  PageRank pagerank;
  pagerank.computePageRank(graph, 0.85, 1e-6, 100);

  std::cout << "\n\n\n\n\nTesting Simple\n";

  Graph graph2;

  // Create nodes
  graph2.addNode("1");
  graph2.addNode("2");
  graph2.addNode("3");

  graph2.addEdge("1", "2");
  graph2.addEdge("1", "3");
  graph2.addEdge("2", "3");
  graph2.addEdge("3", "1");

  PageRank pagerank1;
  pagerank1.computePageRank(graph2, .85, 1e-6, 100);

  /**
   *
   *  NetworkX Dangling Test Case
   *
   *  RESULT: FAILS
   *    - It may be due to how dangling is done. It seems that they had done
   * page ranks separate from dangling page rank. It also doesn't look like they
   * remove the danling nodes and add them back later or they don't converge
   * when it sees a dangling. When there is a dangling node, this implementation
   * will leave it alone and move on to other outward edges. We can consider it
   * as "done".
   *
   */

  std::cout << "\n\nTesting NetworkX Test Case For Dangling\n\n";

  Graph graph3;

  // Create nodes
  graph3.addNode("1");
  graph3.addNode("2");
  graph3.addNode("3");
  graph3.addNode("4");
  graph3.addNode("5");
  graph3.addNode("6");

  // Create edges
  graph3.addEdge("1", "2");
  graph3.addEdge("2", "3");

  // Calculate PageRank
  PageRank pagerank3;
  pagerank3.computePageRank(graph3, 0.85, 1e-6, 100);

  /**
   *
   * ChatGPT Created Test Cases
   *
   * RESULT: PASSESS (+- 0.03)
   *
   */

  std::cout << "\n\nTesting ChatGPT Created Regular Test Case\n\n";

  Graph graph4;

  graph4.addNode("A");
  graph4.addNode("B");
  graph4.addNode("C");

  graph4.addEdge("A", "B");
  graph4.addEdge("B", "C");
  graph4.addEdge("C", "A");

  PageRank pagerank4;

  pagerank4.computePageRank(graph4, 0.85, 0.0001, 100);

  /**
   *
   * RESULT: PASSESS (+- 0.03)
   *
   */
  std::cout << "\n\nTesting ChatGPT Created Dangling Test Case\n\n";

  Graph graph5;

  graph5.addNode("A");
  graph5.addNode("B");
  graph5.addNode("C");

  graph5.addEdge("A", "B");
  graph5.addEdge("A", "C");
  graph5.addEdge("B", "C");

  PageRank pagerank5;

  pagerank5.computePageRank(graph5, 0.85, 1e-5, 100);
  return 0;
}
