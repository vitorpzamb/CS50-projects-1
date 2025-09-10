def main():
    num = int(input("Card number: "))

    strN = str(num)
    if len(strN) != 13 and len(strN) != 15 and len(strN) != 16:
        print("Invalid")
        exit()

    if len(strN) == 16:
        x = 0
    elif len(strN) == 15 or len(strN) == 13:
        x = 1

    valid = credito(x, len(strN), strN)

    if(valid == 1):
        print("Invalid")
    else:
        if(int(strN[0]) == 4):
            print("Visa")
        elif(int(strN[0]) == 3 and (int(strN[1]) == 4 or int(strN[1]) == 7)):
            print("American Express")
        elif(int(strN[0]) == 5 and (int(strN[1]) == 1 or int(strN[1]) == 2 or int(strN[1]) == 3 or int(strN[1]) == 4 or int(strN[1]) == 5)):
            print("Mastercard")

def credito(a, b, strN):
    aux = 0
    for i in range(a, b, 2):
        if int(strN[i])*2 > 9:
            strN1 = str(int(strN[i])*2)
            aux += int(strN1[0]) + int(strN1[1])
        else:
            aux += int(strN[i])*2

    for j in range(abs(a-1), b, 2):
        aux += int(strN[j])

    if aux % 10 == 0:
        return 0
    else:
        return 1


main()
