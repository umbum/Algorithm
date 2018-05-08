#coding: utf-8
### 2^61 -1 이 소수인지 판별하라.

import time

def simple_method(n):
    if n % 2 == 0:
        print("{} is even".format(n))
        return False

    sqrtN = int(n ** 0.5) + 1
    for i in range(3, sqrtN, 2):  # n은 홀수
        if n % i == 0:
            print("{} is divided by {}".format(n, i))
            return False
    print("{} is prime number".format(n))
    return True


def lucas_lehmer(p):
    '''
    2^p - 1 일 때 p을 파라미터로 받는다.
    s_0 = 4, s_i = s_(i-1)^2 -2 일 때
    s_(p-2) % M_p == 0과 M_p가 소수라는 것은 동치다.
    '''

    if simple_method(p) is False:   # M이 소수이려면 반드시 p가 소수여야 한다.
        return False

    s = 4    # s_0 == 4
    M = 2 ** p - 1

    for i in range(p - 2):
        s = (s*s - 2) % M
    if s % M == 0:
        print("{} is prime number".format(M))
        return True
    else:
        return False

def main():
    print(time.ctime())
    print(lucas_lehmer(61))
    print(time.ctime())
    print(simple_method((1<<61) - 1))
    print(time.ctime())

if __name__ == "__main__":
    main()

