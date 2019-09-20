


def quickSort(A, left, right):
    if (left < right):
        split = partition2(A, left, right)
        quickSort(A, left, split - 1)
        quickSort(A, split + 1, right)

def partition(A, left, right):
    p = left
    i = left + 1
    j = right
    while (True):
        while (i < right and A[i] < A[p]):
            i += 1
        while (j > left + 1 and A[j] > A[p]):
            j -= 1

        if (i < j):
            swap(A, i ,j)
        else:
            if (A[p] > A[j]):
                swap(A, p, j)
                
            return j

def partition2(A, left, right):
    p = right
    i = left
    j = left
    while (j < right):
        if (A[j] < A[p]):
            swap(A, i, j)
            i += 1
        j += 1
    swap(A, i, p)
    return i
            


def swap(A, i, j):
    temp = A[i]
    A[i] = A[j]
    A[j] = temp


if __name__ == "__main__":
    a = [4, 6, 3, 2, 1]
    quickSort(a, 0, len(a) - 1)
    print(a)
    a = [2, 1]
    quickSort(a, 0, len(a) - 1)
    print(a)
    a = [1, 2]
    quickSort(a, 0, len(a) - 1)
    print(a)
    