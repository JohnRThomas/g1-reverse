#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00033b0c @ 0x00033b0c
 * public-name: msg_queue_debug_dump
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   msg_queue_debug_dump                     <= FUN_00033b0c @ 0x00033b0c
 * address symbols (name @ address):
 *   rodata_a7d1c                             @ 0x000a7d1c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_message_pool                           @ 0x20007dac
 */
/* Reconstructed FUN_00033b0c @ 0x33b0c  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int, int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern void debug_print(unsigned int, ...);

void msg_queue_debug_dump(unsigned int param_1, unsigned int param_2, unsigned int param_3)
{
    unsigned int format_string = ((unsigned long)&rodata_a7d1c) /*=0xa7d1c*/;
    volatile int *piVar1 = (volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    volatile unsigned int *puVar3 = (volatile unsigned int*)((unsigned long)g_message_pool) /*=0x20007dac*/;
    int iVar2 = 0;
    do {
        unsigned int value0 = puVar3[0];
        unsigned int buffered = *piVar1;
        unsigned int value1 = puVar3[1];
        unsigned int value2 = puVar3[2];
        if (buffered == 0) {
            DEBUG_PRINT(format_string, iVar2, value2, value1, value0, param_2, param_3);
        } else {
            debug_print(format_string, iVar2, value2, value1,
                         value0, param_2, param_3);
        }
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 0x6d;
    } while (iVar2 != 10);
}
