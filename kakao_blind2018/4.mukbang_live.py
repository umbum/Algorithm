

def slowSolution(food_times, k):
    
    eatCount = k

    remainFoods = list(enumerate(food_times))

    while True:
        n = len(remainFoods)
        if (n == 0):
            return -1
        
        if (eatCount < n):
            return remainFoods[eatCount][0] + 1
        
        eatCount = eatCount - n

        remainFoods = list(filter(lambda pair: pair[1] > 0, 
                            map(lambda pair: (pair[0], pair[1] - 1), 
                            remainFoods)))
        


def solution(food_times, k):
    
    eatCount = k

    remainFoods = list(enumerate(food_times))
    

    while True:
        n = len(remainFoods)    
        if (n == 0):
            return -1
        
        eatLoop = int(eatCount / n)
        if (eatLoop == 0):
            return remainFoods[eatCount][0] + 1

        eatCount = eatCount - (n*eatLoop) 
        newRemainFoods = []

        for pair in remainFoods:
            foodTime = pair[1] - eatLoop
            if (foodTime <= 0):
                eatCount += -foodTime
            else:
                newRemainFoods.append((pair[0], foodTime))
        remainFoods = newRemainFoods


# print(solution([3, 1, 2], 5))
print(solution([1, 5, 2, 3, 2], 10))
print(slowSolution([1, 5, 2, 3, 2], 10))
print(solution([3, 5, 2, 3, 2], 2))