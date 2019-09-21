import re


def solution(emails):
    emailPattern = re.compile(r"^[a-z\.]+@[a-z]+\.((com)|(net)|(org))$")
    answer = 0
    for email in emails:
        if emailPattern.match(email):
            print(email)
            answer += 1
    return answer

print(solution(["d@co@m.com", "a@abc.com", "b@def.com", "c@ghi.net"]))
print(solution(["abc.def@x.com", "abc", "abc@defx", "abc@defx.org"]	))
print(solution(["abc.def@x.com1"]))