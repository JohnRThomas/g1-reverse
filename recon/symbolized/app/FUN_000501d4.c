#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000501d4 @ 0x000501d4
 * public-name: FUN_000501d4
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_000501d4 @ 0x501d4  (parity: 300/300 trials, PROVEN) */

int FUN_000501d4(int param_1)
{
    volatile int *base = (volatile int*)((unsigned long)&_kernel) /*=0x2000b448*/;
    int iVar4 = base[2];
    int uVar3 = *(volatile int*)0x00098654UL;
    *(volatile int*)(iVar4 + 0x8c) = param_1;
    *(volatile int*)(iVar4 + 0x90) = uVar3;
    volatile unsigned int *scb = (volatile unsigned int*)0xe000ed00UL;
    scb[1] = scb[1] | 0x10000000;
    __asm volatile ("movs r3, #0\n\tmsr basepri, r3\n\tisb sy\n\t" ::: "r3");
    return *(volatile int*)(base[2] + 0x90);
}
