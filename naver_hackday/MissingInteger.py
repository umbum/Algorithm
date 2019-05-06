"""
Write a function:

def solution(A)

that, given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.

For example, given A = [1, 3, 6, 4, 1, 2], the function should return 5.

Given A = [1, 2, 3], the function should return 4.

Given A = [−1, −3], the function should return 1.

Write an efficient algorithm for the following assumptions:

N is an integer within the range [1..100,000];
each element of array A is an integer within the range [−1,000,000..1,000,000].
"""
# you can write to stdout for debugging purposes, e.g.
# print("this is a debug message")

def solution(A):
    A.sort()

    if (A[0] > 1):
        return 1
    
    positive_flag = False
    for i in range(len(A) - 1):
        if (A[i] <= 0):
            continue
        
        if (positive_flag is False):
            positive_flag = True
            if (i != 0 and A[i-1] <= 0 and A[i] > 1):
                return 1

        if (A[i+1] - A[i] > 1):
            return A[i] + 1
    
    
    if (positive_flag is False):
        if (A[-1] <= 0):
            return 1
        else:
            # A[-2] <= 0 and A[-1] > 0   ( 0 is deleted above )
            if (A[-1] == 1):
                return 2
            else:
                return 1
    else:
        return A[-1] + 1
    


"""
[1, 1, 2, 3, 3, 3, 5, 6]
[-3, 0, 2]
[-3, 0, 1]
[-3, 1, 2]
[-3, 1, 3]
[-3, 2, 3]
[-3, 1, 1, 2, 2]
[4, 5, 6]
"""