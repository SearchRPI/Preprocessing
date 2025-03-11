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

  // Suppose the graph has the following hyperlink structure:
  // A -> B, A -> C
  // B -> C
  // C -> A
  // D -> A, D -> C
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
  cout << "PageRank scores:" << endl;
  unordered_map<string, double> finalNodes = graph.getNodes();
  for (const auto &entry : finalNodes) {
    cout << "Node " << entry.first << ": " << entry.second << endl;
  }

  return 0;
}
