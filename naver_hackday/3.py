# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

def solution(T):
    # write your code in Python 3.6
    # 1. 선택하고, 뒤에서 부터 나보다 작은 온도 중 제일 마지막 온도의 위치를 체크.
    # 2. 여기서 iter를 줄이기 위해 작은놈 위치를 가지고 거기까지 쭉 pass
    # 3. 추가한 상태에서 다시 1, 2를 반복. 작은놈 없으면 return.
    
    i = 0
    while (i < len(T)):
        winter_max = max(T[:i+1])
        j = len(T) - 1
        while (i < j):
            if T[j] <= winter_max:
                i = j - 1
                break
            j -= 1

        if i == j:
            # all winter t < all summer t 
            break
        i += 1
    print("winter {}  /  summer {}  /   winter len : {}".format(T[:i+1], T[i+1:], i + 1))
    return i + 1



if __name__ == "__main__":
    import random
    
    T = [random.randrange(-1000000000, 1000000001) for t in range(5)]
    # T = [random.randrange(-10, 11) for t in range(5)]
    solution(T)
    solution([-5, -5, -5, -42, 6, 12])
    solution([5, -2, 3, 8, 6])
    solution([1, -2, 3, 8, 6])
    solution([1, 1, 1, 1, 1, 2])
    solution([2, 2, 2, 2, 2, 1, 3])
