text = input("Text: ")

letters = 0
words = 1   #number of spaces +1
sentences = 0
for i in text:
    if (65 <= ord(i) <= 90) or (97 <= ord(i) <= 122): #ord converte i para ascii ->>> i recebe o valor de cada caractere antes de ser convertido para ascii
        letters += 1                                                #ex: i = "a" ou i = "J"
    elif ord(i) == 32:
        words += 1
    elif ord(i) in [33, 46, 63]:
        sentences += 1

l = (letters/words)*100 #numero medio de letras a cada 100 palavras
s = (sentences/words)*100 #nuemro medio de sentencas a cada 100 palavras

index = round(0.0588 * l - 0.296 * s - 15.8)
index1 = 0.0588 * l - 0.296 * s - 15.8

if index > 16:
    print("Grade 16+")
elif index < 1:
    print("Before Grade 1")
else:
    print(f"Grade: {index}, {index1}")
