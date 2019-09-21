"""
이 문제는 tree의 depth가 1000이하라고 했다.
tree를 index로 구성(left를 2i+1로 접근하는 방식)하는 경우... 배열을 2^1001만큼 잡을 수 있어야 함.
left, right의 class를 만들어서 푸는게 옳다... 
nodeinfo의 길이는 10000 이하인데 depth가 1000 이하이면 극단적으로 깊은 트리가 될 수도 있는거라... index방식은 아주 안좋다.
"""
import sys
sys.setrecursionlimit(10**6)
# python 기본 재귀 limit이 1000이라서, 그 것 때문에 런타임 에러가 떴었음. 제한을 늘려준다.

class Node:
    def __init__(self, n, axis):
        self.n = n
        self.x, self.y = axis
        self.left = None
        self.right = None

    def __repr__(self):
        return "[{} ({},{})]".format(self.n, self.x, self.y)

class Tree:
    def __init__(self, root):
        self.root = root

    def insert(self, target):
        node = self.root
        while True:
            if (target.x == node.x):
                print("모든 x는 다르다 했으니 이게 나올 리가 없다.")
                return -1
            elif (target.x < node.x):
                if (node.left is None):
                    node.left = target
                    return
                else:
                    node = node.left
            else:
                if (node.right is None):
                    node.right = target
                    return
                else:
                    node = node.right
        print("여기는 들어와서는 안된다.")

    def preorder(self):
        result = []
        self.__preorder(result, self.root)
        return result

    def __preorder(self, result, node):
        if (node is None):
            return
        
        result.append(node.n)
        self.__preorder(result, node.left)
        self.__preorder(result, node.right)

    
    def postorder(self):
        result = []
        self.__postorder(result, self.root)
        return result
    
    def __postorder(self, result, node):
        if (node is None):
            return
        self.__postorder(result, node.left)
        self.__postorder(result, node.right)
        result.append(node.n)
    


def solution(nodeinfo):
    nodes = list(map(lambda x: Node(x[0], x[1]), enumerate(nodeinfo, 1)))
    sortedNodes = sorted(nodes, key=lambda node:node.y, reverse=True)
    # print(sortedNodes)
    
    root = sortedNodes[0]
    tree = Tree(root)
    for node in sortedNodes[1:]:
        tree.insert(node)

    return [tree.preorder(), tree.postorder()]
    

print(solution([[5,3],[11,5],[13,3],[3,5],[6,1],[1,3],[8,6],[7,2],[2,2]]))
print(solution([[0,0]]))