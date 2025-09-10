#include <stdio.h>

int main(void){
    int start;
    int end;
    int cont = 0;

    printf("Start size: ");
    scanf("%d", &start);

    if(start < 9){
        while(1){
            printf("Start size: ");
            scanf("%d", &start);
            if(start >= 9){
                break;
            }
        }
    }

    printf("End size: ");
    scanf("%d", &end);

    if(start > end){
        while(1){
            printf("End size: ");
            scanf("%d", &end);

            if(start <= end){
                break;
            }
        }
    }

    while(start < end){
        start = start + (start/3) - (start/4);
        cont++;
    }

    printf("%d\n", cont);
}
