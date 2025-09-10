num = int(input())

if num > 8 or num < 1:
    print("Usage: num E [1, 8]")
    exit()

j = num-1
for i in range(1, num+1):
    print(" "*j, end = "")
    print("#"*i)
    i += 1
    j -= 1

