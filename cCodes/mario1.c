#include <stdio.h>

int main(void){

    int n;
    int i;
    int j;
    int cont = 1;

    printf("Heigth: ");
    scanf("%d", &n);

    if(n < 1 || n > 8){
        while(1){
            printf("Heigth: ");
            scanf("%d", &n);
            if(n >= 1 && n <= 8){
                break;              //pedir uma altura entre 1 e 8 (pedir novamente se o numero digitado estiver fora do intervalo)
            }
        }
    }

    while(n > 0){
        for(i = 0; i < n; i++){
            printf(" ");
        }
        for(j = 0; j < cont; j++){
            printf("#");
        }
        printf("  ");
        for(j = 0; j < cont; j++){
            printf("#");
        }
        for(i = 0; i < n; i++){
            printf(" ");
        }
        printf("\n");
        n--;
        cont++;
    }
}
