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
    sys.exit(1)

N = len(w)
best_v = 0
cost = 0

def go(sw, sv, d):
    global cost, best_v
    cost += 1
    if sv + sum(v[i] for i in range(d, N)) > best_v:
        if d == N:
            best_v = sv
        else:
            if sw + w[d] <= W:
                go(sw + w[d], sv + v[d], d + 1)
            go(sw, sv, d + 1)

go(0, 0, 0)
print("Cost: " + str(cost))
print("Points earned: " + str(cost * 1e-3))
