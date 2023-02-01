#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// ================================================================= //
//                             Funções                               //
// ================================================================= //

int gravacao(char *arquivo)
{
    FILE *readingFile, *writingFile;

    readingFile = fopen(arquivo, "rb");

    if (!readingFile)
    {
        fclose(readingFile);
        return (1);
    }

    char nomeArquivo[100];
    strcpy(nomeArquivo, arquivo);
    strcat(nomeArquivo, ".wham");
    writingFile = fopen(nomeArquivo, "w+b");
    int len;

    fseek(readingFile, 0, SEEK_END);
    len = ftell(readingFile);
    fseek(readingFile, 0, SEEK_SET);

    char text;
    int MCG[13], M[8], number;
    for (int i = 0; i < len; i++)
    {
        fread(&text, sizeof(char), 1, readingFile);
        number = text;
        printf("%d\n", number);
        for (int i = 0; i < 8; i++)
        {
            M[i] = number % 2;
            number /= 2;
        }

        MCG[1] = (M[6] ^ M[4] ^ M[3] ^ M[1] ^ M[0]);
        MCG[2] = (M[6] ^ M[5] ^ M[3] ^ M[2] ^ M[0]);
        MCG[4] = (M[7] ^ M[3] ^ M[2] ^ M[1]);
        MCG[8] = (M[7] ^ M[6] ^ M[5] ^ M[4]);

        MCG[0] = (M[7] ^ M[6] ^ M[5] ^ M[4] ^ MCG[8] ^ M[3] ^ M[2] ^ M[1] ^ MCG[4] ^ M[0] ^ MCG[2] ^ MCG[1]);
        MCG[3] = M[0];
        MCG[5] = M[1];
        MCG[6] = M[2];
        MCG[7] = M[3];
        MCG[9] = M[4];
        MCG[10] = M[5];
        MCG[11] = M[6];
        MCG[12] = M[7];

        for (int i = 12; i >= 0; i--)
        {
            if (MCG[i] == 1)
            {
                fwrite("1", sizeof(char), 1, writingFile);
            }
            else if (MCG[i] == 0)
            {
                fwrite("0", sizeof(char), 1, writingFile);
            }
        }
    }

    fclose(readingFile);
    fclose(writingFile);
    return (0);
}

int leitura(char *arquivo)
{
    FILE *readingFile;

    readingFile = fopen(arquivo, "rb");

    if (!readingFile)
    {
        fclose(readingFile);
        return (1);
    }

    int len;

    fseek(readingFile, 0, SEEK_END);
    len = ftell(readingFile);
    fseek(readingFile, 0, SEEK_SET);

    char text;
    int MCG[13], C[4];
    for (int i = 0; i < len; i += 13)
    {
        // fread(&text, sizeof(char), 13, readingFile);
        // printf("Lido\n");

        for (int i = 12; i >= 0; i--)
        {
            fread(&text, sizeof(char), 1, readingFile);
            MCG[i] = strcmp(&text, "1") ? 0 : 1;
        }
        // printf("Salvo no MCG\n");

        C[0] = (MCG[3] ^ MCG[5] ^ MCG[7] ^ MCG[9] ^ MCG[11]);
        C[1] = (MCG[3] ^ MCG[6] ^ MCG[7] ^ MCG[10] ^ MCG[11]);
        C[2] = (MCG[5] ^ MCG[6] ^ MCG[7] ^ MCG[12]);
        C[3] = (MCG[9] ^ MCG[10] ^ MCG[11] ^ MCG[12]);

        int sindrome = 0;

        // for (int i = 12; i >= 0; i--)
        //     printf("%d", MCG[i]);

        sindrome = (MCG[1] ^ C[0]) + (MCG[2] ^ C[1]) * 2 + (MCG[2] ^ C[1]) * 4 + (MCG[2] ^ C[1]) * 8;
        printf("sindrome %d\n", sindrome);
        if (sindrome)
        {
            MCG[sindrome] = MCG[sindrome] == 0 ? 0 : 1;
            printf("Corrigido erro\n");
        }

        int G = 0;
        // printf("G' criado\n");
        for (int i = 1; i < 13; i++)
        {
            G = G ^ MCG[i];
        }
        // printf("passou o for\n");

        // printf("%c", MCG[3] + MCG[5] * 2 + MCG[6] * 4 + MCG[7] * 8 + MCG[9] * 16 + MCG[10] * 32 + MCG[11] * 64 + MCG[12] * 128);

        if (G ^ MCG[0])
            printf("Palavra rejeitada\n");
        else
        {
            // printf("%c", MCG[3] + MCG[5] * 2 + MCG[6] * 4 + MCG[7] * 8 + MCG[9] * 16 + MCG[10] * 32 + MCG[11] * 64 + MCG[12] * 128);
            printf("%d%d%d%d%d%d%d%d\n", MCG[12], MCG[11], MCG[10], MCG[9], MCG[7], MCG[6], MCG[5], MCG[3]);
            // printf("... ");
        }
    }

    return (0);
}

// ================================================================= //

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Numero de parametros incorreto, verifique e insira novamente!\n");
        printf("Os parametros para gravacao com integridade de hamming sao './hamming nomeDoArquivo.qualquercoisa -w'\n");
        printf("Os parametros para leitura com integridade de hamming sao './hamming nomeDoArquivo.qualquercoisa.wham -r'\n");
        return (0);
    }
    unsigned writing = strcmp(argv[2], "-w");
    unsigned reading = strcmp(argv[2], "-r");

    if (writing != 0 && reading != 0)
    {
        printf("Funcao nao reconhecida! verifique e insira novamente\n");
        printf("Os parametros para gravacao com integridade de hamming sao './hamming nomeDoArquivo.qualquercoisa -w'\n");
        printf("Os parametros para leitura com integridade de hamming sao './hamming nomeDoArquivo.qualquercoisa.wham -r'\n");
        return (0);
    }

    int erro;
    switch (writing)
    {
    case 0:
        erro = gravacao(argv[1]);
        break;

    default:
        erro = leitura(argv[1]);
        break;
    }

    if (erro == 1) // O código de erro 1 é para arquivo nao encontrado
    {
        printf("Arquivo nao encontrado, verifique e insira novamente\n");
        printf("Os parametros para gravacao com integridade de hamming sao './hamming nomeDoArquivo.qualquercoisa -w'\n");
        printf("Os parametros para leitura com integridade de hamming sao './hamming nomeDoArquivo.qualquercoisa.wham -r'\n");
        return 0;
    }

    return 0;
}