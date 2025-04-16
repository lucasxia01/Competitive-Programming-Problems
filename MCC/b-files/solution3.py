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

gw = 0
gv = 0
b = 0
while b < N and gw + w[b] <= W:
    gw += w[b]
    gv += v[b]
    b += 1

if b == N:
    print("Cost: 0")
    print("Points earned: 0.0")
    sys.exit(0)

best_v = gv
cost = 0

for i in range(b + 1, N):
    if gw + w[i] <= W:
        best_v = max(best_v, gv + v[i])

for i in range(0, b):
    if gw + w[b] - w[i] <= W:
        best_v = max(best_v, gv + v[b] - v[i])

prev = [N if i == 0 else i - 1 for i in range(N + 1)]
next = [0 if i == N else i + 1 for i in range(N + 1)]

def remove(i):
    next[prev[i]] = next[i]
    prev[next[i]] = prev[i]

def go(sw, sv, left, right):
    global cost, best_v
    cost += 1
    if sw <= W:
        if sv > best_v:
            best_v = sv
        while right != N:
            if (best_v + 1 - gv - v[right]) * w[b] > (W - gw - w[right]) * v[b]:
                old = right
                right = next[right]
                remove(old)
                continue
            if (sv - best_v - 1) * w[right] < (sw - W) * v[right]:
                return
            go(sw + w[right], sv + v[right], left, next[right])
            right = next[right]
    else:
        while left != N:
            if (best_v + 1 - gv + v[left]) * w[b] > (W - gw + w[left]) * v[b]:
                old = left
                left = prev[left]
                remove(old)
                continue
            if (sv - best_v - 1) * w[left] < (sw - W) * v[left]:
                return
            go(sw - w[left], sv - v[left], prev[left], right)
            left = prev[left]

go(gw, gv, prev[b], b)
print("best_v: " + str(best_v))
print("Cost: " + str(cost))
print("Points earned: " + str(cost * 1e-3))
