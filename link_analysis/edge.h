#ifndef EDGE_H
#define EDGE_H

#include <string>
class Edge {

public:
  Edge(std::string edgeName, std::string from, std::string to);
  size_t operator()(const Edge e) const;
  struct EdgeHash {
    size_t operator()(const Edge &e) const {
      // Compute individual hashes for each string member.
      std::size_t h1 = std::hash<std::string>{}(e.link);
      std::size_t h2 = std::hash<std::string>{}(e.from);
      std::size_t h3 = std::hash<std::string>{}(e.to);

      // Combine the hashes.
      std::size_t seed = h1;
      seed ^= h2 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      seed ^= h3 + 0x9e3779b9 + (seed << 6) + (seed >> 2);
      return seed;
    }
  };

private:
  std::string link;
  std::string from;
  std::string to;
};

#endif
