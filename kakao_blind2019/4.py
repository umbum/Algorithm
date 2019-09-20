

class Trie:
    def __init__(words):
        self.words = words

    def find(query):
        pass

def solution(words, queries):
    trie = Trie(words)


    
    return list(map(lambda query: trie.find(query), queries))

assert solution(["frodo", "front", "frost", "frozen", "frame", "kakao"], ["fro??", "????o", "fr???", "fro???", "pro?"]) == [3, 2, 4, 1, 0]
