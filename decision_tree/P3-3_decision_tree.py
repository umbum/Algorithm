#coding: utf-8
'''    n=6짜리 Decision Tree 그리기.
(i:j)로 나타내며 left subtree는 x_i < x_j     right subtree는 x_i > x_j

A. left subtree로 내려갈 때.
    1. 우측 끝에 다음 원소 추가
    2. 더 이상 붙일 원소가 없으면 멈추기
B. right subtree로 내려갈 때.
    0. i:j 스왑하기
    1. :를 좌측으로 이동시키기.
        (e.g. (2,1:3)이면 0,1step을 완료한 right child는 (2:3,1)
    2. 더 이상 좌측으로 갈 수 없으면 우측 끝에 다음 원소 추가
    3. 더 이상 붙일 원소가 없으면 멈추기
'''

import graphviz


class DecisionTree():
    def __init__(self, n):
        self.G = graphviz.Graph()
        self.n = n

    def build(self):
        this_node = "1;2"
        self.G.node(this_node, this_node)
        self.left_subtree(this_node)
        self.right_subtree(this_node)

    def left_subtree(self, parent):
        '''
        :param n: MAX count
        :param parent: G.node
        :return: void
        '''
        if (len(parent) < 2*self.n - 1):
            # 우측 끝에 다음 원소 추가
            this_node = parent.replace(";", ",") + ";" + str(int(((len(parent) - 3)/2 + 3)))
            self.G.node(this_node, this_node[-3:])
            self.G.edge(parent, this_node)
            self.left_subtree(this_node)
            self.right_subtree(this_node)
        else:
            # 더 이상 붙일 원소가 없으면 멈추기
            this_node = parent.replace(";", ",")
            self.G.edge(parent, this_node)

    def right_subtree(self, parent):
        # i:j 스왑하기
        idx = parent.index(";")
        this_node = parent[:idx-1] + parent[idx+1] + "," + parent[idx-1] + parent[idx+2:]
        if (idx != 1):
            # :를 좌측으로 이동시키기.
            this_node = this_node[:idx-2] + ";" + this_node[idx-1:]
            self.G.node(this_node, this_node[idx-3:idx])
            self.G.edge(parent, this_node)
            self.left_subtree(this_node)
            self.right_subtree(this_node)
        else:
            if (len(parent) < 2*self.n - 1):
                # 더 이상 좌측으로 갈 수 없으면 우측 끝에 다음 원소 추가
                this_node = this_node + ";" + str(int(((len(parent) - 3)/2 + 3)))
                self.G.node(this_node, this_node[-3:])
                self.G.edge(parent, this_node)
                self.left_subtree(this_node)
                self.right_subtree(this_node)
            else:
                # 더 이상 붙일 원소가 없으면 멈추기
                self.G.edge(parent, this_node)



if __name__ == "__main__":
    tree = DecisionTree(7)
    tree.build()
    tree.G.render("decision_tree.gv", view=True)
    # tree.G.source
