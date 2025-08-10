#ifndef ULA_PF_H
#define ULA_PF_H

#include <stdint.h>
#include <stdio.h>

int ULA_ADD_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow);
int ULA_SUB_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow);
int ULA_MUL_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow);
int ULA_DIV_PF(uint32_t * A, uint32_t * B, uint8_t * overflow, uint8_t * underflow);

#endif //ULA_PF_H
