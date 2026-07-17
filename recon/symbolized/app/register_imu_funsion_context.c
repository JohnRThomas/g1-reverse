#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026250 @ 0x00026250
 * public-name: register_imu_funsion_context
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_25d8d                             @ 0x00025d8d
 *   rodata_25dc5                             @ 0x00025dc5
 *   rodata_25df9                             @ 0x00025df9
 *   rodata_25fad                             @ 0x00025fad
 *   rodata_9af2e                             @ 0x0009af2e
 *   rodata_9fb15                             @ 0x0009fb15
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed register_imu_funsion_context @ 0x26250  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);

unsigned int register_imu_funsion_context(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    *(unsigned int*)(param_1+0x8c) = ((unsigned long)&rodata_25fad) /*=0x25fad*/;
    *(unsigned int*)(param_1+0x90) = ((unsigned long)&rodata_25df9) /*=0x25df9*/;
    *(unsigned int*)(param_1+0x94) = ((unsigned long)&rodata_25dc5) /*=0x25dc5*/;
    *(unsigned int*)(param_1+0x98) = ((unsigned long)&rodata_25d8d) /*=0x25d8d*/;
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
        unsigned int sink = *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if (sink == 0) {
            log_message(((unsigned long)&rodata_9af2e) /*=0x9af2e*/,((unsigned long)&rodata_9fb15) /*=0x9fb15*/,param_3,sink,param_4);
        } else {
            debug_print(((unsigned long)&rodata_9af2e) /*=0x9af2e*/,((unsigned long)&rodata_9fb15) /*=0x9fb15*/,param_3,sink,param_4);
        }
    }
    return 0;
}
