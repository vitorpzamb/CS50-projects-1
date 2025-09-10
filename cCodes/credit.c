#include <stdio.h>
#include <math.h>

int valid(long int n){
    int sum = 0;
    int k;
    int x;
    int upper;

    if((n/100000000000) < 100){
        //o numero tem 13 digitos
        upper = 13;
    } else if((n/10000000000000) < 100){
        //o numero tem 15 digitos
        upper = 15;
    } else if((n/100000000000000) < 100){
        //o numero tem 16 digitos
        upper = 17;
    } else{
        return 0;
    }

    for(int i = 1; i < upper; i = i + 2){
        k = (n/(long int)pow(10,i))%10;
        x = k*2;
        if(x > 9){
            sum += x/10; //primeiro digito
            sum += x%10; //segundo digito
        } else{
            sum += x;
        }
    }

    for(int i = 0; i < upper; i = i + 2){
        k = (n/(long int)pow(10,i))%10;
        sum += k;
    }

    if(sum % 10 != 0){
        return 0;
    } else{
        if(upper == 15){
            return 1;
        } else if((n/(long int)pow(10,15))%10 == 5){
            return 2;
        } else if((n/(long int)pow(10,15))%10 == 4 || (n/(long int)pow(10,12))%10 == 4){
            return 3;
        } else{
            return 0;
        }
    }
}

int main(void){

    long int n;
    printf("Number: ");
    scanf("%ld", &n);

    if(n/10000000000 < 100){
        while(1){
            printf("Number: ");
            scanf("%ld", &n);
            if(n/10000000000 > 100){
                break;
            }
        }
    }

    if(valid(n) == 0){
        printf("Invalid\n");
    } else if(valid(n) == 1){
        printf("American Express\n");
    } else if(valid(n) == 2){
        printf("MasterCard\n");
    } else{
        printf("Visa\n");
    }
}
