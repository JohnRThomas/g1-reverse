#include "g1_app_symbols.h"
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00048998 @ 0x00048998
 * public-name: SendSystemLanguageInfoToSlave
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_ef596                             @ 0x000ef596
 *   rodata_ef59e                             @ 0x000ef59e   [INLINED -- G6 literal batch]
 *   rodata_ef6d4                             @ 0x000ef6d4   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_translate_lang_string_table            @ 0x200024f4
 *   g_dashboard_response_msgq                @ 0x2000392c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed SendSystemLanguageInfoToSlave @ 0x48998  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void memset_bytes(void*, int, int);
extern int k_msgq_put(unsigned int, void*, int, int);

u32 SendSystemLanguageInfoToSlave(int param_1)
{
    u8 local[28];
    int iVar1;
    u32 uVar4;

    memset_bytes(&local[1], 0, 0x17);
    local[0] = 5;
    local[4] = (u8)param_1;
    *(u16*)&local[2] = 1;
    iVar1 = k_msgq_put(((unsigned long)&g_dashboard_response_msgq) /*=0x2000392c*/, local, 0, 0);
    if (iVar1 == 0) {
        uVar4 = 0;
        if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
            u32 uVar3 = (u32)(param_1 - 1);
            u32 uVar2;
            if ((uVar3 & 0xff) < 0x11) {
                uVar2 = *(volatile u32*)(((unsigned long)&g_translate_lang_string_table) /*=0x200024f4*/ + (uVar3 & 0xff) * 4);
            } else {
                uVar2 = ((unsigned long)&rodata_ef596) /*=0xef596*/;
            }
            if (*(volatile u32*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): send APP Language infomation to slave . app language = %s\n") /*=0xef59e*/, ((unsigned long)"SendSystemLanguageInfoToSlave") /*=0xef6d4*/, uVar2);
            } else {
                debug_print(((unsigned long)"%s(): send APP Language infomation to slave . app language = %s\n") /*=0xef59e*/, ((unsigned long)"SendSystemLanguageInfoToSlave") /*=0xef6d4*/, uVar2);
            }
        }
    } else {
        log_message(((unsigned long)"message queue send failed %s\r\n") /*=0xef058*/, ((unsigned long)"SendSystemLanguageInfoToSlave") /*=0xef6d4*/);
        uVar4 = 0xffffffffU;
    }
    return uVar4;
}
