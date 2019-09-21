import itertools

candidateCombis = []

def isInCandidate(combi):
    # 예를 들어서... (ID, NAME, MAJOR)이게 들어오면, candidateCombi 여기에는 (ID, NAME)가 있을거라고.
    # 그러면, candidateCombi의 모든 원소들이, _combi에 들어가는지를 확인해봐야하는거네.
    for candidate in candidateCombis:
        if len(list(filter(lambda col: col in combi, candidate))) == len(candidate):
            # candidate에 있다.
            return True
    return False

def solution(relation):
    answer = 0
    # 돌아야 하는 애들을 컨테이너에서 하나씩 꺼내서 set으로 unique check하는게 좋겠는데?
    colLen = len(relation[0])
    
    for i in range(1, colLen+1):
        for combi in itertools.combinations(range(colLen), i):
            if isInCandidate(combi) == True:
                continue

            uniqueRows = set()
        
            for row in relation:
                # 여기서 set으로 묶어서 add 해줘야 하는데?
                combiEntitys = []
                for col in combi:
                    combiEntitys.append(row[col])
                uniqueRows.add(tuple(combiEntitys))
            
            if (len(relation) == len(uniqueRows)):
                # 해당 조합(combi)으로 식별 가능.
                candidateCombis.append(combi)

    return len(candidateCombis)



def getCombinationSets(relation):
    """
    조합을 만들 때, bit를 이용해서 만들 수 있다.
    A(1), B(10), BA(11), C(100), CA(101), ... 이런 식으로 
    """
    answer_list = list()
    for i in range(1, 1 << len(relation[0])):    # 조합을 의미. 총 조합의 수 만큼 돌아야 하니 nC1 + nC2 + ... nCn = (2^n)-1 만큼 돈다.
        tmp_set = set()
        for j in range(len(relation)):           # 한 row씩 꺼낸다.
            tmp = ''
            for k in range(len(relation[0])):    # 조합에 해당하는 col들을 선택하는 역할.
                if i & (1 << k):
                    tmp += str(relation[j][k])
            tmp_set.add(tmp)
        yield tmp_set, i

def solution2(relation):
    answer_list = list()
    combinationSets = getCombinationSets(relation)
    for tmp_set, i in combinationSets:
        if len(tmp_set) == len(relation):
            not_duplicate = True
            for num in answer_list:
                if (num & i) == num:
                    not_duplicate = False
                    break
            if not_duplicate:
                answer_list.append(i)
    return len(answer_list)

r = solution([["100","ryan","music","2"],["200","apeach","math","2"],["300","tube","computer","3"],["400","con","computer","4"],["500","muzi","music","3"],["600","apeach","music","2"]])
print(r)