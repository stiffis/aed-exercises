# Binary Search Tree (BST) implementation in Python
class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.data = key

class BST:
    def __init__(self):
        self.root = None

    def insertNode(self, key):
        if self.root is None:
            self.root = Node(key)
        else:
            self._insert_rec(self.root, key)

    def _insert_rec(self, node, key):
        if key < node.data:
            if node.left is None:
                node.left = Node(key)
            else:
                self._insert_rec(node.left, key)
        else:
            if node.right is None:
                node.right = Node(key)
            else:
                self._insert_rec(node.right, key)

