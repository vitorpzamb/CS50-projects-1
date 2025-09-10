import csv
import sys


def main():

    with open(sys.argv[2], "r") as file:
        dna_str = file.read()


    with open(sys.argv[1]) as file1:
        leitor = csv.DictReader(file1) # ainda nao eh um dicionario
        str_list = leitor.fieldnames[1:]
        lista_leitor = list(leitor)  # Converte para uma lista de dicionarios (se tentassemos converter para um dicionario daria errado, ja que o comando dict(leitor))
        x = len(lista_leitor)  # temos o numero de "dicionarios" dentro da lista                 (so consegue criar UM unico dicionario (e temos varios))


    listSTR = list()
    for i in str_list:
        listSTR.append(longest_match(dna_str, i))  #aqui temos um for percorrendo str_list, que contem todos os STRs diferentes da tabela
                                                    #e o resultado da função longest_match sera colocado na listSTR

    #Check database for matching profiles
    aux1 = 1
    aux = 0
    for j in range(x):
        posicaoK = 0
        if aux == -1:
            print(lista_leitor[j-1]["name"]) #mostrara o valor que tem dentro do name na lista j do dicionario
            aux1 = 0
            break
        cont = 0
        for k in listSTR:
            if int(k) != int(lista_leitor[j][str_list[posicaoK]]):                             #aqui str_list eh uma lista com todos os nomes dos STRs
                break #break aqui sai do for com a variavel k e aumenta o j
            else:
                cont += 1

            if cont == len(listSTR): 
                aux = -1
                if(j == x-1):
                    print(lista_leitor[j]["name"])
                    aux1 = 0
                break
            posicaoK += 1 # essa variavel mostra qual posição K esta dentro da lista "listSTR" (esse valor será o numero da coluna que vamos comparar)

    if aux1 == 1:
        print("No match.")

    return


def longest_match(sequence, subsequence):
    #Returns length of longest run of subsequence in sequence.

    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    for i in range(sequence_length):

        # consecutive runs
        count = 0

        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break # ai vemos se o count que foi calculado dentro desse while eh maior que o maior atual (longest_run)

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    return longest_run


main()
