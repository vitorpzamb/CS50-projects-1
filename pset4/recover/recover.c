#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if(f == NULL){
        printf("Could not open fila.\n");
        return 1;
    }

    int num = 0;
    BYTE bytes[512];
    size_t lidos = fread(bytes, sizeof(BYTE), 512, f);

    FILE *img = NULL;

    while(lidos == 512){
        if(bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0){

            if(img != NULL){ //aqui fechamos o ultimo jpeg para iniciarmos o proximo
                fclose(img);
            }

            char filename[10];
            sprintf(filename, "%03i.jpg", num);
            img = fopen(filename, "w");

            if(img == NULL){
                printf("Could not create image file.\n");
                return 1;
            }

            // Escreve o primeiro bloco no novo arquivo JPEG, se nao fizessemos isso perderiamos o bloco que tem o comeco do jpeg e ele nao seria colocado no img
            fwrite(bytes, sizeof(BYTE), 512, img);

            // Lê o próximo bloco antes de entrar no while interno (fazemos isso para a condicao do while funcionar, se nao nem entrariamos no while)
            lidos = fread(bytes, sizeof(BYTE), 512, f);

            // Escreve os blocos subsequentes até encontrar um novo JPEG ou o final do arquivo
            while(lidos == 512 && !(bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)){
                fwrite(bytes, sizeof(BYTE), 512, img); //um chunk de 512 bytes, que queremos escrever em img
                lidos = fread(bytes, sizeof(BYTE), 512, f);
                //quando acharmos um novo comeco de jpeg, seus bytes ficarao armazenados em bytes[]
            }
            num++;
        } else{
            lidos = fread(bytes, sizeof(BYTE), 512, f); //isso apenas para o comeco do cartao de memoria, que pode ter blocos que nao sao comecos de jpeg
        }
    }

    if(img != NULL){ //aqui vamos fechar o ultimo arquivo por que chegamos no final do cartao de memoria
        fclose(img);
    }

    fclose(f);
}
