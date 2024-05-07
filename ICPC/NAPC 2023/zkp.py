p = int(input())
g = int(input())
y = int(input())
C = int(input())
q = int(input())

h = pow(g, C, p)
if (pow(g, q, p) * pow(y, h, p))%p == C%p:
    print("VALID")
else:
    print("INVALID")

# team127
# wound-shadow-pronto