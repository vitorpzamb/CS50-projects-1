#include <stdio.h>
#include <math.h>

int main(void){

    long int a = 9999999999999;
    long int b = a/10000000000;
    printf("%ld\n", b);

    if(a/10000000000 > 100){
        printf("boa\n");
    } else{
        printf("ruim\n");
    }
}
