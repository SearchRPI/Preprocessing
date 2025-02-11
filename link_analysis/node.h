#include <functional>
#include <string>
class Node {
public:
  Node();
  struct NodeHash {
    size_t operator()(const Node &node) {
      return std::hash<std::string>{}(node.vertice);
    }
  };

private:
  std::string vertice;
};
