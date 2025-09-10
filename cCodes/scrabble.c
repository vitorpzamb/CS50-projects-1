#import <stdio.h>

int score(char word[], int list[]);

int main(void){

    //65 - 90
    //97 - 122

    int pts[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    char player1[50];
    char player2[50];

    printf("Player1: ");
    scanf("%s", player1);

    printf("Player2: ");
    scanf("%s", player2);

    if(score(player1, pts) > score(player2, pts)){
        printf("Player 1 wins!\n");
    } else if(score(player1, pts) < score(player2, pts)){
        printf("Player 2 wins!\n");
    } else{
        printf("Tie!\n");
    }
}

int score(char word[], int list[]){

    int points = 0;
    int i = 0;
    while(1){
        if(word[i] == 0){
            break;
        }
        if(word[i] < 91 && word[i] > 64){
            points += list[(int)word[i] - 65];
        } else if(word[i] > 96 && word[i] < 123){
            points += list[(int)word[i] - 97];
        }
        i++;
    }

    return points;
}
