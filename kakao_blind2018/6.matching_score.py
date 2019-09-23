import re


def solution(word, pages):
    pageDict = {}
    pKey  = re.compile(r"<meta.+?content=\"https://(.+?)\"")
    pWord = re.compile(r"[^a-zA-Z]{}(?=[^a-zA-Z])".format(word), re.I)
    pLink = re.compile(r"<a +href=\"https://(.+?)\"")

    for i, page in enumerate(pages):
        key = pKey.search(page).group(1)
        if key is None:
            raise Exception()
        pageDict[key] = {
            "idx" : i,
            "basicScore" : len(pWord.findall(page)),
            "links" : pLink.findall(page),
            "linkScore" : 0,
            "matchScore" : 0
        }
    
    for key in pageDict.keys():
        links = pageDict[key]["links"]
        for link in links:
            if link in pageDict.keys():
                pageDict[link]["linkScore"] += pageDict[key]["basicScore"] / len(links)

    for page in pageDict.values():
        page["matchScore"] = page["basicScore"] + page["linkScore"]

    maxPage = None
    for page in pageDict.values():
        if maxPage is None or page["matchScore"] > maxPage["matchScore"]:
            maxPage = page
        elif page["matchScore"] == maxPage["matchScore"]:
            if (page["idx"] < maxPage["idx"]):
                maxPage = page

    return maxPage["idx"]


print(solution("blind", ["<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n <meta charset=\"utf-8\">\n <meta property=\"og:url\" content=\"https://a.com\"/>\n</head> \n<body>\nBlind Lorem Blind ipsum dolor Blind test sit amet BlindBlindBlind, consectetur adipiscing elit. \n<a href=\"https://b.com\"> Link to b </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n <meta charset=\"utf-8\">\n <meta property=\"og:url\" content=\"https://b.com\"/>\n</head> \n<body>\nSuspendisse potenti. Vivamus venenatis tellus non turpis bibendum, \n<a href=\"https://a.com\"> Link to a </a>\nblind sed congue urna varius. Suspendisse feugiat nisl ligula, quis malesuada felis hendrerit ut.\n<a href=\"https://c.com\"> Link to c </a>\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n <meta charset=\"utf-8\">\n <meta property=\"og:url\" content=\"https://c.com\"/>\n</head> \n<body>\nUt condimentum urna at felis sodales rutrum. Sed dapibus cursus diam, non interdum nulla tempor nec. Phasellus rutrum enim at orci consectetu blind\n<a href=\"https://a.com\"> Link to a </a>\n</body>\n</html>"]))
print(solution("Muzi", ["<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n <meta charset=\"utf-8\">\n <meta property=\"og:url\" content=\"https://careers.kakao.com/interview/list\"/>\n</head> \n<body>\n<a href=\"https://programmers.co.kr/learn/courses/4673\"></a>#!MuziMuzi!)jayg07con&&\n\n</body>\n</html>", "<html lang=\"ko\" xml:lang=\"ko\" xmlns=\"http://www.w3.org/1999/xhtml\">\n<head>\n <meta charset=\"utf-8\">\n <meta property=\"og:url\" content=\"https://www.kakaocorp.com\"/>\n</head> \n<body>\ncon%\tmuzI92apeach&2<a href=\"https://hashcode.co.kr/tos\"></a>\n\n\t^\n</body>\n</html>"]))