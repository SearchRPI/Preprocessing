from link_analysis.edges import Edge
from link_analysis.node import Node


class Graph(object):
    def __init__(self) -> None:
        self.graph: dict[str, Node] = dict()
        pass

    def addNode(self, nodeName: str) -> None:
        self.graph[nodeName] = Node(nodeName)

    def addEdge(self, start:str, end:str, edgeName:str) -> None:
        fromNode:Node = self.graph[start]
        if not self.graph.__contains__(start):
            fromNode:Node = Node(start)

        toNode:Node = self.graph[end]
        if not self.graph.__contains__(end):
            toNode:Node = Node(end)

        edge:Edge = Edge(edgeName, fromNode, toNode )

