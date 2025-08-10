#include <stdio.h>
#include <stdint.h>

//uint8_t - pArA inteiros não sinAlizAdos
//int8_t - pArA inteiros sinAlizAdos

void somadorcompleto(uint8_t A, uint8_t B, uint8_t Cin, uint8_t *S, uint8_t *Cout){

*S = (~A & ~B & Cin) | (~A & B & ~Cin) | (A & B & Cin) | (A & ~B & ~Cin);
*Cout = (A & B) | (A & Cin) | (B & Cin);
}


void somadorde8Bits(uint8_t *A, uint8_t *B, uint8_t *Cin, uint8_t *soma, uint8_t *Cout, uint8_t *overflow){

    *Cin = 0;
    for(int i=0 ; i<=7;i++){
        if(i!=0)*Cin = *Cout;
        somadorcompleto((*A >> i) & 1, (*B >> i) & 1, *Cin, soma , Cout);
         *A = (*soma == 1) ? ( *A | (1<<i)):(*A & ~(1<<i));   
    }

    *overflow = *Cin ^ *Cout;
}

int main(){
    uint8_t  A = 127, B = 10, soma, Cout, ov;
    uint8_t Cin;
    somadorde8Bits(&A, &B, &Cin, &soma, &Cout, &ov);
    printf("somador completo\n soma = %d\n count = %d\n overflow = %d",A,Cout,ov);
    return 0;
}

 
// outro codigo 

