/**
 * Each edge is representing links (URLs)
 */
#include "edge.h"
#include <string>

Edge::Edge(std::string edgeName, std::string from, std::string to) {
  link = edgeName;
  from = from;
  to = to;
}
