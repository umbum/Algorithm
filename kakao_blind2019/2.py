"""
1. 입력이 빈 문자열인 경우, 빈 문자열을 반환합니다. 
2. 문자열 w를 두 "균형잡힌 괄호 문자열" u, v로 분리합니다. 단, u는 "균형잡힌 괄호 문자열"로 더 이상 분리할 수 없어야 하며, v는 빈 문자열이 될 수 있습니다. 
3. 문자열 u가 "올바른 괄호 문자열" 이라면 문자열 v에 대해 1단계부터 다시 수행합니다. 
  3-1. 수행한 결과 문자열을 u에 이어 붙인 후 반환합니다. 
4. 문자열 u가 "올바른 괄호 문자열"이 아니라면 아래 과정을 수행합니다. 
  4-1. 빈 문자열에 첫 번째 문자로 '('를 붙입니다. 
  4-2. 문자열 v에 대해 1단계부터 재귀적으로 수행한 결과 문자열을 이어 붙입니다. 
  4-3. ')'를 다시 붙입니다. 
  4-4. u의 첫 번째와 마지막 문자를 제거하고, 나머지 문자열의 괄호 방향을 뒤집어서 뒤에 붙입니다. 
  4-5. 생성된 문자열을 반환합니다.
  
3번. 왼쪽에서부터 첫번째로 만난 균형잡힌 괄호 문자열이 u, 나머지는 v (v is nullable)
"""

def isCollect(u):
    openLen = 0
    for b in u:
        if b == "(":
            openLen += 1
        else:
            openLen -= 1
        
        if (openLen < 0):
            return False
    
    assert openLen == 0
    return True


def solution(p):
    if (p == ""):
        return ""
    
    # 균형잡힌 괄호 문자열 찾기
    homoLen = 1
    heteLen = 0
    i = 1
    while True:
        if p[i] == p[0]:
            homoLen += 1
        else:
            heteLen += 1
        i += 1
        if (homoLen == heteLen):
            break
        
    u = p[:i]
    v = p[i:]
    
    if (isCollect(u)):
        return u + solution(v)
    else:
        return "(" + solution(v) + ")" + u[1:-1].replace("(", "-").replace(")", "(").replace("-", ")")
        

print(solution("(()())()"))
print(solution("()()"))
print(solution("()))((()"))