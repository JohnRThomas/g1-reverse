#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003444c @ 0x0003444c
 * public-name: is_msg_expiration
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   get_timestamp                            <= FUN_0007d224 @ 0x0007d224
 *   set_device_sync_timestamp                <= FUN_0007d230 @ 0x0007d230
 * address symbols (name @ address):
 *   rodata_a80e3                             @ 0x000a80e3   [INLINED -- G6 literal batch]
 *   rodata_a8146                             @ 0x000a8146   [INLINED -- G6 literal batch]
 *   rodata_a820f                             @ 0x000a820f   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pool_index                     @ 0x2001a22a
 */
/* Reconstructed is_msg_expiration @ 0x3444c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
extern void *get_device_info(void);
extern unsigned int get_timestamp(void);
extern void set_device_sync_timestamp(unsigned int);

unsigned int is_msg_expiration(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned char *pbVar1;
    int iVar2;
    char *pcVar3;
    unsigned int uVar4;
    int iVar5;
    unsigned int uVar6;
    unsigned int uVar7;
    unsigned int uVar8;

    iVar2 = (int)(intptr_t)get_device_info();
    if (*(char*)(intptr_t)(iVar2 + 0x108f) != 0) {
        pcVar3 = (char*)get_device_info();
        if (*pcVar3 == 1) {
            iVar2 = (int)(intptr_t)get_device_info();
            set_device_sync_timestamp(**(unsigned int**)(intptr_t)(iVar2 + 0xfec));
        }
    }
    iVar2 = ((unsigned long)g_message_pool) /*=0x20007dac*/;
    pbVar1 = (unsigned char*)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/;
    iVar5 = (int)(*pbVar1) * 0x1b4 + iVar2;
    uVar6 = (unsigned int)*(unsigned char*)(intptr_t)(iVar5 + 0xf);
    if ((uVar6 != 0) && ((uVar6 = *(unsigned int*)(intptr_t)(iVar5 + 4)) != 0)) {
        uVar6 = get_timestamp();
        uVar7 = (unsigned int)*pbVar1;
        iVar5 = *(int*)(intptr_t)(uVar7 * 0x1b4 + iVar2 + 4);
        if (iVar5 + 10U < uVar6) {
            if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
                if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    uVar4 = get_timestamp();
                    log_message(((unsigned long)"%s(): [csh_debug_msg]the msg has expirtion,g_curShowMsgIdx is %u, startShowTime is %u, now is %d\n\n") /*=0xa80e3*/, ((unsigned long)"is_msg_expiration") /*=0xa820f*/, uVar7, iVar5, uVar4, param_2, param_3);
                } else {
                    uVar4 = get_timestamp();
                    debug_print(((unsigned long)"%s(): [csh_debug_msg]the msg has expirtion,g_curShowMsgIdx is %u, startShowTime is %u, now is %d\n\n") /*=0xa80e3*/, ((unsigned long)"is_msg_expiration") /*=0xa820f*/, uVar7, iVar5, uVar4, param_2, param_3);
                }
            }
            uVar6 = 2;
        } else {
            uVar6 = 1;
        }
    }
    uVar8 = *(unsigned int*)(intptr_t)((unsigned int)*pbVar1 * 0x1b4 + iVar2 + 4);
    uVar7 = get_timestamp();
    if (uVar7 < uVar8) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"error startShowTime, greate than now time ! \n") /*=0xa8146*/);
        } else {
            debug_print(((unsigned long)"error startShowTime, greate than now time ! \n") /*=0xa8146*/);
        }
        uVar6 = 2;
    }
    return uVar6;
}
