#include <stdio.h>

int main (void){
    int n;
    int i = 0;
    int cont = 1;

    printf("Heigth: ");
    scanf("%d", &n);

    if(n < 1 || n > 8){
        while(1){
            printf("Heigth: ");
            scanf("%d", &n);
            if(n >= 1 && n <= 8){
                break;
            }
        }
    }


    //do
    //{
     //   printf("Heigth: ");
     //   n = scanf("%d", &n);
    //}
    //while(n < 1 || n > 8);

    while(n > 0){
        for(i = 0; i < n; i++){
            printf(" ");
        }
        for(int j = 0; j < cont; j++){
            printf("#");
        }
        printf("\n");
        n--;
        cont++;
    }
}
