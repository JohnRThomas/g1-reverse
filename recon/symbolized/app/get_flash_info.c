#include "g1_app_symbols.h"
/* named: get_flash_info */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed get_flash_info @ 0x32628  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int DEBUG_PRINT(int,...);
extern int get_device_info(void);
extern int debug_print(int,...);
extern int FUN_0007d120(int,int,int,int,void*);
extern int z_device_is_ready(int);
extern int memcpy(void*,int,int);

uint32_t get_flash_info(int param_1, uint32_t param_2, uint32_t *param_3, uint8_t *param_4){
    volatile uint8_t *puVar4;
    int iVar2;
    uint8_t uVar3;
    volatile uint8_t *puVar5 = (volatile uint8_t*)param_4;
    DEBUG_PRINT("join in get_flash_info\n" /*=0xa69f3*/);
    if (param_3==0 || param_4==0){ DEBUG_PRINT("get_flash_info para is NULL\n" /*=0xa6a0b*/); return 0xffffffff; }
    puVar4 = (volatile uint8_t*)*param_3;
    *puVar4 = 0x1e;
    uVar3 = *(volatile uint8_t*)(param_1+1);
    puVar4[2]=3; puVar4[1]=uVar3; puVar4[3]=4;
    iVar2 = z_device_is_ready(((uintptr_t)&tbl_87b30) /*=0x87bf0*/);
    if (iVar2==0){
        if (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/){
            uint32_t v = *(volatile uint32_t*)((uintptr_t)&tbl_87b30) /*=0x87bf0*/;
            int c = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
            if (c==0){ DEBUG_PRINT("%s():  [%s] device not ready.\n" /*=0xa40e6*/,"get_flash_info" /*=0xa76cb*/,v); }
            else { debug_print("%s():  [%s] device not ready.\n" /*=0xa40e6*/,"get_flash_info" /*=0xa76cb*/,v); }
        }
        *puVar4=0x1e; puVar4[1]=*(volatile uint8_t*)(param_1+1); puVar4[2]=3; uVar3=1; puVar4[3]=1;
        puVar4[4]=uVar3; uVar3=5;
    } else {
        iVar2 = get_device_info();
        if (*(volatile int*)(iVar2+0x1030) != 0){
            iVar2 = FUN_0007d120(((uintptr_t)&tbl_87b30) /*=0x87bf0*/, 0x002612d2, ((uintptr_t)&g_flash_info) /*=0x20019daf*/, 0x4e, (void*)puVar5);
            if (iVar2 != 0){
                DEBUG_PRINT("Flash read failed! %d\n" /*=0x9e2da*/, iVar2);
                *puVar4=0x1e; uVar3=*(volatile uint8_t*)(param_1+1); puVar4[2]=3; puVar4[1]=uVar3; puVar4[3]=1; uVar3=2;
                puVar4[4]=uVar3; uVar3=5;
                *(volatile uint8_t*)param_4=uVar3; return 0;
            }
            DEBUG_PRINT("flash read ok\n" /*=0xa6aab*/, 0);
        }
        memcpy((void*)(puVar4+4), ((uintptr_t)&g_flash_info) /*=0x20019daf*/, 0x4e);
        uVar3=0x52;
    }
    *(volatile uint8_t*)param_4=uVar3;
    return 0;
}

