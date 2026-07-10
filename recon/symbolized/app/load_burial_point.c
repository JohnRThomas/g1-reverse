#include "g1_app_symbols.h"
/* named: load_burial_point */
/* globals referenced:
//   0x00135000  FLASH_ADDR_SETTINGS_RECORD   
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed load_burial_point @ 0x230e0  (parity: 300/300 trials, PROVEN) */

extern int flash_settings_read(unsigned int, void*, int, unsigned int, unsigned int);
extern unsigned int sys_rand32_get(void);
extern void memset_bytes(void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(void);

unsigned int load_burial_point(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    unsigned int uVar2;
    unsigned int uVar3;
    unsigned char *base = (unsigned char*)(param_1 + 0x1000);

    iVar1 = flash_settings_read(FLASH_ADDR_SETTINGS_RECORD /*=0x135000*/, (void*)(param_1 + 0x10c6), 0xc0, param_4, param_4);
    if (iVar1 == 0) {
        uVar3 = 0;
        if ((*(volatile short*)(base + 0xda) == -1) || (*(volatile char*)(base + 0xdc) == 0)) {
            uVar2 = sys_rand32_get();
            memset_bytes(base + 0xca, 0, 0xbc);
            *(volatile unsigned char*)(base + 0xda) = 7;
            *(volatile unsigned int*)(base + 0xc6) = uVar2;
            *(volatile unsigned char*)(base + 0xdc) = 1;
        }
    } else {
        if (1 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): burial_point read error!\n" /*=0x9e67c*/, "load_burial_point" /*=0x9e777*/);
            } else {
                debug_print();
            }
        }
        uVar3 = 0xffffffff;
    }
    return uVar3;
}

