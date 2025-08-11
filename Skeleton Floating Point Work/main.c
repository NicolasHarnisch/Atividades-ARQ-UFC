#include "ULA_PF.h"
#define MAX_LINHAS 200 // Defina um limite máximo de linhas de dados

int lerArquivo(float (*operandos)[2]);

static void printBitsPontoFlutuante(uint32_t val) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (val >> i) & 1);
        if (i == 31 || i == 23) printf(" ");  // separa sinal, expoente, significando
    }
}

int main() {

    /*Cabeçalho*/
    printf("\t\t\t\t==========================================\n");
    printf("\t\t\t\t SIMULADOR DE ULA - v0.3  by Prof. Reuber      \n");
    printf("\t\t\t\t      ARITMETICA EM PONTO FLUTUANTE      \n");
    printf("\t\t\t\t==========================================\n");

    float operandos[MAX_LINHAS][2];

    int linhas = lerArquivo(operandos);

    for(int i=0;i<linhas;i++){
        uint8_t overflow=0, underflow=0;
        float a = operandos[i][0], aa;
        float b = operandos[i][1], bb;
        aa = a;
        bb = b;
        uint32_t * A = (uint32_t*)&aa;  // passando os bits de float para int
        uint32_t * B = (uint32_t*)&bb;

        printf("----------------------------------------------\n");
        printf("Operando A: (%11f)_10 = (",a);
        printBitsPontoFlutuante(*A);
        printf(")_IEEE754\n");
        printf("Operando B: (%11f)_10 = (",b);
        printBitsPontoFlutuante(*B);
        printf(")_IEEE754\n");

        //Retire os comentarios de acordo com implementacao de cada operacao
       ULA_ADD_PF(A,B, &overflow, &underflow);
       printf("ADD_PF:   REG A: %11f           \tOverflow:%d \tUnderflow:%d\n",aa,overflow,underflow);
       aa = a;
       bb = b;
       ULA_SUB_PF(A,B,&overflow,&underflow);
       printf("SUB_PF:   REG A: %11f           \tOverflow:%d \tUnderflow:%d\n",aa,overflow,underflow);
       aa = a;
       bb = b;
       ULA_MUL_PF(A,B,&overflow,&underflow);
       printf("MUL_PF:   REG A: %11f           \tOverflow:%d \tUnderflow:%d\n",aa,overflow,underflow);
       aa = a;
       bb = b;
       ULA_DIV_PF(A,B,&overflow,&underflow);
       printf("DIV_PF:   REG A: %11f           \tOverflow:%d \tUnderflow:%d\n",aa,overflow,underflow);
    }

    printf("\n\nExecucao concluida. Pressione Enter para sair...");
    getchar();

    return 0;
}

int lerArquivo (float (* op)[2]){
    /*---------------------------------*/
    //Leitura de Arquivo com os Operandos
    FILE *arquivo = fopen("operandos.txt", "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    int linhas = 0;                  // Contador de linhas
    // Lendo os pares de números do arquivo até EOF
    while (linhas < MAX_LINHAS && fscanf(arquivo, "%f %f", &op[linhas][0], &op[linhas][1]) == 2) {
        linhas++;
    }
    fclose(arquivo);
    return linhas;
    //Fim da Leitura do Arquivo com Operandos
    /*----------------------------*/
}