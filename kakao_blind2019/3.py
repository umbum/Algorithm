from pprint import pprint

def rotate(m):
    N = len(m)
    ret = [[0] * N for _ in range(N)]

    for r in range(N):
        for c in range(N):
            ret[c][N-1-r] = m[r][c]
    return ret


def solve(key, _lock):
    N = len(_lock)
    M = len(key)
    for i in range(1, M + N):
        for j in range(1, M + N):
            lock = [row[:] for row in _lock]
            if (i < M):
                if (j < M):
                    # 여기서 loop를 2중으로 돌아야함. 2d array니까.
                    for p in range(i):
                        for q in range(j):
                            lock[p][q] += key[M - i + p][M -j + q]
                elif (M <= j <= N):
                    for p in range(i):
                        for q in range(M):
                            lock[p][j - M + q] += key[M - i + p][q]
                else:
                    for p in range(i):
                        for q in range(M - (j - N)):
                            lock[p][j - M + q] += key[M - i + p][q]
            elif (M <= i <= N):
                if (j < M):
                    # 여기서 loop를 2중으로 돌아야함. 2d array니까.
                    for p in range(M):
                        for q in range(j):
                            lock[i - M + p][q] += key[p][M -j + q]
                elif (M <= j <= N):
                    for p in range(M):
                        for q in range(M):
                            lock[i - M + p][j - M + q] += key[p][q]
                else:
                    for p in range(M):
                        for q in range(M - (j - N)):
                            lock[i - M + p][j - M + q] += key[p][q]
            else:
                if (j < M):
                    # 여기서 loop를 2중으로 돌아야함. 2d array니까.
                    for p in range(M - (i - N)):
                        for q in range(j):
                            lock[i - M + p][q] += key[p][M -j + q]
                elif (M <= j <= N):
                    for p in range(M - (i - N)):
                        for q in range(M):
                            lock[i - M + p][j - M + q] += key[p][q]
                else:
                    for p in range(M - (i - N)):
                        for q in range(M - (j - N)):
                            lock[i - M + p][j - M + q] += key[p][q]
            if len(list(filter(lambda row: list(filter(lambda x:x != 1, row)), lock))) == 0:
                return True
    return False


def solution(key, lock):
    _key = [row[:] for row in key]
    for k in range(4):
        if solve(_key, lock) == True:
            return True
        _key = rotate(_key)
        
    return False


print(solution([[0, 1, 1], 
                [1, 0, 0], 
                [1, 1, 0]], 

                [[1, 1, 1], 
                [1, 1, 0],
                [1, 0, 1]]))

print(solution([[1, 0, 1], 
                [1, 0, 0], 
                [0, 1, 1]], 

                [[1, 1, 1], 
                [1, 1, 0],
                [1, 0, 1]]))

print(solution([[0, 1], 
                [0, 1]], 

                [[1, 1, 1], 
                [0, 1, 1],
                [1, 0, 1]]))
