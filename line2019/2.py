
import itertools


# pool = list(map(str, input().strip().split(' ')))
# k = int(input())
pool = ['1', '0', '2']
k = 5

print(list(map(''.join, itertools.permutations(pool)))) 
print(sorted(list(map(''.join, itertools.permutations(pool))))[k-1])


def permute(pool):
    i = 0
    