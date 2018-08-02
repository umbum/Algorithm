# n-dimension is supported.
import math
from random import seed, randint

def k_means(data):
    _sum = get_sum_list(data)
    min_idx = _sum.index(min(_sum))
    max_idx = _sum.index(max(_sum))

    g1_centroid = data[min_idx]
    g2_centroid = data[max_idx]

    last_g1_centroid = g1_centroid
    last_g2_centroid = g2_centroid
    print("initial minimum centroid : ", g1_centroid)
    print("initial maximum centroid : ", g2_centroid)
    while True:
        g1 = []
        g2 = []
        for point in data:
            if cal_d(point, g1_centroid) <= cal_d(point, g2_centroid):
                g1.append(point)
            else:
                g2.append(point)
        g1_centroid = get_centroid(g1)
        g2_centroid = get_centroid(g2)
        if (last_g1_centroid == g1_centroid) and (last_g2_centroid == g2_centroid):
            break
        last_g1_centroid = g1_centroid
        last_g2_centroid = g2_centroid
        print("[group1]       : ", g1)
        print("[group2]       : ", g2)
        print("[new centroid] : ", g1_centroid)
        print("[new centroid] : ", g2_centroid)
        input()
    return g1, g2

def cal_d(a, b):
    _sum = 0
    for i in range(len(a)):
        _sum += (a[i] - b[i])**2
    return math.sqrt(_sum)
    
def get_sum_list(point_list):
    # input  : [(1, 2), (3, 4)]
    # output : [3, 7]
    return list(map(lambda x: sum(x), point_list))

def get_centroid(group):
    # input             : [(1, 2), (3, 4)]
    # transposed        : [(1, 3), (2, 4)]
    # axis_sum_list     : [4, 6]
    # output            : [2, 3]
    transposed = list(zip(*group))
    axis_sum_list = get_sum_list(transposed)
    return list(map(lambda x: x/len(group), axis_sum_list))

if __name__ == "__main__":
    test_basic = [(0, 2),
                  (0, 1),
                  (2, 0),
                  (1, 0)]
    seed()
    test = []
    for i in range(15):
        test.append((randint(160, 180), randint(50, 80), randint(230, 285)))

    g1, g2 = k_means(test)
    print("[*] cluster1   : ", g1)
    print("[*] cluster2   : ", g2)
