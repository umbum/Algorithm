
def solution(drum):
    N = len(drum)

    answer = 0
    for j in range(N):
        starFlag = False
        i = 0

        while i < N:
            if (drum[i][j] == "#"):
                i += 1
            elif (drum[i][j] == "*"):
                if (starFlag == True):
                    break
                else:
                    starFlag = True
                    i += 1
            elif (drum[i][j] == ">"):
                # 구슬이 밖으로 벗어나는 경우는 입력으로 주지 않는다고 했음.
                j += 1
            elif (drum[i][j] == "<"):
                j -= 1
        if i == N:
            answer += 1
    
    return answer

assert solution(["######",">#*###","####*#","#<#>>#",">#*#*<","######"]) == 4