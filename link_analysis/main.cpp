#include "pagerank.h"
#include <iostream>

using namespace std;

void separator() {
  std::cout << "=----------------------------------="
               "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

  std::cout << "=----------------------------------=\n";
}

void testFigure3() {
  Graph graph;
  cout << "Figure 3" << endl;

  graph.setNode("A", 0.0);
  graph.setNode("B", 0.0);
  graph.setNode("C", 0.0);

  graph.setEdge("A", "B", "http://link_from_A_to_B");
  graph.setEdge("A", "C", "http://link_from_A_to_C");
  graph.setEdge("B", "C", "http://link_from_B_to_C");
  graph.setEdge("C", "A", "http://link_from_C_to_A");

  // Now compute PageRank.
  PageRank pagerank;
  pagerank.computePageRank(graph, 0.85, 1e-6, 100);

  // Display the computed PageRank scores.
  cout << "PageRank scores:" << endl;
  unordered_map<string, double> finalNodes = graph.getNodes();
  for (const auto &entry : finalNodes) {
    cout << "Node " << entry.first << ": " << entry.second << endl;
  }
}

/**
 * @brief Tests whether there are no infinite sinks. It will converge eventually
 * and should not infinite loop to figure out the page rank of "A"
 */
void testFigure4() {
  Graph graph;
  cout << "Figure 4" << endl;

  graph.setNode("A", 0.0); // Top left
  graph.setNode("B", 0.0); // Bottom left
  graph.setNode("C", 0.0); // Top right

  graph.setEdge("A", "B", "http://link_from_A_to_B");
  graph.setEdge("B", "C", "http://link_from_B_to_C");
  graph.setEdge("C", "A", "http://link_from_C_to_A");

  // Now compute PageRank.
  PageRank pagerank;
  pagerank.computePageRank(graph, 0.85, 1e-6, 100);

  // Display the computed PageRank scores.
  cout << "PageRank scores:" << endl;
  unordered_map<string, double> finalNodes = graph.getNodes();
  for (const auto &entry : finalNodes) {
    cout << "Node " << entry.first << ": " << entry.second << endl;
  }
}

/**
 * @brief Tests whether pagerank counts for dangling pages (i.e. no out links)
 */
void testDangling() {
  Graph graph;
  cout << "Dangling" << endl;

  graph.setNode("A", 0.0); // Top left
  graph.setNode("B", 0.0); // Bottom left
  graph.setNode("C", 0.0); // Top right

  graph.setEdge("A", "B", "http://link_from_A_to_B");
  graph.setEdge("B", "C", "http://link_from_B_to_C");

  // Now compute PageRank.
  PageRank pagerank;
  pagerank.computePageRank(graph, 0.85, 1e-6, 100);

  // Display the computed PageRank scores.
  cout << "PageRank scores:" << endl;
  unordered_map<string, double> finalNodes = graph.getNodes();
  for (const auto &entry : finalNodes) {
    cout << "Node " << entry.first << ": " << entry.second << endl;
  }
}

int main() {
  testFigure3();

  separator();

  testFigure4();

  separator();

  testDangling();

  return 0;
}
