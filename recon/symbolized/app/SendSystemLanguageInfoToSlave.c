#include "g1_app_symbols.h"
/* named: SendSystemLanguageInfoToSlave */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x2000392c  g_dashboard_response_msgq    
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed SendSystemLanguageInfoToSlave @ 0x48998  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int);

u32 SendSystemLanguageInfoToSlave(int param_1)
{
    u8 local[28];
    int iVar1;
    u32 uVar4;

    memset_bytes(&local[1], 0, 0x17);
    local[0] = 5;
    local[4] = (u8)param_1;
    *(u16*)&local[2] = 1;
    iVar1 = k_msgq_put(((uintptr_t)&g_dashboard_response_msgq) /*=0x2000392c*/, local, 0, 0);
    if (iVar1 == 0) {
        uVar4 = 0;
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
            u32 uVar3 = (u32)(param_1 - 1);
            u32 uVar2;
            if ((uVar3 & 0xff) < 0x11) {
                uVar2 = *(volatile u32*)(((uintptr_t)&g_translate_lang_string_table) /*=0x200024f4*/ + (uVar3 & 0xff) * 4);
            } else {
                uVar2 = "unknown" /*=0xef596*/;
            }
            if (*(volatile u32*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): send APP Language infomation to slave . app language = %s\n" /*=0xef59e*/, "SendSystemLanguageInfoToSlave" /*=0xef6d4*/, uVar2);
            } else {
                debug_print("%s(): send APP Language infomation to slave . app language = %s\n" /*=0xef59e*/, "SendSystemLanguageInfoToSlave" /*=0xef6d4*/, uVar2);
            }
        }
    } else {
        DEBUG_PRINT("message queue send failed %s\r\n" /*=0xef058*/, "SendSystemLanguageInfoToSlave" /*=0xef6d4*/);
        uVar4 = 0xffffffffU;
    }
    return uVar4;
}

