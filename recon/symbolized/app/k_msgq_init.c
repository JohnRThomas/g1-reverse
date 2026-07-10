#include "g1_app_symbols.h"
/* named: k_msgq_init */
/* Reconstructed k_msgq_init @ 0x86420  (parity: 300/300 trials, PROVEN) */

void k_msgq_init(char *param_1, int param_2, int param_3, int param_4)
{
    *(volatile int*)(param_1 + 0xc) = param_3;
    *(volatile int*)(param_1 + 0x10) = param_4;
    *(volatile int*)(param_1 + 0x24) = 0;
    *(volatile unsigned char*)(param_1 + 0x30) = 0;
    *(volatile int*)(param_1 + 8) = 0;
    *(volatile int*)(param_1 + 0x18) = param_4 * param_3 + param_2;
    *(volatile int*)(param_1 + 0x1c) = param_2;
    *(volatile long*)param_1 = (long)param_1;
    *(volatile long*)(param_1 + 4) = (long)param_1;
    *(volatile long*)(param_1 + 0x28) = (long)(param_1 + 0x28);
    *(volatile long*)(param_1 + 0x2c) = (long)(param_1 + 0x28);
    *(volatile int*)(param_1 + 0x14) = param_2;
    *(volatile int*)(param_1 + 0x20) = param_2;
}

