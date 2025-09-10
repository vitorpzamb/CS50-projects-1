#include <stdio.h>
#include <string.h>

struct candidate{
    char name[50];
    int votes;
};

int vote(char name[], struct candidate vetor[], int len);

void print_winner(struct candidate vetor[], int len);

int main(int argc, char *argv[]){

    struct candidate candidates[argc-1];
    for(int i = 1; i < argc; i++){
        strcpy(candidates[i-1].name, argv[i]); //uma funcao para passar o nome do candidato para cadidatos[]
        candidates[i-1].votes = 0;
    }

    int num;
    printf("Number of votes: ");
    scanf("%d", &num);

    for(int i = 0; i < num; i++){
        printf("Vote: ");
        char name[50];
        scanf("%s", name);
        vote(name, candidates, argc-1);
    }

    print_winner(candidates, argc-1);
}

int vote(char name[], struct candidate vetor[], int len){
    for(int i = 0; i < len; i++){
        if(strcmp(vetor[i].name, name) == 0){
            vetor[i].votes++;
            return 0;
        } else{
            if(i == len-1){
                return 1;
            }
        }
    }
    return 0;
}

void print_winner(struct candidate vetor[], int len){
    int maior = -1;
    for(int i = 0; i < len; i++){
        if(vetor[i].votes > maior){
            maior = vetor[i].votes; //achando o maior valor dentro do vetor
        }
    }

    for(int i = 0; i < len; i++){
        if(vetor[i].votes == maior){
            printf("%s\n", vetor[i].name); //percorrendo o vetor novamente e printando todos
        }                                  //os valores com votos == maior
    }
}
