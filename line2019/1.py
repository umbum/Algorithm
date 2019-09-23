from queue import Queue

q = Queue()
a, b = map(int, input().strip().split(' '))
answer = 0

for _ in range(a):
    q.put(int(input()))

consumers = []
for _ in range(b):
    if q.empty():
        break
    consumers.append(q.get())

while q.empty() is False:
    minv = min(consumers)

    consumers = list(map(lambda x: x - minv, consumers))
    idle = consumers.count(0)

    answer += minv * idle

    consumers = list(filter(lambda x: x != 0, consumers))

    for _ in range(idle):
        if q.empty():
            break
        consumers.append(q.get())

answer += max(consumers)
# 남은 consumers의 시간 중 제일 오래 걸리는 것 더해줌.
print(answer)