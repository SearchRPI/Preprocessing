#include "pagerank.h"
#include <iostream>

using namespace std;

int main() {
  Graph graph;
  // Example: Manually adding nodes and edges.
  // In a full implementation these would be read from file using
  // graph.readFromFile("filename.txt") For demonstration we assume URLs "A",
  // "B", "C", "D" as nodes:
  graph.setNode("A", 0.0);
  graph.setNode("B", 0.0);
  graph.setNode("C", 0.0);
  graph.setNode("D", 0.0);

  graph.setEdge("A", "B", "http://link_from_A_to_B");
  graph.setEdge("A", "C", "http://link_from_A_to_C");
  graph.setEdge("B", "C", "http://link_from_B_to_C");
  graph.setEdge("C", "A", "http://link_from_C_to_A");
  graph.setEdge("D", "A", "http://link_from_D_to_A");
  graph.setEdge("D", "C", "http://link_from_D_to_C");

  // Now compute PageRank.
  PageRank pagerank;
  pagerank.computePageRank(graph, 0.85, 1e-6, 100);

  // Display the computed PageRank scores.
  cout << "Graph 1" << endl;
  cout << "PageRank scores:" << endl;
  unordered_map<string, double> finalNodes = graph.getNodes();
  for (const auto &entry : finalNodes) {
    cout << "Node " << entry.first << ": " << entry.second << endl;
  }

  // Make sure that circular graphs (node that always has a link to another
  // node) works and can end leaving an infinite loop and rank the pages/nodes
  Graph graph1;

  graph1.setNode("A", 0.0);
  graph1.setNode("B", 0.0);
  graph1.setNode("C", 0.0);
  graph1.setNode("D", 0.0);

  graph1.setEdge("A", "B", "http://link_from_A_to_B");
  graph1.setEdge("A", "C", "http://link_from_A_to_C");
  graph1.setEdge("A", "D", "http://link_from_A_to_D");

  graph1.setEdge("B", "A", "http://link_from_B_to_A");
  graph1.setEdge("B", "C", "http://link_from_B_to_C");
  graph1.setEdge("B", "D", "http://link_from_B_to_D");

  graph1.setEdge("C", "A", "http://link_from_C_to_A");
  graph1.setEdge("C", "B", "http://link_from_C_to_B");
  graph1.setEdge("C", "C", "http://link_from_C_to_C");

  graph1.setEdge("D", "A", "http://link_from_D_to_A");
  graph1.setEdge("D", "B", "http://link_from_D_to_B");
  graph1.setEdge("D", "C", "http://link_from_D_to_C");

  pagerank.computePageRank(graph1, 0.90, 1e-6, 1000);

  cout << "Graph 2" << endl;
  cout << "PageRank scores:" << endl;
  unordered_map<string, double> finalNodes1 = graph1.getNodes();
  for (const auto &entry : finalNodes1) {
    cout << "Node " << entry.first << ": " << entry.second << endl;
  }

  return 0;
}
