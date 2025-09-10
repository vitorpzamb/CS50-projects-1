#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct pair{
    int winner; //cada int representa o indice do candidato em cadidates[]
    int loser;
};

#define MAX_VOTERS 100
#define MAX_NAME_LENGTH 100
#define MAX_CANDIDATES 9
int PAIR_COUNT = 0;

//preferences, 2D array (preferences[i][j] is the
//NUMBER of voters who prefer candidate i over j     ->>>> ver como funciona no video 8:11
int preferences[MAX_CANDIDATES][MAX_CANDIDATES];

//criando as estruturas
//array of candidate names
char candidates[MAX_CANDIDATES][MAX_NAME_LENGTH];

//usando a array pairs vamos gerar um grafico chamado locked
//(um bool array bidimensional). toda vez que "desenharmos"
//uma flecha do candidato i para j, locked[i][j] sera mudado
//de false para true (a menos que nesse caso colocar a seta criasse um loop
//nesse caso pulamos e vamos para o proximo par)
bool locked[MAX_CANDIDATES][MAX_CANDIDATES];


//pairs, um vetor de struct pairs em que nele tem apenas
//pares em que nao ha empate
struct pair pairs[100];

bool vote(int rank, char name[], int ranks[]);
void record_preferences(int ranks[], int num);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool has_cycle(int winner, int loser);

int main(int argc, char *argv[]){

    for(int i = 0; i < argc-1; i++){
        strcpy(candidates[i], argv[i+1]);
    }

    int num;
    printf("Number of electors: ");
    scanf("%d", &num);

    for(int i = 0; i < num; i++){
        int ranks[argc-1];
        for(int j = 0; j < argc-1; j++){
            printf("Rank %d: ", j+1); // <<<<<-------  ****SETA****
            char name[50];
            scanf("%s", name);

            if(vote(j, name, ranks) == false){
                printf("Invalid vote\n");
                return 1;
            }
        }

        record_preferences(ranks, argc-1);
        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

bool vote(int rank, char name[], int ranks[]){
    for(int i = 0; i < MAX_CANDIDATES; i++){
        if(strcmp(name, candidates[i]) == 0){
            ranks[rank] = i; //o numero do candidato com o nome de candidates[i] foi colocado na a posicao J (olhar a seta)
            return true;
        }
    }
    return false; //nenhum candidato com o nome "name" foi encontrado em candidates
}

void record_preferences(int ranks[], int num) {
    for (int i = 0; i < num; i++) {
        for (int j = i + 1; j < num; j++) {
            preferences[ranks[i]][ranks[j]]++;  // O candidato ranks[i] é preferido sobre ranks[j]
        }
    }
}

void add_pairs(void){
    for(int i = 0; i < MAX_CANDIDATES; i++){
        for(int j = i+1; j < MAX_CANDIDATES; j++){  //aqui j eh igual a i+1 para nao ter repeticao
            if(preferences[i][j] > preferences[j][i]){
                pairs[PAIR_COUNT].winner = i;
                pairs[PAIR_COUNT].loser = j;
                PAIR_COUNT++;
            } else if(preferences[i][j] < preferences[j][i]){
                pairs[PAIR_COUNT].winner = j;
                pairs[PAIR_COUNT].loser = i;
                PAIR_COUNT++;
            }
        }
    }
}

void sort_pairs(void){
    //abs(preferences[pair[i].winner][pair[i].loser] - preferences[pair[i].loser][pair[i].winner]) aqui temos o valor em si
    for(int i = 0; i < PAIR_COUNT-1; i++){
        int max = i;
        for(int j = i+1; j < PAIR_COUNT; j++){
            if(abs(preferences[pairs[j].winner][pairs[j].loser] - preferences[pairs[j].loser][pairs[j].winner]) > abs(preferences[pairs[max].winner][pairs[max].loser] - preferences[pairs[max].loser][pairs[max].winner])){
                max = j;
            }
        }
        if(max != i){
            struct pair temp = pairs[i];   //depois do programa rodando, ver se criar com o tipo struct pair eh realmente necessario
            pairs[i] = pairs[max];
            pairs[max] = temp;
        }
    }
}


bool has_cycle(int winner, int loser){
    if(locked[loser][winner] == true){    //aqui estamos apenas vendo se o perdedor da funcao (ou seja quem voce quer apontar) ja aponta para o winner
        return true;
    }

    for(int i = 0; i < MAX_CANDIDATES; i++){
        if(locked[loser][i] == true && has_cycle(winner, i) == true){  //aqui estamos usando um for para achar (e conferir) para quem voce quer apontar aponta (se apontar para alguem)
            return true;                                                //se essa pessoa apontar vamos chamar a funcao com a apontada (a pessoa cuja qual eh apontada por quem voce quer apontar)
        }                                                               //e conferir se essa apontada ja nao aponta para voce
    }
    return false;
}

//locked[pairs[i].winner][pairs[i].loser];  -> colocar uma flexa do candidato x para o y

void lock_pairs(void){ //vai passar por todo o array pairs e lock them into the graph
    for(int i = 0; i < PAIR_COUNT; i++){
        if(has_cycle(pairs[i].winner, pairs[i].loser) == false){
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
}

void print_winner(void) {
    for (int i = 0; i < MAX_CANDIDATES; i++) {
        bool is_winner = true;

        for (int j = 0; j < MAX_CANDIDATES; j++) {
            if(locked[j][i] == true) {  // Se alguém aponta para i, ele não é o vencedor
                is_winner = false;
                break;  // Não precisa continuar verificando
            }
        }

        if(is_winner == true) {
            printf("%s\n", candidates[i]);  // Exibir o nome do candidato vencedor
            return;  // Como só pode haver um vencedor, podemos sair da função
        }
    }
}

