// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 10000;

unsigned int word_count = 0; // Variável global para armazenar a contagem de palavras

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char lower_word[LENGTH + 1];
    int i = 0;

    // Converte a palavra para minúsculas
    while (word[i] != '\0' && i < LENGTH)
    {
        lower_word[i] = tolower(word[i]);
        i++;
    }
    lower_word[i] = '\0'; // Finaliza a string corretamente     ///  ESSA EH A PRINCIPAL LINHA DE TODO O CODIGO ->>>>>> O CODIGO FUNCIONA SEM CONVERTER AS PALAVRAS
                                                                                            //PARA MINUSCULAS, MAS FALTAVA COLOCAR O '\0' NO FINAL (SEM ESSE OPERADOR)
    int num = hash(lower_word); // num recebe o indice da palavra que queremos conferir                 //TODAS AS PALAVAS VAO SER CONSIDERADAS ERRADAS

    node *aux = table[num]; // aux recebe o primeiro no da hash no indice que a palavra está

    while(aux != NULL){
        if(strcmp(aux->word, lower_word) == 0){
            return true; // aqui conferimos se a word esta na hash, ja que todas as palavras do dicionario foram colocadas nela
        }
        aux = aux->next; //vamos para o proximo no
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)   //retorna um numero baseado nas 3 primeiras letras da palavra
{
    int num = 0;
    for(int i = 0; i < 3 && word[i] != '\0'; i++){
        num += (int)round(pow(31, abs(i-2))) * (int)word[i];
    }

    return num % N;
}

// Loads dictionary into memory, returning true if successful, else false ->>> responsavel por colocar todas as palavras do dicionario na hash
bool load(const char *dictionary)
{
    FILE *f = fopen(dictionary, "r");
    if(f == NULL){
        printf("Could not open file\n");
        return false;
    }

    char buffer[100];

    while(fgets(buffer, sizeof(buffer), f) != NULL){

        buffer[strcspn(buffer, "\n")] = '\0'; // Remove o '\n'

        node *word = malloc(sizeof(node));
        if(word == NULL){
            fclose(f);
            return false;
        }
        strcpy(word->word, buffer);

        int num = hash(buffer);

        word->next = table[num];  // aqui word->next vai apontar para onde table[num] estava apontando, o "chao" (NULL)
        table[num] = word;   // agora table[num] aponta para nossa word atual

        word_count++;
    }

    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false ///// liberar toda a memoria que foi alocada para a hash
bool unload(void)
{
    int num = 0;

    while(num < N){
        node *aux = table[num];
        node *aux1 = NULL;
        while(aux != NULL){
            aux1 = aux;
            aux = aux->next;
            free(aux1);
        }
        table[num] = NULL;
        num++;
    }

    return true;
}
