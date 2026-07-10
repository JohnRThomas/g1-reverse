#include "g1_app_symbols.h"
/* named: check_device_readiness */
/* Reconstructed check_device_readiness @ 0x167b4  (parity: 300/300 trials, PROVEN) */

extern int z_device_is_ready(unsigned int);
extern void DEBUG_PRINT(unsigned int, ...);
unsigned int check_device_readiness(void){
    unsigned int *puVar1 = (unsigned int*)((uintptr_t)&tbl_87b30) /*=0x87bf0*/;
    int iVar2 = z_device_is_ready((unsigned int)puVar1);
    unsigned int uVar3;
    if(iVar2==0){
        DEBUG_PRINT(" [%s] device not ready.\n" /*=0xa40ec*/, puVar1[0]);
        uVar3 = 0xffffffffU;
    } else {
        void (*fn)(unsigned int,unsigned int,unsigned int) = (void*)(*(unsigned int*)(puVar1[2] + 8));
        fn((unsigned int)puVar1, 0, FLASH_OFF_130000 /*=0x130000*/);
        DEBUG_PRINT("erase_dfu_flash done.\n" /*=0x99726*/);
        uVar3 = 0;
    }
    return uVar3;
}

