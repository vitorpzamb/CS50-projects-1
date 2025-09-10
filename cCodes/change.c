#include <stdio.h>

int main(void){

    float aux;
    printf("Total: ");
    scanf("%f", &aux);

    if(aux < 0 || aux > 1){
        while(1){
            printf("Total: ");
            scanf("%f", &aux);
            if(aux >= 0 && aux <= 1){
                break;
            }
        }
    }

    //temos moedas de $0.25, $0.10, $0.05 e $0.01

    int num = 0;
    while(aux > 0.005){  //aqui usamos 0.005 ao inves de 0 por estarmos trabalhando com floats (as vezes o computador erra na aproximacao e nunca chega exatamente em 0)
        if(aux >= 0.25){
            aux -= 0.25;
            num += 1;
        } else if(aux < 0.25 && aux >= 0.10){
            aux -= 0.10;
            num += 1;
        } else if(aux < 0.10 && aux >= 0.05){
            aux -= 0.05;
            num += 1;
        } else{
            aux -= 0.01;
            num += 1;
        }
    }
    printf("%d\n", num);
}
