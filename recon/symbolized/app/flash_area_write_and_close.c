#include "g1_app_symbols.h"
/* named: flash_area_write_and_close */
/* Reconstructed flash_area_write_and_close @ 0x84e72  (parity: 300/300 trials, PROVEN) */

extern int flash_area_open(unsigned int a, void *b, unsigned int c, unsigned int d, unsigned int e);
extern unsigned int FUN_0006403c(unsigned int a, unsigned int b);
extern void nullsub_3(unsigned int a);

unsigned int flash_area_write_and_close(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int local_c;
    local_c = param_2;
    iVar1 = flash_area_open(param_1 & 0xff, &local_c, param_3, param_4, param_1);
    if (iVar1 == 0) {
        uVar2 = FUN_0006403c(local_c, param_2);
        nullsub_3(local_c);
    } else {
        uVar2 = 1;
    }
    return uVar2;
}

