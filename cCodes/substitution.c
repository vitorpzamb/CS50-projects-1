#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

int valido(char *vetor);

int main(int argc, char *argv[]){

    char aux[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    char aux1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    if(argc == 1){
        printf("Usage: ./substitution KEY\n");
    } else{
        int k = strlen(argv[1]);
        if((k < 26 && k != 0) || k > 26){
            printf("Key must contain 26 characters\n");
        } else if(valido(argv[1]) == 1) {
            printf("Key must contain alphabetic characters\n");
        } else if(valido(argv[1]) == 2){
            printf("Key must not contain repeated characters\n");
        } else{
            char word[50];
            printf("plaintext: ");
            fgets(word, sizeof(word), stdin);
            printf("ciphertext: ");

            int n = 0;
            while(1){
                if(word[n] == '\0'){
                    break;
                }
                if(isupper(word[n])){
                    for(int i = 0; i < 26; i++){
                        if(word[n] == aux1[i]){
                            if(isupper(argv[1][i])){
                                printf("%c", argv[1][i]);
                            } else{
                                printf("%c", toupper(argv[1][i]));
                            }
                        }
                    }
                } else if(islower(word[n])){
                    for(int i = 0; i < 26; i++){
                        if(word[n] == aux[i]){
                            if(islower(argv[1][i])){
                                printf("%c", argv[1][i]);
                            } else{
                                printf("%c", tolower(argv[1][i]));
                            }
                        }
                    }
                } else{
                    printf("%c", word[n]);
                }
                n++;
            }
        }
    }
}

int valido(char *vetor){

    bool visto[256] = {false};

    for(int i = 0; vetor[i] != '\0'; i++){
        if(visto[(int)vetor[i]] == true){
            return 2;
        }
        visto[(int)vetor[i]] = true;

        if(vetor[i] < 'A' || (vetor[i] > 'Z' && vetor[i] < 'a') || vetor[i] > 'z'){ //nao pode ter repetida tmb
            return 1;
        }
    }
    return 0;
}
