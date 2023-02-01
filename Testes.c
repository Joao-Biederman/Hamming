#include <stdio.h>
#include <math.h>

int main(int argc, char const *argv[])
{
    /*FILE *correctionFile;
    // palavra de teste 4 bits ----- palavra a ser corrigida 8

    correctionFile = fopen(argv[1], "r+b");

    if (!correctionFile)
    {
        fclose(correctionFile);
        printf("Arquivo inexistente\n");
        // return 0;
    }

    int M[8], C[4], G;
    int cont = 1;

    do
    {
        for (int i = 0; i < 8; i++)
        {
            M[i] = 0;
        }

        M[7] = 1;
        M[4] = 1;
        M[3] = 1;

        C[0] = (M[6] ^ M[4] ^ M[3] ^ M[1] ^ M[0]);
        C[1] = (M[6] ^ M[5] ^ M[3] ^ M[2] ^ M[0]);
        C[2] = (M[7] ^ M[3] ^ M[2] ^ M[1]);
        C[3] = (M[7] ^ M[6] ^ M[5] ^ M[4]);

        G = (M[7] ^ M[6] ^ M[5] ^ M[4] ^ C[3] ^ M[3] ^ M[2] ^ M[1] ^ C[3] ^ M[0] ^ C[1] ^ C[0]);

    } while (0);

    int C_[4], G_;
    do
    {
        C_[0] = (M[6] ^ M[4] ^ M[3] ^ M[1] ^ M[0]);
        C_[1] = (M[6] ^ M[5] ^ M[3] ^ M[2] ^ M[0]);
        C_[2] = (M[7] ^ M[3] ^ M[2] ^ M[1]);
        C_[3] = 1;

        int sindrome[4];
        printf("\n\nC =\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%d\n", C[i]);
        }
        printf("\nC_ =\n");
        for (int i = 0; i < 4; i++)
        {
            printf("%d\n", C_[i]);
        }

        printf("\n\nSindrome =\n");
        for (int i = 0; i < 4; i++)
        {
            sindrome[i] = C[i] ^ C_[i];
            printf("%d\n", sindrome[i]);
        }

        if (sindrome[3] || sindrome[2] || sindrome[1] || sindrome[0])
        {
            int error = (pow(2, 3) * sindrome[3]) + (pow(2, 2) * sindrome[2]) + (pow(2, 1) * sindrome[1]) + (pow(2, 0) * sindrome[0]);

            int MC[12];
            MC[11] = M[7];
            MC[10] = M[6];
            MC[9] = M[5];
            MC[8] = M[4];
            MC[7] = C_[3];
            MC[6] = M[3];
            MC[5] = M[2];
            MC[4] = M[1];
            MC[3] = C_[2];
            MC[2] = M[0];
            MC[1] = C_[1];
            MC[0] = C_[0];

            MC[error - 1] = MC[error - 1] == 1 ? 0 : 1; // condição ? verdadeiro : falso

            G_ = (MC[11] ^ MC[10] ^ MC[9] ^ MC[8] ^ MC[7] ^ MC[6] ^ MC[5] ^ MC[4] ^ MC[3] ^ MC[2] ^ MC[1] ^ MC[0]);
            break;
        }

        G_ = (M[7] ^ M[6] ^ M[5] ^ M[4] ^ C_[3] ^ M[3] ^ M[2] ^ M[1] ^ C_[3] ^ M[0] ^ C_[1] ^ C_[0]);

    } while (0);

    printf("\nParidade geral = %d\n", (G ^ G_));
    */

    printf("%d", sizeof(char));
    return 0;
}
