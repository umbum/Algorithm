# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

class Tree(object):
    def __init__(self, _x):
        self.x = _x
        self.l = None
        self.r = None

cnt_distincts = []
max_distincts_count = 0

def dfs(T):
    if T is not None:
        T.visited = True
        cnt_distincts.append(T.x)
        print(cnt_distincts)
        if hasattr(T.l, 'visited') is False:
            dfs(T.l)
        if hasattr(T.r, 'visited') is False:
            dfs(T.r)
        cnt_distincts.remove(T.x)
    else:
        cnt_distincts_count = len(set(cnt_distincts))
        global max_distincts_count
        if max_distincts_count < cnt_distincts_count:
            max_distincts_count = cnt_distincts_count 

def solution(T):
    # write your code in Python 3.6
    dfs(T)
    return max_distincts_count

if __name__ == "__main__":
    t = Tree(4)
    t.l = Tree(5)
    t.l.l = Tree(4)
    t.l.l.l = Tree(5)
    t.l.l.r = Tree(3)
    t.l.l.r.l = Tree(2)

    t.r = Tree(6)
    t.r.l = Tree(1)
    t.r.r = Tree(6)

    print(solution(t))
    