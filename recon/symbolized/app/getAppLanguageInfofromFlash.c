#include "g1_app_symbols.h"
/* named: getAppLanguageInfofromFlash */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
//   0x20018462  g_ui_mode_flag               
*/
/* Reconstructed getAppLanguageInfofromFlash @ 0x23d0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern int z_device_is_ready(uint32_t);

unsigned char getAppLanguageInfofromFlash(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    volatile int *piVar1;
    volatile unsigned int *puVar2;
    int iVar3;
    unsigned int uVar4;
    int iVar5;
    unsigned char uVar6;
    int iVar7;

    piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    unsigned int local_14 = param_2;

    if (2 < *piVar1) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): read setting flash data to ram...\r\n\n" /*=0x9e9bf*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, param_3, 0, param_1);
        } else {
            debug_print("%s(): read setting flash data to ram...\r\n\n" /*=0x9e9bf*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, param_3, 0, param_1);
        }
    }
    puVar2 = (volatile unsigned int*)((uintptr_t)&tbl_87b30) /*=0x87bf0*/;
    iVar3 = z_device_is_ready(((uintptr_t)&tbl_87b30) /*=0x87bf0*/);
    if (iVar3 == 0) {
        if (0 < *piVar1) {
            if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s():  [%s] device not ready.\n\n" /*=0x9e9ea*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, *puVar2, 0, param_1);
            } else {
                debug_print("%s():  [%s] device not ready.\n\n" /*=0x9e9ea*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, *puVar2, 0, param_1);
            }
        }
        uVar6 = 0xff;
    } else {
        local_14 = local_14 & 0xff000000UL;
        char *p1 = (char*)get_device_info();
        void *pcVar8 = *(void**)(p1 + 0x1030);
        void *r1arg = get_device_info();
        int (*fn)(void*, unsigned int, void*, int) = (int(*)(void*, unsigned int, void*, int))pcVar8;
        iVar5 = fn(r1arg, FLASH_OFF_13e000 /*=0x13e000*/, &local_14, 3);
        iVar3 = ((uintptr_t)&g_ui_mode_flag) /*=0x20018462*/;
        iVar7 = *piVar1;
        if (iVar5 == 0) {
            if ((char)local_14 == -0x56) {
                uVar6 = (unsigned char)(local_14 >> 8);
            } else {
                uVar6 = 2;
            }
            *(unsigned char*)(intptr_t)(((uintptr_t)&g_ui_mode_flag) /*=0x20018462*/ + 1) = uVar6;
            if (3 < iVar7) {
                if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s(): system language type = %d\n" /*=0x9ea37*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, (unsigned int)*(unsigned char*)(intptr_t)(iVar3 + 1));
                } else {
                    debug_print("%s(): system language type = %d\n" /*=0x9ea37*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, (unsigned int)*(unsigned char*)(intptr_t)(iVar3 + 1));
                }
            }
            uVar6 = *(unsigned char*)(intptr_t)(iVar3 + 1);
        } else {
            if (0 < iVar7) {
                if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s():  form address [%d] read data failed.\n\n" /*=0x9ea0a*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, FLASH_OFF_13e000 /*=0x13e000*/);
                } else {
                    debug_print("%s():  form address [%d] read data failed.\n\n" /*=0x9ea0a*/, "getAppLanguageInfofromFlash" /*=0x9ed2e*/, FLASH_OFF_13e000 /*=0x13e000*/);
                }
            }
            uVar6 = 0;
        }
    }
    return uVar6;
}

