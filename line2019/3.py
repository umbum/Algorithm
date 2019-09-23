import itertools

def solution():
    N = int(input())
    apps = []

    for _ in range(N):
        go, back = map(int, input().strip().split(' '))
        apps.append(set(range(go, back)))

    for p in range(N, 1, -1):
        # nCp
        combis = list(itertools.combinations(apps, p))
        for combi in combis:
            isOverlapped = combi[0].intersection(*combi[1:])
            if isOverlapped:
                return p

    return 1

print(solution())