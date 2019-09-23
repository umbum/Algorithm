
N = int(input())
seat = input().strip().replace(' ', '')
splited = seat.split('1')
emptySeats = map(lambda x: len(x), splited)
maxEmpty = max(emptySeats)
if maxEmpty in (emptySeats[-1], emptySeats[0]):
    print(maxEmpty)
else:
    print(int((emptySeat + 1) / 2))
