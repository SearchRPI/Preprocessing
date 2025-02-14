#include "graph.h"
#include <string>

class PageRank {
public:
  void initGraph(std::string fileName);

  Graph getGraph() { return graph; }

private:
  Graph graph;
};
