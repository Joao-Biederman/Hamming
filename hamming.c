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

    if (!readingFile) // No caso de erro na abertura do arquivo retorna um código de erro
    {
        fclose(readingFile);
        return (1);
    }

    char nomeArquivo[100]; // Abre um arquivo para escrita com o mesmo nome do aberto + .wham
    strcpy(nomeArquivo, arquivo);
    strcat(nomeArquivo, ".wham");
    writingFile = fopen(nomeArquivo, "w+b");

    int len;
    fseek(readingFile, 0, SEEK_END); // Vai até o final do arquivo para calcular o tamanho dele.
    len = ftell(readingFile);
    fseek(readingFile, 0, SEEK_SET); // Volta para o começo do arquivo para começar a ler

    int MCG[13], M[8], number;
    for (int i = 0; i < len; i++)
    {
        fread(&number, sizeof(char), 1, readingFile); // Pega o valor inteiro do próximo byte
        // printf("%d\n", number);

        for (int i = 0; i < 8; i++) // Transforma o valor inteiro em um vetor binário
        {
            M[i] = number % 2;
            number /= 2;
        }

        MCG[1] = (M[6] ^ M[4] ^ M[3] ^ M[1] ^ M[0]);  // Calcula os bits de controle, responsaveis por gerar o local da sindrome
        MCG[2] = (M[6] ^ M[5] ^ M[3] ^ M[2] ^ M[0]);
        MCG[4] = (M[7] ^ M[3] ^ M[2] ^ M[1]);
        MCG[8] = (M[7] ^ M[6] ^ M[5] ^ M[4]);

        MCG[0] = (M[7] ^ M[6] ^ M[5] ^ M[4] ^ MCG[8] ^ M[3] ^ M[2] ^ M[1] ^ MCG[4] ^ M[0] ^ MCG[2] ^ MCG[1]); // gera o bit de controle responsável por controlar a aceitação ou não da palavra
        MCG[3] = M[0]; // Armazena o valor binário nos espaços remanescentes do bloco
        MCG[5] = M[1];
        MCG[6] = M[2];
        MCG[7] = M[3];
        MCG[9] = M[4];
        MCG[10] = M[5];
        MCG[11] = M[6];
        MCG[12] = M[7];

        for (int i = 12; i >= 0; i--) //Escreve o bloco no arquivo de saida
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

    fclose(readingFile); // Fecha ambos os arquivos
    fclose(writingFile);
    return (0);
}

int leitura(char *arquivo)
{
    FILE *readingFile, *newFile;

    readingFile = fopen(arquivo, "rb+");

    if (!readingFile) // No caso de erro na abertura do arquivo retorna um código de erro
    {
        fclose(readingFile);
        return (1);
    }

    memset(strrchr(arquivo, '.'), '\0', 1);


    newFile = fopen(arquivo, "w");


    int len;
    fseek(readingFile, 0, SEEK_END); // Vai até o final do arquivo para calcular o tamanho dele.
    len = ftell(readingFile);
    fseek(readingFile, 0, SEEK_SET); // Volta para o começo do arquivo para começar a ler

    char text; // A leitura é realizada por uma variavel tipo char por ocupar menos espaço que um inteiro
    int MCG[13], C[4];
    for (int i = 0; i < len; i += 13)
    {
        for (int i = 12; i >= 0; i--)
        {
            fread(&text, sizeof(char), 1, readingFile); //Lê bit por bit e salva o bloco inteiro e em MCG
            if (text == 49)
                MCG[i] = 1;
            else
                MCG[i] = 0;            
        }

        C[0] = (MCG[3] ^ MCG[5] ^ MCG[7] ^ MCG[9] ^ MCG[11]); //Calculo de C'
        C[1] = (MCG[3] ^ MCG[6] ^ MCG[7] ^ MCG[10] ^ MCG[11]);
        C[2] = (MCG[5] ^ MCG[6] ^ MCG[7] ^ MCG[12]);
        C[3] = (MCG[9] ^ MCG[10] ^ MCG[11] ^ MCG[12]);

        // Gera o local da sindrome com base nos bits de controle salvos em MCG e C'
        int sindrome = (MCG[1] ^ C[0]) + (MCG[2] ^ C[1]) * 2 + (MCG[4] ^ C[2]) * 4 + (MCG[8] ^ C[3]) * 8;
        printf("sindrome %d\n", sindrome);
        int erro = 0;
        if (sindrome) // Se a sindrome for diferente de 0 vai para a posição sindrome e inverte o bit
        {
            MCG[sindrome] = !MCG[sindrome];
            erro = 1;
            printf("Corrigido erro\n");
        }

        int G = 0; // Define G (controle de aceitação de palavra) como 0
        for (int i = 1; i < 13; i++)
        {
            G = G ^ MCG[i]; // xor entre todos os elementos de MCG exceto a posição ocupada pelo bit de controle de aceitação de palavra
        }

        if (G ^ MCG[0]) // se os bits de controle de aceitação forem diferentes a palavra está errada e será rejeitada
            printf("Uma palavra rejeitada\n");
        else
        {
            printf("%d%d%d%d%d%d%d%d\n", MCG[12], MCG[11], MCG[10], MCG[9], MCG[7], MCG[6], MCG[5], MCG[3]);
            if (erro)
            {            
                fseek(readingFile, -13, SEEK_CUR);
                for (int i = 12; i >= 0; i--)
                {
                    fwrite((MCG[i] == 1 ? "1" : "0"), sizeof(char), 1, readingFile);
                }
            }
        }

        int number = 0;
        for (int i = 3, cont = 0; i < 13; i++)
        {
            if (i != 8 && i != 4)
            {
                number += MCG[i] * (int)pow(2, cont++);
            }
        }
        
        fwrite(&number, sizeof(char), 1, newFile);
    }

    fclose(readingFile);
    fclose(newFile);
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