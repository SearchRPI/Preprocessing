from .node import Node

class Edge(object):
    """
    Each edge is a link that is connecting two different websites
    Each vertice is a page (node)

    Start node is the node that has an edge coming out of it
    End node is the node that the arrow is pointing to
    """
    def __init__(self, url:str, start:Node, end:Node ) -> None:
        self.url:str = url 
        self.start:Node = start
        self.end:Node = end
        pass

    def getPoints(self) -> tuple[Node,Node]: 
        return self.start,self.end
    
    def getEdgeName(self) -> str:
        return self.url
