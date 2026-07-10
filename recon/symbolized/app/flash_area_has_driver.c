#include "g1_app_symbols.h"
/* named: flash_area_has_driver */
/* Reconstructed flash_area_has_driver @ 0x83cb4  (parity: 300/300 trials, PROVEN) */

extern int z_device_is_ready(unsigned int);

unsigned int flash_area_has_driver(void *param_1)
{
    int iVar1;
    unsigned int uVar2;
    int *p = *(volatile int**)((char*)param_1 + 4);
    iVar1 = z_device_is_ready(*(volatile unsigned int*)((char*)p + 4));
    if (iVar1 == 0) {
        uVar2 = 0xffffffed;
    } else {
        uVar2 = 0;
    }
    return uVar2;
}

