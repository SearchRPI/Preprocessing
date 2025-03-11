#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h" // Include your Graph header file
#include <cmath>
#include <iostream>
#include <unordered_map>

class PageRank {
public:
  void computePageRank(Graph &graph, double damping, double tol, int maxIter);
};

#endif
