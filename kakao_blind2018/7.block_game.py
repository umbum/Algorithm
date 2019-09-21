from pprint import pprint
"""
위에서부터 떨어트려서 직사각형을 만들 수 있는가? -> 삭제. 하고 카운트 증가.
"""
black = 1000
transpose = lambda data: [[row[i] for row in data] for i in range(len(data[0]))]

def fillBlack(board):
    transposed = transpose(board)
    for i, row in enumerate(transposed):
        for j, x in enumerate(row):
            if (x == 0):
                transposed[i][j] = black
            else:
                break
    return transpose(transposed)


def isDeletable(B, board, N):
    # 3x2 검사
    for i in range(N - 1):
        for j in range(N - 2):
            arr = []
            arr += B[i][j], B[i][j+1], B[i][j+2], \
                B[i+1][j], B[i+1][j+1], B[i+1][j+2]
            if arr.count(black) == 2:
                nonBlack = list(filter(lambda x: x != black, arr))
                if nonBlack[0] != 0 and nonBlack.count(nonBlack[0]) == 4:
                    board[i][j] = 0
                    board[i][j+1] = 0
                    board[i][j+2] = 0
                    board[i+1][j] = 0
                    board[i+1][j+1] = 0
                    board[i+1][j+2] = 0
                    return True
    # 3x2 검사
    for i in range(N - 2):
        for j in range(N - 1):
            arr = []
            arr += B[i][j], B[i][j+1], \
                B[i+1][j], B[i+1][j+1], \
                B[i+2][j], B[i+2][j+1]
            if arr.count(black) == 2:
                nonBlack = list(filter(lambda x: x != black, arr))
                if nonBlack[0] != 0 and nonBlack.count(nonBlack[0]) == 4:
                    board[i][j] = 0
                    board[i][j+1] = 0
                    board[i+1][j] = 0
                    board[i+1][j+1] = 0
                    board[i+2][j] = 0
                    board[i+2][j+1] = 0
                    return True
    return False

def solution(board):
    answer = 0
    N = len(board)
    B = fillBlack(board)
    # pprint(board)
    while isDeletable(B, board, N):
        # pprint(board)
        answer += 1
        B = fillBlack(board)
    return answer

assert solution([[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,0,0,0,0],[0,0,0,0,0,0,4,0,0,0],[0,0,0,0,0,4,4,0,0,0],[0,0,0,0,3,0,4,0,0,0],[0,0,0,2,3,0,0,0,5,5],[1,2,2,2,3,3,0,0,0,5],[1,1,1,0,0,0,0,0,0,5]]) == 2
assert solution([[0,3,0,2], [3,3,0,2], [1,3,2,2], [1,1,1,0]]) == 1
assert solution([[0,0,0,2], [0,0,0,2], [1,0,2,2], [1,1,1,0]]) == 2
assert solution([[0,0,1,0], [0,1,1,1], [0,0,2,0], [0,2,2,2]]) == 2
assert solution([[3,0,1,0], [3,1,1,1], [3,3,2,0], [0,2,2,2]]) == 3
