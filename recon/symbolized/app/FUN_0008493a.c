#include "g1_app_symbols.h"
/* named: FUN_0008493a */
/* Reconstructed FUN_0008493a @ 0x8493a  (parity: 300/300 trials, PROVEN) */

int FUN_0008493a(int param_1, unsigned char *param_2)
{
    unsigned int *p10 = *(unsigned int* volatile*)(param_1 + 0x10);
    unsigned int *p4  = *(unsigned int* volatile*)(param_1 + 4);
    unsigned int cond = *(volatile unsigned int*)((char*)p10 + 0xc);
    unsigned int puVar2_int = *(volatile unsigned int*)p4;
    unsigned int *puVar2 = (unsigned int*)puVar2_int;
    if (cond != 0) {
        return (int)0xffffff7a;
    }
    unsigned int v44 = *(volatile unsigned int*)((char*)puVar2 + 0x110);
    if (v44 == 0) {
        return -1;
    }
    unsigned char *p18 = *(unsigned char* volatile*)((char*)p10 + 0x18);
    *param_2 = *(volatile unsigned char*)p18;
    *(volatile unsigned int*)((char*)puVar2 + 0x110) = 0;
    *(volatile unsigned int*)puVar2 = 1;
    return 0;
}

