
def solution(s):
    sLen = len(s)
    if (sLen == 1):
        return 1
    
    halfLen = int(sLen / 2)

    compList = []
    for n in range(1, halfLen+1): # 묶는 양
        
        isFirstMatch = True
        i = 0
        j = n
        compressedLen = len(s)
        while j < sLen:
            cntStr = s[i:j]
            i += n
            j += n
            if (cntStr == s[i:j]):
                compressedLen -= n
                if isFirstMatch:
                    compressedLen += 1
                    isFirstMatch = False
            else:
                isFirstMatch = True
                
        compList.append(compressedLen)
    print(compList)
    return min(compList)


assert solution("a") == 1
assert solution("ab") == 2
assert solution("abc") == 3
assert solution("abab") == 3
assert solution("abcabc") == 4
assert solution("aaaaa") == 2
assert solution("cccccbbbbbbbddddddd") == 6
assert solution("abcdabcdabcd") == 5
assert solution("abcdabcdxabcd") == 10
assert solution("aabbaccc") == 7
assert solution("ababcdcdababcdcd") == 9
assert solution("abcabcdede") == 8
assert solution("abcabcdedezx") == 10
assert solution("abcabcabcabcdededededede") == 14
assert solution("xababcdcdababcdcd") == 17
assert solution("xxababxx") == 7
assert solution("ababacababac") == 7