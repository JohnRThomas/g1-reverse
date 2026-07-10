#include "g1_app_symbols.h"
/* named: get_timestamp */
/* Reconstructed get_timestamp @ 0x7d224  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_device_info(void);
unsigned int get_timestamp(void){
    unsigned int iVar1 = get_device_info();
    return *(unsigned int*)(iVar1 + 0xd0);
}

