#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000342e0 @ 0x000342e0
 * public-name: pull_message
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a804b                             @ 0x000a804b
 *   rodata_a806c                             @ 0x000a806c
 *   rodata_a80bc                             @ 0x000a80bc
 *   rodata_a8221                             @ 0x000a8221
 *   rodata_a822e                             @ 0x000a822e
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 *   g_message_pool_index                     @ 0x2001a22a
 */
/* Reconstructed pull_message @ 0x342e0  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,...);
extern void debug_print(unsigned int,...);
extern unsigned int get_device_info(void);

unsigned char pull_message(int *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int iVar3;

    if (param_1 == (int *)0) {
        if (0 < *(int *)((unsigned long)&g_log_level) /*=0x2000230c*/) {
            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT(((unsigned long)&rodata_a804b) /*=0xa804b*/, ((unsigned long)&rodata_a822e) /*=0xa822e*/, ((unsigned long)&rodata_a8221) /*=0xa8221*/, 0x3bdU, param_4);
            } else {
                debug_print(((unsigned long)&rodata_a804b) /*=0xa804b*/, ((unsigned long)&rodata_a822e) /*=0xa822e*/, ((unsigned long)&rodata_a8221) /*=0xa8221*/, 0x3bdU);
            }
        }
    } else {
        iVar3 = get_device_info();
        if (*(unsigned char *)(iVar3 + 0xdd) <= 0xa) {
            *param_1 = (unsigned int)(*(unsigned char *)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/) * 0x1b4 + ((unsigned long)g_message_pool) /*=0x20007dac*/;
            if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT(((unsigned long)&rodata_a80bc) /*=0xa80bc*/);
            } else {
                debug_print(((unsigned long)&rodata_a80bc) /*=0xa80bc*/);
            }
            return *(unsigned char *)((unsigned long)&g_message_pool_index) /*=0x2001a22a*/;
        }
        if (*(int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            iVar3 = get_device_info();
            DEBUG_PRINT(((unsigned long)&rodata_a806c) /*=0xa806c*/, (unsigned int)*(unsigned char *)(iVar3 + 0xdd));
        } else {
            iVar3 = get_device_info();
            debug_print(((unsigned long)&rodata_a806c) /*=0xa806c*/, *(unsigned char *)(iVar3 + 0xdd));
        }
    }
    return 10;
}
