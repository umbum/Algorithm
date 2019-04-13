"""
Problem
You have just entered the world's easiest maze. You start in the northwest cell of an N by N grid of unit cells, and you must reach the southeast cell. You have only two types of moves available: a unit move to the east, and a unit move to the south. You can move into any cell, but you may not make a move that would cause you to leave the grid.

You are excited to be the first in the world to solve the maze, but then you see footprints. Your rival, Labyrinth Lydia, has already solved the maze before you, using the same rules described above!

As an original thinker, you do not want to reuse any of Lydia's moves. Specifically, if her path includes a unit move from some cell A to some adjacent cell B, your path cannot also include a move from A to B. (However, in that case, it is OK for your path to visit A or visit B, as long as you do not go from A to B.) Please find such a path.

In the following picture, Lydia's path is indicated in blue, and one possible valid path for you is indicated in orange:

Input
The first line of the input gives the number of test cases, T. T test cases follow; each case consists of two lines. The first line contains one integer N, giving the dimensions of the maze, as described above. The second line contains a string P of 2N - 2 characters, each of which is either uppercase E (for east) or uppercase S (for south), representing Lydia's valid path through the maze.

Output
For each test case, output one line containing Case #x: y, where x is the test case number (starting from 1) and y is a string of 2N - 2 characters each of which is either uppercase E (for east) or uppercase S (for south), representing your valid path through the maze that does not conflict with Lydia's path, as described above. It is guaranteed that at least one answer exists.

Limits
1 ≤ T ≤ 100.
Time limit: 15 seconds per test set.
Memory limit: 1GB.
P contains exactly N - 1 E characters and exactly N - 1 S characters.

Test set 1 (Visible)
2 ≤ N ≤ 10.

Test set 2 (Visible)
2 ≤ N ≤ 1000.

Test set 3 (Hidden)
For at most 10 cases, 2 ≤ N ≤ 50000.
For all other cases, 2 ≤ N ≤ 10000.

Sample

Input 
 	
Output 
 
2
2
SE
5
EESSSESE

  
Case #1: ES
Case #2: SEEESSES

  
In Sample Case #1, the maze is so small that there is only one valid solution left for us.

Sample Case #2 corresponds to the picture above. Notice that it is acceptable for the paths to cross.
"""


# the num of cases : (2N-2)!*2! / (N-1)!*(N-1)!
# 길이 겹치는지를 어떻게 판단할지가 핵심.
"""
현재 지점의 위치 == 지금까지의 E와 S의 합.
지금까지의 E와 S의 합이 같을 때, 같은 방향으로 움직이면 길이 겹치는 것. 이 것만 주의하면 될듯?
무조건 반대로 하게 하면??? 이러면 안겹칠 것 같은데
"""

import sys

# 0 < T <= 100
num_of_test_case = int(sys.stdin.readline())
test_cases = []
for i in range(num_of_test_case):
    N = int(sys.stdin.readline())
    P = input()
    test_cases.append((N, P))

answers = []
def solve(N, P):
    # 2, SE
    my_path = ""
    for i in range(len(P)):
        if P[i] == "S":
            my_path += "E"
        else:
            my_path += "S"
    return my_path


def generateTest(N = 1000):
    import random
    _test_case = []
    for i in range(N):
        _test_case.append("E")
        _test_case.append("S")
    random.shuffle(_test_case)
    return ''.join(_test_case)
    

f = open("test50000.txt", 'w')
f.write(generateTest(50000))
f.close

# Hidden test case 3  10개는 N <= 50000 나머지는 N <= 10000
# test_cases.append((0, generateTest(50000)))
    

for i, T in enumerate(test_cases):
    N, P = T
    print("Case #{}: {}".format(i+1, solve(N, P)))