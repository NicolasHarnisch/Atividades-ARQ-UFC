#include "ULA.h"
#include <stdio.h>

//Somador Baseado no livro Willian Stallings 10ed, capítulo 10, pag. 334
static void somadorCompleto(uint8_t A, uint8_t B, uint8_t cin, uint8_t * s, uint8_t * cout){
    *s = (~A & ~B & cin) | (~A & B & ~cin) | (A & B & cin) | (A & ~B & ~cin);
    *cout = (A & B) | (A & cin) | (B & cin);
}

static void somador8bits(uint8_t * regA, uint8_t * regB, uint8_t * cin, uint8_t * soma, uint8_t * cout, uint8_t * overflow){
    *cin = 0;
    for(int i=0 ; i<=7;i++){
        if(i!=0) * cin = * cout;
        somadorCompleto((*regA >> i) & 1, (*regB >> i) & 1, *cin, soma , cout);
         *regA = (*soma == 1) ? ( *regA | (1<<i)):(*regA & ~(1<<i));    
    }

    *overflow = *cin ^ *cout;
    
}

static void complementador(uint8_t * A){
    uint8_t BAux = 1, cin, s, cout,o;
    *A = ~(*A);
    somador8bits(A,&BAux, &cin, &s, &cout, &o);
}


void ULA_ADD(int8_t * regA, int8_t * regB, int8_t * overflow){
    uint8_t cin = 0, s, cout;

    // Faça o "cast" dos ponteiros para o tipo que a função espera
    somador8bits((uint8_t*)regA, (uint8_t*)regB, &cin, &s, &cout, (uint8_t*)overflow);
}

void ULA_SUB(int8_t * regA, int8_t * regB, int8_t * overflow){
    uint8_t BAux; 
    uint8_t cin = 0, s, cout, o_sub;
    
    BAux = *regB; 
    complementador(&BAux); 

    somador8bits((uint8_t*)regA, &BAux, &cin, &s, &cout, overflow);
}

//Multiplicação de Q(8bits) com M(8bits) gera resultado de 16bits que está em A(8bits) e Q(8bits)
void ULA_MUL(int8_t * A, int8_t * Q, int8_t * M,  int8_t * overflow){
    *A = 0;
    uint8_t Q_1 = 0, cont = 0;

    //Estrutura de repetição para multiplicação
     for(cont = 0; cont < 8; cont++){
        uint8_t Q0 = *Q & 1; 

        if (Q0 == 1 && Q_1 == 0) { 
            ULA_SUB(A, M, overflow);
        } else if (Q0 == 0 && Q_1 == 1) { 
            ULA_ADD(A, M, overflow);
        }

        Q_1 = Q0; 
        uint8_t LSB_A = *A & 1;
        *A = *A >> 1;
        *Q = (uint8_t)*Q >> 1; 
        *Q = *Q | (LSB_A << 7); 
        }   
    }

//Divisão com sinal de Q(Dividendo de 8bits) por M(Divisor de 8bits) com Quociente em Q(8bits) e Resto em A(8bits)
void ULA_DIV(int8_t * A, int8_t * Q, int8_t * M, int8_t * overflow){
    if (*M == 0) {
        *A = 0;
        *Q = 0;
        *overflow = 1;
        return;
    }

    int8_t A_reg = 0;
    int8_t Q_reg_original = *Q;
    int8_t M_reg_original = *M;

    int8_t M_abs = (M_reg_original < 0) ? -M_reg_original : M_reg_original;
    int8_t Q_abs = (Q_reg_original < 0) ? -Q_reg_original : Q_reg_original;

    *A = 0;
    *Q = Q_abs;

    int8_t i;

    for(i = 0; i < 8; i++){
        A_reg = (A_reg << 1) | ((*Q & 0x80) >> 7);
        *Q <<= 1;

        int8_t M_temp = M_abs;
        int8_t aux_overflow = 0;
        ULA_SUB(&A_reg, &M_temp, &aux_overflow);

        if (A_reg < 0) {
            M_temp = M_abs;
            ULA_ADD(&A_reg, &M_temp, &aux_overflow);
            *Q &= ~1;
        } else {
            *Q |= 1;
        }
    }

    if (*Q == -128 && M_reg_original == -1 && Q_reg_original == -128) {
         *overflow = 1;
         *A = 0;
         *Q = 0;
         return;
    } 

    if ((Q_reg_original < 0) ^ (M_reg_original < 0)) {
        *Q = -*Q;
    }

    if (Q_reg_original < 0) {
        *A = -A_reg;
    } else {
        *A = A_reg;
    }

    *overflow = 0;
}
