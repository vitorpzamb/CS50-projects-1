num = int(input())

if num < 1 or num > 8:
    print("Usage: 1 <= num <= 8")
    exit()

j = num-1
for i in range (1, num+1): #i vai de 1 ate num inclusivo
    print(" "*j, end = "")
    print("#"*i, end = "")
    print("  ", end = "")
    print("#"*i)
    j -= 1
