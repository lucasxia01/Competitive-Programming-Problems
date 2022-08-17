import heapq

n, m, k = map(int, input().split())

d = int(input())

g = [[] for _ in range(d * k * 5 * 5)]

roadToIndex = {}
dInputs = []

for i in range(d):
    r0, c0, r1, c1, t, *ls = input().split()
    r0, c0, r1, c1, t = map(int, (r0, c0, r1, c1, t))

    dInputs.append((r0, c0, r1, c1, t, ls))
    roadToIndex[(r0, c0, r1, c1)] = i

ds = [(0, 1), (1, 0), (0, -1), (-1, 0)]

for i in range(d):
    r0, c0, r1, c1, t, ls = dInputs[i]

    lefts = 0
    straights = 0
    rights = 0

    leftsCount = 0
    straightsCount = 0
    rightsCount = 0

    for l in ls:
        rightsCount += 1 if 'R' in l else 0
        leftsCount += 1 if 'L' in l else 0
        straightsCount += 1 if 'S' in l else 0

    curDx, curDy = r1 - r0, c1 - c0
    curDi = ds.index((curDx, curDy))

    for lane in range(k):
        if 'L' in ls[lane]:
            newDx, newDy = ds[(curDi - 1) % 4]
            newr, newc = r1 + newDx, c1 + newDy

            j = roadToIndex[(r1, c1, newr, newc)]

            for x in range(4):
                for y in range(5):
                    g[i * (k * 25) + (lane * 25) + x * 5 + y].append((j *
                                                                      (k * 25) + (lefts * 25) + (x + 1) * 5 + y, t))

            if lefts == leftsCount - 1:
                for newLane in range(lefts + 1, k):
                    for x in range(4):
                        for y in range(5):
                            g[i * (k * 25) + (lane * 25) + x * 5 + y].append((j *
                                                                              (k * 25) + (newLane * 25) + (x + 1) * 5 + y, t))

            lefts += 1

        if 'R' in ls[lane]:

            newDx, newDy = ds[(curDi + 1) % 4]
            newr, newc = r1 + newDx, c1 + newDy

            j = roadToIndex[(r1, c1, newr, newc)]

            for x in range(5):
                for y in range(5):
                    g[i * (k * 25) + (lane * 25) + x * 5 + y].append((j *
                                                                      (k * 25) + ((k - rightsCount + rights) * 25) + x * 5 + y, t))

            if rights == 0:
                for newLane in range(k - rightsCount):
                    for x in range(4):
                        for y in range(5):
                            g[i * (k * 25) + (lane * 25) + x * 5 + y].append((j *
                                                                              (k * 25) + (newLane * 25) + x * 5 + y, t))

            rights += 1

        if 'S' in ls[lane]:
            newr, newc = r1 + curDx, c1 + curDy

            j = roadToIndex[(r1, c1, newr, newc)]

            for x in range(5):
                for y in range(5):
                    g[i * (k * 25) + (lane * 25) + x * 5 + y].append((j *
                                                                      (k * 25) + (straights * 25) + x * 5 + y, t))

            if straights == straightsCount - 1:
                for newLane in range(straights + 1, k):
                    for x in range(4):
                        for y in range(5):
                            g[i * (k * 25) + (lane * 25) + x * 5 + y].append((j *
                                                                              (k * 25) + (newLane * 25) + x * 5 + y, t))

            straights += 1

for i in range(d):
    for lane in range(k - 1):
        for x in range(5):
            for y in range(4):
                g[i * (k * 25) + lane * 25 + x * 5 +
                  y].append((i * (k * 25) + (lane + 1) * 25 + x * 5 + y + 1, 0))

for i in range(d):
    for lane in range(1, k):
        for x in range(5):
            for y in range(4):
                g[i * (k * 25) + lane * 25 + x * 5 +
                  y].append((i * (k * 25) + (lane - 1) * 25 + x * 5 + y + 1, 0))


p = int(input())

for _ in range(p):
    rs0, cs0, rs1, cs1, rd0, cd0, rd1, cd1, x, y = map(int, input().split())

    sourceI = roadToIndex[(rs0, cs0, rs1, cs1)]
    destI = roadToIndex[(rd0, cd0, rd1, cd1)]

    source = sourceI * (k * 25) + (k - 1) * 25
    destinations = []
    for a in range(x + 1):
        for b in range(y + 1):
            destinations.append((destI * (k * 25) + (k - 1) * 25 + a * 5 + b))

    addition = (dInputs[destI][4] - dInputs[sourceI][4]) // 2

    h = [(0, source)]
    seen = set()
    found = False

    while len(h) != 0:
        d, u = heapq.heappop(h)

        if u in seen:
            continue

        i = u // (k * 25)
        road = dInputs[i][:4]

        lane = (u % (k * 25)) // 25
        lefts = (u % 25) // 5
        changes = u % 5

        if lefts > x:
            continue
        if changes > y:
            continue

        if u in destinations:
            addition += d
            found = True
            break

        print(*road, lane, lefts, changes)

        # print('edges:')
        # for v, _ in g[u]:
        #     i = v // (k * 25)
        #     road = dInputs[i][:4]
        #     lane = (v % (k * 25)) // 25
        #     lefts = (v % 25) // 5
        #     changes = v % 5

        #     print(*road, lane, lefts, changes)

        # print('done')

        seen.add(u)

        for v, w in g[u]:
            if v in seen:
                continue
            heapq.heappush(h, (d + w, v))

    if not found:
        print(-1)
    else:
        print(addition)
