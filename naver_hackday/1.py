
def solution(A):
    min_rot = -1
    for i in range(1, 7):
        l_min_rot = 0
        for e in A:
            if e == i:
                pass
            elif e + i == 7:
                l_min_rot += 2
            else:
                l_min_rot += 1
        # print(l_min_rot)
        if l_min_rot < min_rot or min_rot == -1:
            min_rot = l_min_rot
    # print("answer : {}".format(min_rot))
    return min_rot


if __name__ == "__main__":
    solution([1, 2, 3])
    solution([1, 1, 6])
    solution([1, 6, 2, 3])
    solution([1, 6, 1, 6, 1, 6, 1, 6, 1, 3])
    solution([1, 2, 3, 4, 5, 6])
    solution([4, 4, 4, 4, 2, 3])
    solution([2, 2, 2, 2])
    solution([1])
