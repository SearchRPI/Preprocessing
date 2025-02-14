#include "../graph.h"
#include <cassert>

bool testEmptyGraph() {
  Graph graph;

  // Test number of edges is correct
  assert(graph.numberOfEdges() == 0);

  // Test number of nodes is correct
  assert(graph.numberOfNodes() == 0);

  // Test whether node is in graph in empty graph
  assert(graph.nodeInGraph("") == false);

  return true;
}

bool testOneNodeGraph() {
  Graph graph;

  graph.setNode("http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf", .03);

  assert(graph.numberOfNodes() == 1);

  assert(graph.nodeVal("http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf") ==
         0.03);

  assert(graph.numberOfEdges() == 0);

  graph.clear();
  assert(graph.numberOfNodes() == 0);

  return true;
}

bool testTwoNodesGraph() {
  Graph graph;

  graph.setNode("https://ciir.cs.umass.edu/downloads/SEIRiP.pdf", 0.05);
  graph.setNode("http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf", 0.03);

  assert(graph.nodeVal("https://ciir.cs.umass.edu/downloads/SEIRiP.pdf") ==
         0.05);
  assert(graph.nodeVal("http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf") ==
         0.03);

  graph.setEdge("https://ciir.cs.umass.edu/downloads/SEIRiP.pdf",
                "http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf",
                "https://github.com/networkx/networkx/blob/main/networkx/"
                "algorithms/link_analysis/pagerank_alg.py");

  assert(graph.numberOfEdges() == 1);
  assert(graph.edgeLink("https://ciir.cs.umass.edu/downloads/SEIRiP.pdf",
                        "http://ilpubs.stanford.edu:8090/422/1/1999-66.pdf") ==
         "https://github.com/networkx/networkx/blob/main/networkx/"
         "algorithms/link_analysis/pagerank_alg.py");

  graph.clear();
  assert(graph.numberOfEdges() == 0);
  assert(graph.numberOfNodes() == 0);
  assert(graph.getEdges().size() == 0);
  assert(graph.getNodes().size() == 0);

  return true;
}

int main() {
  assert(testEmptyGraph() == true);
  assert(testOneNodeGraph() == true);
  assert(testTwoNodesGraph() == true);
  return 0;
}
