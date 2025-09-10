#include <stdio.h>
#include <string.h>
#include <stdbool.h>

struct candidate{
    char name[50];
    int votes;
    bool eliminated;
};

#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];
struct candidate candidates[MAX_CANDIDATES];

bool vote(int voter, int rank, char name[]); //aqui a funcao vai procurar por um candidato especifico
                                            //se achado preferences eh atualizadado, se nao retorna false

void tabulate(void); //aqui fazemos a contagem dos votos
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, char *argv[]){

    int num;
    printf("Number of electors: ");
    scanf("%d", &num);

    //aqui estamos apenas preenchendo o candidates[]
    for(int i = 0; i < argc-1; i++){
        strcpy(candidates[i].name, argv[i+1]); //uma funcao para passar o nome do candidato para cadidates[]
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    for(int i = 0; i < num; i++){
        for(int j = 0; j < argc-1; j++){
            printf("Rank %d: ", j+1);
            char name[50];
            scanf("%s", name);
            if(!vote(i, j, name)){
                printf("Invalid vote\n");
                return 1;
            }
        }
    }

    while(true){
        tabulate();

        bool num1 = print_winner();
        if(num1 == true){
            break;
        }

        int min = find_min();
        bool tie = is_tie(min);

        if(tie == true){
            for(int i = 0; i < argc-1; i++){
                if(candidates[i].eliminated == false){
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        eliminate(min);

        for(int i = 0; i < argc-1; i++){
            candidates[i].votes = 0;
        }
    }
    return 0;
}

bool vote(int voter, int rank, char name[]){
    for(int i = 0; i < MAX_CANDIDATES; i++){
        if(strcmp(name, candidates[i].name) == 0){
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

void tabulate(void){
    int i = 0;
    while(true){
        for(int j = 0; j < MAX_CANDIDATES; j++){
            if(candidates[preferences[i][j]].eliminated == false){
                candidates[preferences[i][j]].votes++;
                i++;
                j = 0;
                if(i == MAX_VOTERS-1){
                    break;
                }
            }
        }
        break;
    }
}

bool print_winner(void){
    int votes = 0;
    for(int i = 0; i < MAX_CANDIDATES; i++){
        votes += candidates[i].votes; //soma de todos os votos
    }

    int aux = votes/2;

    for(int i = 0; i < MAX_CANDIDATES; i++){
        if(candidates[i].votes > aux && candidates[i].eliminated == false){
            printf("%s\n", candidates[i].name); //printa o nome do candidato que tiver mais da
            return true;                              //metade dos votosm(e retorna 0)
        }
    }
    return false;
}

int find_min(void){
    int menor = 1000;
    for(int i = 0; i < MAX_CANDIDATES; i++){
        if(candidates[i].votes < menor && candidates[i].eliminated == false){
            menor = candidates[i].votes;
        }
    }
    return menor;
}

bool is_tie(int min){
    for(int i = 0; i < MAX_CANDIDATES; i++){
        if(candidates[i].eliminated == false && candidates[i].votes != min){
            return false;
        }
    }
    return true;
}

void eliminate(int min){
    for(int i = 0; i < MAX_CANDIDATES; i++){
        if(candidates[i].votes == min){
            candidates[i].eliminated = true;
        }
    }
}
