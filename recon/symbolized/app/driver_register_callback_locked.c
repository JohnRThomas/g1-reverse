#include "g1_app_symbols.h"
/* named: driver_register_callback_locked */
/* Reconstructed driver_register_callback_locked @ 0x848d2  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
uint32_t driver_register_callback_locked(int *param_1, uint32_t param_2, uint32_t param_3){
    int iVar4 = **(volatile int* volatile*)((char*)param_1 + 4);
    int iVar6 = *(volatile int*)((char*)param_1 + 0x10);
    uint32_t uVar3;
    int iVar5 = *(volatile int*)(iVar6 + 0xc);
    if(*(volatile int*)(iVar5 + 0x58) == 0){
        uVar3 = 0xfffffff3;
    } else if(*(volatile int*)(iVar5 + 0x64) == 0){
        *(volatile int*)(iVar5 + 0x64) = (int)param_2;
        *(volatile int*)(*(volatile int*)(iVar6+0xc) + 0x68) = (int)param_3;
        *(volatile int*)(iVar4 + 0x534) = (int)param_2;
        *(volatile int*)(iVar4 + 0x538) = (int)param_3;
        *(volatile uint32_t*)(iVar4 + 0x200) |= 0x20;
        uVar3 = 0;
    } else {
        uVar3 = 0xfffffff0;
    }
    return uVar3;
}

