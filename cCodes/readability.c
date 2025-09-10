#include <stdio.h>
#include <math.h>

void grade(char frase[]);

int main(void){


    char frase[400];
    printf("Text: ");
    fgets(frase, sizeof(frase), stdin);

    grade(frase);
}

void grade(char frase[]){

    float l;
    float s;

    int i = 0;
    int letters = 0;
    int spaces = 0;
    int sentences = 0;
    while(1){
        if(frase[i] == 0){
            l = (100/((float)spaces+1))*(float)letters; //numero medio de letras a cada 100 palavras
            s = (100/((float)spaces+1))*(float)sentences; //numero médio de sentenças a cada 100 palavras
            break;
        }

        if((frase[i] >= 65 && frase[i] <= 90) || (frase[i] >= 97 && frase[i] <= 122)){
            letters++;
        }
        if(frase[i] == 32){
            spaces++;
        }
        if(frase[i] == 46){ //44 63 e 33
            sentences++;
        }
        i++;
    }

    float index = (0.0588 * l) - (0.296 * s) - 15.8;
    if(index < 1){
        printf("Before Grade 1\n");
    } else if(index > 16){
        printf("Grade 16+\n");
    } else{
        printf("Grade %.0f\n", round(index));
    }
}
