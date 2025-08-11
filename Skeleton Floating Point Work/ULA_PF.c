#include "ULA_PF.h"
//Descomente os códigos com "prints" para debugar o algoritmo


static void printBitsPontoFlutuante(uint32_t val) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (val >> i) & 1);
        if (i == 31 || i == 23) printf(" ");  // separa sinal, expoente, significando
    }
}

static void print8Bits( uint8_t *A){ // Corrigido para uint8_t para evitar warnings
    for (int8_t i = 7; i >= 0; i--) {
        printf("%d", (*A >> i) & 1);
    }
}

static void print16Bits( uint16_t *A){
    for (int8_t i = 15; i >= 0; i--) {
        printf("%d", (*A >> i) & 1);
    }
}

int ULA_ADD_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow){
    //Considerar que o Computador sÃ³ tem registrador de 8 bits
    uint8_t sinalA, ExpPolA, sinalB, ExpPolB, SignfA, SignfB, sinalAB;
    
    *overflow = 0;
    *underflow = 0;

    //Pegar Sinal, expoente e Significando de cada operando
    uint32_t mantissaA_full = *A & 0x7FFFFF;
    uint32_t mantissaB_full = *B & 0x7FFFFF;

    //Pegar Sinal de A
    sinalA = (*A >> 31) & 0x01;
    printf("Sinal A: %d\n",sinalA);

    //Pegar Expoente Polarizado de A
    ExpPolA = (*A >> 23) & 0xFF;
    printf("Expoente Polarizado de A: %d -> Bits: ",ExpPolA);
    print8Bits(&ExpPolA);

    //Pegar sinal de B
    sinalB = (*B >> 31) & 0x01;
    printf("\nSinal B: %d\n",sinalB);

    //Pegar expoente polarizado de B
    ExpPolB = (*B >> 23) & 0xFF;
    printf("Expoente Polarizado de B: %d -> Bits: ",ExpPolB);
    print8Bits(&ExpPolB);

    //Pegar Significando + bit implIcito
    SignfA = (0x80) | (mantissaA_full >> 16);
    printf("\nSignificando Efetivo de A: \t");
    print8Bits(&SignfA);
    
    SignfB = (0x80) | (mantissaB_full >> 16);
    printf("\nSignificando Efetivo de B: \t");
    print8Bits(&SignfB);

    //FASE 1 - Verificar se tem operando igual a zero
    if (ExpPolA == 0 && mantissaA_full == 0) {
        *A = *B;
        return 0;
    }
    if (ExpPolB == 0 && mantissaB_full == 0) {
        return 0;
    }

    //Adiciona bit implícito para cálculo
    mantissaA_full |= 0x800000;
    mantissaB_full |= 0x800000;

    //FASE 2 - Alinhar os Significandos
    if (ExpPolA < ExpPolB) {
        mantissaA_full >>= (ExpPolB - ExpPolA);
        ExpPolA = ExpPolB;
    } else if (ExpPolB < ExpPolA) {
        mantissaB_full >>= (ExpPolA - ExpPolB);
    }

    // Atualiza as variáveis de 8 bits para impressão
    SignfA = mantissaA_full >> 16;
    SignfB = mantissaB_full >> 16;

    printf("\nSignificando de A Alinhado: \t");
    print8Bits(&SignfA);
    printf("\nSignificando de B Alinhado: \t");
    print8Bits(&SignfB);

    //FASE 3 - Somar significandos sinalizados
    uint32_t mantissaResultado;
    sinalAB = sinalA;

    //Primeiro Tranformar os significandos para forma sinalizada
    int32_t SigAS = (sinalA == 1) ? -mantissaA_full : mantissaA_full;
    int32_t SigBS = (sinalB == 1) ? -mantissaB_full : mantissaB_full;
    
    //Realizar a Soma Sinalizada
    int32_t Z_sinalizado = SigAS + SigBS;

    //Codigo para Verificar se Significando eh 0
    if (Z_sinalizado == 0) {
        *A = 0;
        return 0;
    }
    
    //Pegar sinal do resultado da soma dos significandoss
    if (Z_sinalizado < 0) {
        sinalAB = 1;
        //Faz complemento de 2 se resultado da soma dos significandos for negativo
        mantissaResultado = -Z_sinalizado;
    } else {
        sinalAB = 0;
        mantissaResultado = Z_sinalizado;
    }
    
    //===== FASE 4 - Normalizar o resultado
    if (mantissaResultado & 0x1000000) { 
        mantissaResultado >>= 1;
        ExpPolA++;
    } else {
        while (!(mantissaResultado & 0x800000)) {
            mantissaResultado <<= 1;
            ExpPolA--;
        }
    }

    // Verificar overflow/underflow
    if ((int16_t)ExpPolA >= 255) { *overflow = 1; *A = (sinalAB << 31) | (0xFF << 23); return 1; }
    if ((int16_t)ExpPolA <= 0) { *underflow = 1; *A = 0; return 1; }

    //remover bit implicito
    mantissaResultado &= 0x7FFFFF;

    //Montar os bits novamente no Padrao IEEE754
    *A = (sinalAB << 31) | (ExpPolA << 23) | mantissaResultado;

    printf("\nSoma: ");
    printBitsPontoFlutuante(*A);
    return 0;
}

int ULA_SUB_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow){
    //Muda bit de Sinal de B
    *B ^= 0x80000000;
    //Chama ULA_ADD_PF
    return ULA_ADD_PF(A, B, overflow, underflow);
}

int ULA_MUL_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow){
    //Considerar que o Computador sÃ³ tem registrador de 8 bits
    uint8_t sinalA, ExpPolA, sinalB, ExpPolB, SignfA, SignfB, sinalAB;
    int16_t SomaExp_int; // Usar int16_t para o cálculo
    uint8_t SomaExp, polarizador = 0x7F;
    uint16_t Z;

    *overflow = 0;
    *underflow = 0;

    //Pegar Sinal, expoente e Significando de cada operando
    uint32_t mantissaA_full = *A & 0x7FFFFF;
    uint32_t mantissaB_full = *B & 0x7FFFFF;

    //Pegar Sinal de A
    sinalA = (*A >> 31) & 0x01;
    printf("Sinal A: %d\n",sinalA);

    //Pegar Expoente Polarizado de A
    ExpPolA = (*A >> 23) & 0xFF;
    printf("Expoente Polarizado de A: %d -> Bits: ",ExpPolA);
    print8Bits(&ExpPolA);

    //Pegar sinal de B
    sinalB = (*B >> 31) & 0x01;
    printf("\nSinal B: %d\n",sinalB);

    //Pegar expoente polarizado de B
    ExpPolB = (*B >> 23) & 0xFF;
    printf("Expoente Polarizado de B: %d -> Bits: ",ExpPolB);
    print8Bits(&ExpPolB);

    //Pegar Significando + bit implIcito
    SignfA = (0x80) | (mantissaA_full >> 16);
    printf("\nSignificando Efetivo de A: \t");
    print8Bits(&SignfA);

    SignfB = (0x80) | (mantissaB_full >> 16);
    printf("\nSignificando Efetivo de B: \t");
    print8Bits(&SignfB);

    //PASSO 1 - Verificar se tem operando igual a zero
    if ((ExpPolA == 0 && mantissaA_full == 0) || (ExpPolB == 0 && mantissaB_full == 0)) {
        *A = 0;
        return 0;
    }
    
    //Pegar sinal do resultado da multiplicação dos significandos
    sinalAB = sinalA ^ sinalB;

    //PASSO 2 - Somar os Expoentes
    SomaExp_int = (int16_t)ExpPolA + (int16_t)ExpPolB;
    SomaExp = SomaExp_int;
    printf("\nSoma Expoentes: %d \t\t",SomaExp);
    print8Bits(&SomaExp);

    //Subtrai polarização
    SomaExp_int -= polarizador;
    SomaExp = SomaExp_int;
    printf("\nSubtrai Polarizacao: %d \t",SomaExp);
    print8Bits(&SomaExp);

    //PASSO 3 - Verificar Overflow e Underflow de Expoente
    if (SomaExp_int >= 255) { *overflow = 1; *A = (sinalAB << 31) | (0xFF << 23); return 1; }
    if (SomaExp_int <= 0) { *underflow = 1; *A = 0; return 1; }

    //PASSO 4 - Multiplica Significandos
    mantissaA_full |= 0x800000;
    mantissaB_full |= 0x800000;
    uint64_t mult_mantissas = (uint64_t)mantissaA_full * (uint64_t)mantissaB_full;
    Z = mult_mantissas >> 30; // Pega os 16 bits mais significativos para visualização
    printf("\nMult. Significando: %d\t",Z);
    print16Bits(&Z);

    //===== Passo 5  - Normalizar o resultado
    mult_mantissas >>= 23;
    //Normaliza
    if (mult_mantissas & 0x2000000) {
        mult_mantissas >>= 1;
        SomaExp_int++;
    }

    //Retira bit implícito
    uint32_t final_mantissa = mult_mantissas & 0x7FFFFF;

    //Montar os bits novamente no Padrão IEEE754
    *A = (sinalAB << 31) | ((uint8_t)SomaExp_int << 23) | final_mantissa;

    printf("\nMult.: ");
    printBitsPontoFlutuante(*A);
    return 0;
}

int ULA_DIV_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow){
    //Considerar que o Computador so tem registrador de 8 bits
    uint8_t sinalA, ExpPolA, sinalB, ExpPolB, SignfA, SignfB, sinalAB;
    int16_t SubExp_int;
    uint8_t SubExp, polarizador = 0x7F;
    uint8_t Q, R, Z;

    *overflow = 0;
    *underflow = 0;
    
    //Pegar Sinal, expoente e Significando de cada operando
    uint32_t mantissaA_full = *A & 0x7FFFFF;
    uint32_t mantissaB_full = *B & 0x7FFFFF;

    //Pegar Sinal de A
    sinalA = (*A >> 31) & 0x01;
    printf("Sinal A: %d\n",sinalA);

    //Pegar Expoente Polarizado de A
    ExpPolA = (*A >> 23) & 0xFF;
    printf("Expoente Polarizado de A: %d -> Bits: ",ExpPolA);
    print8Bits(&ExpPolA);

    //Pegar sinal de B
    sinalB = (*B >> 31) & 0x01;
    printf("\nSinal B: %d\n",sinalB);

    //Pegar expoente polarizado de B
    ExpPolB = (*B >> 23) & 0xFF;
    printf("Expoente Polarizado de B: %d -> Bits: ",ExpPolB);
    print8Bits(&ExpPolB);

    //Pegar Significando + bit implIcito
    SignfA = (0x80) | (mantissaA_full >> 16);
    printf("\nSignificando Efetivo de A: \t");
    print8Bits(&SignfA);
    
    SignfB = (0x80) | (mantissaB_full >> 16);
    printf("\nSignificando Efetivo de B: \t");
    print8Bits(&SignfB);

    //PASSO 1 - Verificar se tem operando igual a zero
    if (ExpPolB == 0 && mantissaB_full == 0) {
        *overflow = 1; // Divisão por zero
        *A = (sinalA << 31) | (0xFF << 23);
        return 1;
    }
    if (ExpPolA == 0 && mantissaA_full == 0) {
        *A = 0;
        return 0;
    }

    //Pegar sinal do resultado da multiplicação dos significandos
    sinalAB = sinalA ^ sinalB;

    //PASSO 2 - Subtrai os Expoentes
    SubExp_int = (int16_t)ExpPolA - (int16_t)ExpPolB;
    SubExp = SubExp_int;
    printf("\nSubtrai Expoentes: %d \t\t",SubExp);
    print8Bits(&SubExp);

    //Soma polarização
    SubExp_int += polarizador;
    SubExp = SubExp_int;
    printf("\nSoma Polarizacao: %d \t\t",SubExp);
    print8Bits(&SubExp);

    //PASSO 3 - Verificar Overflow e Underflow de Expoente
    if (SubExp_int >= 255) { *overflow = 1; *A = (sinalAB << 31) | (0xFF << 23); return 1; }
    if (SubExp_int <= 0) { *underflow = 1; *A = 0; return 1; }

    //PASSO 4 - Divide Significandos
    mantissaA_full |= 0x800000;
    mantissaB_full |= 0x800000;
    uint64_t dividendo = (uint64_t)mantissaA_full << 23;
    
    //Calcula Quociente
    uint64_t quociente_full = dividendo / mantissaB_full;
    Q = quociente_full >> 16;

    //Calcula Resto
    uint64_t resto_full = dividendo % mantissaB_full;
    R = resto_full >> 16;
    
    printf("\nQuociente Significandos: \t");
    print8Bits(&Q);
    printf("\nResto do Significandos: \t");
    print8Bits(&R);

    //===== Passo 5  - Normalizar o resultado
    //Normalize
    if (!(quociente_full & 0x800000)) {
        quociente_full <<= 1;
        SubExp_int--;
    }

    //Retira bit implícito
    uint32_t final_mantissa = quociente_full & 0x7FFFFF;

    //Montar os bits novamente no Padrão IEEE754
    *A = (sinalAB << 31) | ((uint8_t)SubExp_int << 23) | final_mantissa;

    printf("\nDiv.: ");
    printBitsPontoFlutuante(*A);
    return 0;
}