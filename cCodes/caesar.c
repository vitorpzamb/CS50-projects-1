#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Usage: ./caesar key\n");
    } else {
        char *end;
        int arg = (int)strtol(argv[1], &end, 10);

        if(argc > 2 || *end != '\0'){
            printf("Usage: ./caesar key\n");
        } else{
            char frase[100];
            printf("plaintext: ");
            fgets(frase, sizeof(frase), stdin);
            printf("ciphertext: ");

            int i = 0;
            while(1){
                if(frase[i] == 0){
                    break;
                }

                int soma = frase[i] + arg;
                if(frase[i] > 64 && frase[i] < 91){
                    if(soma > 90){
                        int resto = soma - 91;
                        frase[i] = 65 + resto;
                    } else{
                        frase[i] += arg;
                    }
                } else if(frase[i] > 96 && frase[i] < 123){
                    if(soma > 122){
                        int resto = soma - 123;
                        frase[i] = 97 + resto;
                    } else{
                        frase[i] += arg;
                    }
                }
                printf("%c", frase[i]);
                i++;
            }
        }
    }

}
