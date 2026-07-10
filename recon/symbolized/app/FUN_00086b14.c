#include "g1_app_symbols.h"
/* named: FUN_00086b14 */
/* Reconstructed FUN_00086b14 @ 0x86b14  (parity: 300/300 trials, PROVEN) */

extern unsigned int* _malloc_r(unsigned int, int);
extern void memset_bytes(unsigned int*, int, int);

unsigned int* FUN_00086b14(unsigned int param_1, int param_2)
{
    unsigned int *puVar1;
    int iVar2;
    iVar2 = (param_2 - 1) * 0x68;
    puVar1 = _malloc_r(param_1, iVar2 + 0x74);
    if (puVar1 != (unsigned int*)0) {
        puVar1[0] = 0;
        puVar1[1] = (unsigned int)param_2;
        puVar1[2] = (unsigned int)(puVar1 + 3);
        memset_bytes(puVar1 + 3, 0, iVar2 + 0x68);
    }
    return puVar1;
}

