from queue import PriorityQueue


def solution_submit(data):
    q = PriorityQueue()
    t = 0
    i = 0
    remainWork = 0
    answer = []

    while i < len(data) or q.empty() is False:
        if i < len(data) and data[i][1] <= t:
            if remainWork == 0:
                answer.append(data[i][0])
                remainWork = data[i][2]
            else:
                q.put((data[i][2], data[i]))
            i += 1

        if remainWork > 0:
            remainWork -= 1
        else:
            if q.empty() is False:
                page = q.get()[1]
                answer.append(page[0])
                remainWork = page[2]
        
        t += 1

    return answer


def solution(data):
    q = PriorityQueue()
    t = 0
    answer = []
    i = 0
    while i < len(data):
        d = data[i]
        if d[1] <= t:
            q.put((d[2], d))
            i += 1
            continue
        
        if q.empty() is True:
            answer.append(d[0])
            t = d[1] + d[2]
            i += 1
        else:
            d = q.get()[1]
            answer.append(d[0])
            t += d[2]
    
    while q.empty() is False:
        d = q.get()[1]
        answer.append(d[0])
        
    return answer



assert solution([[1, 0, 5],[2, 2, 2],[3, 3, 1],[4, 4, 1],[5, 10, 2]]) == [1,3,4,2,5]
assert solution([[1, 0, 3], [2, 1, 3], [3, 3, 2], [4, 9, 1], [5, 10, 2]]) == [1,3,2,4,5]
assert solution([[1, 2, 10], [2, 5, 8], [3, 6, 9], [4, 20, 6], [5, 25, 5]]) == [1,2,4,5,3]
print(solution([[1, 2, 6], [2, 3, 6], [3, 5, 5], [4, 6, 16], [5, 20, 6], [6, 21, 5]]))

import random
_testCase = []
for i in range(1000):
    t = random.randrange(0, 100000000)
    pageAmount = random.randrange(1, 100000)
    _testCase.append([t, pageAmount])
_testCase.sort(key=lambda x:x[0])
testCase = [[i, t[0], t[1]] for i, t in enumerate(_testCase)]
solution(testCase)