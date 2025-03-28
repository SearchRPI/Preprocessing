#ifndef PAGERANK_H
#define PAGERANK_H

#include "graph.h" // Include your Graph header file
#include <cmath>
#include <iostream>
#include <unordered_map>

class PageRank {
public:
  /**
   * @brief Returns the page rank of the entire graph. That is, rank each page
   * using a page rank algorithm.
   *
   * @param graph The graph that we want to calculate the page ranks of.
   * @param c The normalization factor so that the total rank of all web pages
   * is constant. It is used to calculate the value for R, the page rank for the
   current page/node.
   * @param epsilon The value used for the convergence threshold. It is also
   used to determine when to stop iterating. Similar to the usage to the maxIter
   value.
   * @param maxIter The max iterations before we stop and converge. This is used
   * to help prevent infinite loops from happening, typically graphs that has
   * all nodes reach all other nodes.
   * @param initialPageRank The initial page ranks of the graph that is
   optional. If it is empty, the entire page rank algorithm will be ran again
   and will recalculate all of the page ranks. However, if it is not empty, it
   will re use some of the previous values and will handle the new nodes that
   might be added. This will be initially empty, once there are initial values,
   this will just be the old data in the database. This will act as the "cached"
   values that we can reuse instead of recalculating.
   * @param e A "teleportation" or randomness factor that can be specified by
   * the user or uses the default value (1 / total number of nodes). It is the
   * probability that a user might jump to a different page due to being in a
   * infinite loop or are "stuck".
   */
  std::unordered_map<std::string, double> computePageRank(
      Graph &graph, double c, double epsilon, int maxIter, double e = -1,
      double updateThreshold = 0,
      const std::unordered_map<std::string, double> &initialPageRank = {});
};

#endif
