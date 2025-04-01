#include "../includes/graph.h"
#include "../includes/pagerank.h"
#include <chrono>
#include <csignal>
#include <iostream>
#include <map>

using namespace std;
using namespace std::chrono;

void smallTestCase() {
  Graph graph;

  std::cout << "Large Test Case (~100 nodes)" << std::endl;

  // Create nodes: "1" to "100"
  for (int i = 1; i <= 100; i++) {
    graph.addNode(std::to_string(i));
  }

  // Create edges:
  // 1. Ring structure: each node points to the next (with wrap-around)
  for (int i = 1; i <= 100; i++) {
    std::string src = std::to_string(i);
    std::string dest = std::to_string((i % 100) + 1); // Wrap-around
    graph.addEdge(src, dest);
  }

  // 2. Additional edges: for each node, add an edge to the node two steps ahead
  // and three steps ahead
  for (int i = 1; i <= 100; i++) {
    std::string src = std::to_string(i);
    std::string dest2 = std::to_string(((i + 1) % 100) + 1);
    std::string dest3 = std::to_string(((i + 2) % 100) + 1);
    graph.addEdge(src, dest2);
    graph.addEdge(src, dest3);
  }

  // 3. More random-like cross links: for every 10th node, add extra edges to
  // simulate shortcuts
  for (int i = 1; i <= 100; i += 10) {
    std::string src = std::to_string(i);
    // Connect node i to nodes (i+15) and (i+20) (with wrap-around)
    std::string dest15 = std::to_string(((i + 14) % 100) + 1);
    std::string dest20 = std::to_string(((i + 19) % 100) + 1);
    graph.addEdge(src, dest15);
    graph.addEdge(src, dest20);
  }

  // Calculate PageRank
  PageRank pagerank;

  auto first_start = high_resolution_clock::now();

  std::unordered_map<std::string, double> res =
      pagerank.computePageRank(graph, 0.85, 1e-6, 100);

  auto first_stop = high_resolution_clock::now();

  auto first_duration = duration_cast<microseconds>(first_stop - first_start);

  // Create more edges:
  for (int i = 1; i <= 500; i++) {
    std::string src = std::to_string(i);
    std::string dest = std::to_string((i % 100) + 1); // Wrap-around
    graph.addEdge(src, dest);
  }

  auto second_start = high_resolution_clock::now();

  pagerank.computePageRank(graph, 0.85, 1e-6, 100, -1, 0.03, res);

  auto second_stop = high_resolution_clock::now();

  auto second_duration =
      duration_cast<microseconds>(second_stop - second_start);

  auto third_start = high_resolution_clock::now();

  pagerank.computePageRank(graph, 0.85, 1e-6, 100);

  auto third_stop = high_resolution_clock::now();

  auto third_duration = duration_cast<microseconds>(third_stop - third_start);

  cout << "\n\n\n\nTime difference to run the third "
          "computePageRank() function: "
       << third_duration.count() << " ms\n";

  cout << "\n\n\n\nTime difference to run the second "
          "computePageRank() function: "
       << second_duration.count() << " ms\n";

  cout << "\n\n\n\nTime difference to run the first and the second "
          "computePageRank() function: "
       << first_duration.count() - second_duration.count() << " ms\n";
}

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

  smallTestCase();

  return 0;
}
