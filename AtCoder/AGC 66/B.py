
start = 10**99
for i in range(50):
    print(start//(1<<(i+50)),end="")
    for j in range(50):
        print(0, end="")
        