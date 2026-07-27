/* readable reconstruction; identity: FUN_000342e0 @ 0x000342e0
 * public-name: pull_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a804b                             @ 0x000a804b   [INLINED -- G6 literal batch]
 *   rodata_a806c                             @ 0x000a806c   [INLINED -- G6 literal batch]
 *   rodata_a80bc                             @ 0x000a80bc   [INLINED -- G6 literal batch]
 *   rodata_a8221                             @ 0x000a8221   [INLINED -- G6 literal batch]
 *   rodata_a822e                             @ 0x000a822e   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pool_index                     @ 0x2001a22a
 */
#include "../headers/g1_log.h"
/* Reconstructed pull_message @ 0x342e0  (parity: 300/300 trials, PROVEN) */

extern unsigned int get_device_info(void);

unsigned char pull_message(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int iVar3;

    if (param_1 == (int *)0) {
        if (0 < *(int *)0x2000230cUL) {
            if (*(int *)0x20007554UL == 0) {
                log_message(0xa804bU, 0xa822eU, 0xa8221U, 0x3bdU, param_4);
            } else {
                debug_print(0xa804bU, 0xa822eU, 0xa8221U, 0x3bdU, param_4);
            }
        }
    } else {
        iVar3 = get_device_info();
        if (*(unsigned char *)(iVar3 + 0xdd) <= 0xa) {
            *param_1 = (unsigned int)(*(unsigned char *)0x2001a22aUL) * 0x1b4 + 0x20007dacU;
            if (*(int *)0x20007554UL == 0) {
                log_message(0xa80bcU);
            } else {
                debug_print(0xa80bcU);
            }
            return *(unsigned char *)0x2001a22aUL;
        }
        if (*(int *)0x20007554UL == 0) {
            iVar3 = get_device_info();
            log_message(0xa806cU, (unsigned int)*(unsigned char *)(iVar3 + 0xdd));
        } else {
            iVar3 = get_device_info();
            debug_print(0xa806cU, *(unsigned char *)(iVar3 + 0xdd));
        }
    }
    return 10;
}
