from functools import reduce

def solution():
    N, M = map(int, input().strip().split(' '))
    x, y = map(int, input().strip().split(' '))

    if (x > N or y > M or (x == 0 and y == 0)):
        print("fail")
        return

    def fac(n):
        return reduce(lambda acc, x: acc*x, [1] + range(1, n+1))
    print(x + y)
    print(int(fac(x+y) / (fac(x)*fac(y))))

solution()