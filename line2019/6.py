
N, align = map(str, input().strip().split(' '))
N = int(N)
numbers = []
for _ in range(N):
    size, nums = input().strip().split(' ')
    for num in nums:
        numbers.append((int(size), int(num)))

maxWidth = max(numbers, key=lambda x:x[0])[0]
maxHeight = maxWidth * 2 - 1

# size대로 번호 문자열을 만들어주는 함수를 하나 짜고,["....#", "....#" ...] 이런 식으로 반환되게.
# 마지막 정답 문자열을 만들 때는 한줄 씩 for돌면서 붙이면 되겠네.
def makeStrNumber(width, number):
    height = width * 2 - 1
    strNumber = []
    i = 0
    if number not in range(0, 10):
        raise Exception()

    while i < height:
        if number == 0:
            if (i in (0, height-1)):
                strNumber.append("#"*width)
            else:
                strNumber.append("#{}#".format("."*(width-2)))
        elif number == 1:
            strNumber.append("{}#".format("."*(width-1)))
        elif number == 2:
            if (i in (0, height-1, int(height/2))):
                strNumber.append("#"*width)
            elif (i < int(height / 2)):
                strNumber.append("{}#".format("."*(width-1)))
            else:
                strNumber.append("#{}".format("."*(width-1)))
        elif number == 3:
            if (i in (0, height-1, int(height/2))):
                strNumber.append("#"*width)
            else:
                strNumber.append("{}#".format("."*(width-1)))
        elif number == 4:
            if (i < int(height / 2)):
                strNumber.append("#{}#".format("."*(width-2)))
            elif (i == int(height / 2)):
                strNumber.append("#"*width)
            else:
                strNumber.append("{}#".format("."*(width-1)))
        elif number == 5:
            if (i in (0, height-1, int(height/2))):
                strNumber.append("#"*width)
            elif (i < int(height / 2)):
                strNumber.append("#{}".format("."*(width-1)))
            else:
                strNumber.append("{}#".format("."*(width-1)))
        elif number == 6:
            if (i < int(height / 2)):
                strNumber.append("#{}".format("."*(width-1)))
            elif (i in (int(height / 2), height - 1)):
                strNumber.append("#"*width)
            else:
                strNumber.append("#{}#".format("."*(width-2)))
        elif number == 7:
            if (i == 0):
                strNumber.append("#"*width)
            else:
                strNumber.append("{}#".format("."*(width-1)))
        elif number == 8:
            if (i in (0, height-1, int(height/2))):
                strNumber.append("#"*width)
            else:
                strNumber.append("#{}#".format("."*(width-2)))
        elif number == 9:
            if (i in (0, int(height/2))):
                strNumber.append("#"*width)
            elif (i < int(height/2)):
                strNumber.append("#{}#".format("."*(width-2)))
            else:
                strNumber.append("{}#".format("."*(width-1)))
        i += 1

    while i < maxHeight:
        if (align == "TOP"):
            strNumber.append("."*width)
            i += 1
        elif (align == "BOTTOM"):
            strNumber.insert(0, "."*width)
            i += 1
        else:
            strNumber.insert(0, "."*width)
            strNumber.append("."*width)
            i += 2
    return strNumber

strNums = []
for width, num in numbers:
    strNums.append(makeStrNumber(width, num))

i = 0
while i < maxHeight:
    printStr = ""
    for strNum in strNums:
        printStr += strNum[i] + " "
    print(printStr)
    i += 1
