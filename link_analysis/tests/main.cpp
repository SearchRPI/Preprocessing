#include "../includes/graph.h"
#include "../includes/pagerank.h"
#include <csignal>
#include <iostream>

using namespace std;

int main() {
  Graph graph;

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

  // Calculate PageRank
  PageRank pagerank;
  pagerank.computePageRank(graph, 0.85, 1e-8, 100);

  std::cout << "\n\n\n\n\n\n";

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
  pagerank1.computePageRank(graph2, .85, 1e-8, 100);

  return 0;
}

//
// void separator() {
//   std::cout << "=----------------------------------="
//                "\n\n\n\n\n\n\n\n\n\n\n\n";
//
//   std::cout << "=----------------------------------=";
// }
//
// void testFigure3() {
//   Graph graph;
//   cout << "Figure 3" << endl;
//
//   graph.addNode("A", 0.0);
//   graph.addNode("B", 0.0);
//   graph.addNode("C", 0.0);
//
//   graph.setEdge("A", "B", "http://link_from_A_to_B");
//   graph.setEdge("A", "C", "http://link_from_A_to_C");
//   graph.setEdge("B", "C", "http://link_from_B_to_C");
//   graph.setEdge("C", "A", "http://link_from_C_to_A");
//
//   // Now compute PageRank.
//   PageRank pagerank;
//   pagerank.computePageRank(graph, 0.85, 1e-6, 100);
// }
//
// /**
//  * @brief Tests whether there are no infinite sinks. It will converge
//  eventually
//  * and should not infinite loop to figure out the page rank of "A"
//  */
// void testFigure4() {
//   Graph graph;
//   cout << "Figure 4" << endl;
//
//   graph.addNode("A", 0.0); // Top left
//   graph.addNode("B", 0.0); // Bottom left
//   graph.addNode("C", 0.0); // Top right
//
//   graph.setEdge("A", "B", "http://link_from_A_to_B");
//   graph.setEdge("B", "C", "http://link_from_B_to_C");
//   graph.setEdge("C", "A", "http://link_from_C_to_A");
//
//   // Now compute PageRank.
//   PageRank pagerank;
//   pagerank.computePageRank(graph, 0.85, 1e-6, 100);
// }
//
// /**
//  * @brief Tests whether pagerank counts for dangling pages (i.e. no out
//  links)
//  */
// void testDangling() {
//   Graph graph;
//   cout << "Dangling" << endl;
//
//   graph.addNode("A", 0.0); // Top left
//   graph.addNode("B", 0.0); // Bottom left
//   graph.addNode("C", 0.0); // Top right
//
//   graph.setEdge("A", "B", "http://link_from_A_to_B");
//   graph.setEdge("B", "C", "http://link_from_B_to_C");
//
//   // Now compute PageRank.
//   PageRank pagerank;
//   pagerank.computePageRank(graph, 0.85, 1e-6, 100);
// }
//
// void testNetworkxTestCase() {
//   Graph graph;
//
//   graph.addNode("1", 0.0);
//   graph.addNode("2", 0.0);
//   graph.addNode("3", 0.0);
//   graph.addNode("4", 0.0);
//   graph.addNode("5", 0.0);
//   graph.addNode("6", 0.0);
//
//   // No need for edge name
//   graph.setEdge("1", "2", "");
//   graph.setEdge("1", "3", "");
//   graph.setEdge("3", "1", "");
//   graph.setEdge("3", "2", "");
//   graph.setEdge("3", "5", "");
//   graph.setEdge("4", "5", "");
//   graph.setEdge("4", "6", "");
//   graph.setEdge("5", "4", "");
//   graph.setEdge("5", "6", "");
//   graph.setEdge("6", "4", "");
//
//   PageRank pagerank;
//   pagerank.computePageRank(graph, 0.90, 1e-8, 100);
// }
//
// int main() {
//   testFigure3();
//
//   separator();
//
//   testFigure4();
//
//   separator();
//
//   testDangling();
//
//   separator();
//
//   testNetworkxTestCase();
//
//   return 0;
// }
