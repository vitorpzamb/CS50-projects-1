//O CODIGO FUNCIONAL ESTA NA PASTA VOLUME NA PSET4 ONDE TEMOS DOIS ARQUIVOS DE AUDIO

// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    BYTE bytes[44];
    size_t lidos = fread(bytes, sizeof(BYTE), 44, input);

    size_t escritos = fwrite(bytes, sizeof(BYTE), 44, output);

    if(lidos != escritos){
        printf("Erro\n");
    } else{
        printf("ok!\n");
    }

    // TODO: Read samples from input file and write updated data to output file
    int16_t bytes2[2];
    while((fread(bytes2, sizeof(int16_t), 2, input)) == 2){
        bytes2[0] *= factor;
        bytes2[1] *= factor;

        fwrite(bytes2, sizeof(int16_t), 2, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
