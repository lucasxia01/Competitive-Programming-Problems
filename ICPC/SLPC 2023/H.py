n = int(input())
arr = list(map(int, input().split()))
num = 1
for i in range(300):
    num *= 2

eps = 100000000

sum = 0
for x in arr:
    sum += num//x
    
if sum >= num-eps:
    print("No")
else:
    print("Yes")