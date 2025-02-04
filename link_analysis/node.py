from typing import override

class Node(object):
    """
    Each node is represented as pages of a URL
    Each node can be associated with an edge
        - There are two types of edges:
            1. An edge that is pointing to another node (edgesTo)
            2. An edge that is pointing to this node (edgesFrom)
    """
    def __init__(self, url:str) -> None:
        self.name: str = url
        self.edgesTo: set[str] = set()
        self.edgesFrom: set[str] = set()
        pass

    def getName(self) -> str:
        return self.name

    def removeEdge(self, edgeName:str ) -> None:
        self.edgesFrom.remove(edgeName)

    def addEdgeTo(self, edgeName:str ) -> None:
        self.edgesFrom.add(edgeName)

    def addEdgeFrom(self, edgeName:str ) -> None:
        self.edgesFrom.add(edgeName)

    def getEdgesFrom(self) -> set[str]:
        return self.edgesFrom

    def getEdgesTo(self) -> set[str]:
        return self.edgesTo

    @override
    # Assumes that the page is unique. That is, every page is its own node,
    # there will be no duplicate pages so it is safe to assume that the hash will be unique enough.
    def __hash__(self) -> int:
        # NOTE: Might cause an issue/error?
        return hash(self.name) + hash(self.edgesTo) + hash(self.edgesFrom)

    @override
    def __eq__(self, other) -> bool:
        return self.name == other.name
