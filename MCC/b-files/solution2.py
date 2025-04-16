import sys

W = 0
w = []
v = []

input_length = 0
for line in open(sys.argv[1]):
    line = line.strip()
    input_length += len(line) + 1
    if W == 0:
        W = int(line)
        if W <= 0:
            print("Incorrect data: Non-positive weight")
            sys.exit(1)
    else:
        cw, cv = [int(t) for t in line.split()]
        if cw <= 0 or cv <= 0:
            print("Incorrect data: Non-positive capacity or weight")
            sys.exit(1)
        w.append(cw)
        v.append(cv)

if input_length > 100:
    print("Incorrect data: Input length exceeds 100")
    print(str(input_length))
    sys.exit(1)

N = len(w)

def should_swap(l, r):
    if v[l] * w[r] < v[r] * w[l]:
        return True
    if v[l] * w[r] == v[r] * w[l] and w[l] < w[r]:
        return True
    return False

for i in range(1, N):
    while i > 0 and should_swap(i - 1, i):
        w[i], w[i - 1] = w[i - 1], w[i]
        v[i], v[i - 1] = v[i - 1], v[i]
        i -= 1

best_v = 0
cost = 0

def heuristic(sw, sv, d):
    rw = min(W - sw, sum(w[i] for i in range(d, N)))
    rv = best_v + 1 - sv
    return v[d] * rw >= rv * w[d]

def go(sw, sv, d):
    global cost, best_v
    cost += 1
    if d == N:
        if sv > best_v:
            best_v = sv
    elif sv > best_v or heuristic(sw, sv, d):
        if sw + w[d] <= W:
            go(sw + w[d], sv + v[d], d + 1)
        go(sw, sv, d + 1)

go(0, 0, 0)
print("Cost: " + str(cost))
print("Points earned: " + str(cost * 1e-3))
