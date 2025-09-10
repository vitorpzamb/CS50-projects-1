num = int(float(input("Change owed: "))*100)

if num < 0:
    print("Usage: num > 0")
    exit()

aux = 0
while num > 0:
    if num >= 25:
        num -= 25
        aux += 1
    elif num < 25 and num >= 10:
        num -= 10
        aux += 1
    elif num < 10 and num >= 5:
        num -= 5
        aux += 1
    elif num < 5 and num >= 1:
        num -= 1
        aux += 1

print(aux)
