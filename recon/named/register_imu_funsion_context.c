#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00026250 @ 0x00026250
 * public-name: register_imu_funsion_context
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   ADDR_imu_fusion_init_THUMB               @ 0x00025fad
 *   ADDR_imu_fusion_suspend_THUMB            @ 0x00025df9
 *   ADDR_imu_fusion_resume_THUMB             @ 0x00025dc5
 *   ADDR_set_imu_thread_delay_THUMB          @ 0x00025d8d
 *   rodata_9af2e                             @ 0x0009af2e   [INLINED -- G6 literal batch]
 *   rodata_9fb15                             @ 0x0009fb15   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed register_imu_funsion_context @ 0x26250  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);

unsigned int register_imu_funsion_context(unsigned char *param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    /* CODE-POINTER REBIND (iteration 13): the four stored words are Thumb entry
     * addresses of functions Ghidra never catalogued (gaps 0x25d8c..0x25ecc and
     * 0x25f90..0x26100).  They are now reconstructed and referenced by symbol,
     * which is also what pulls them into the link (main() reaches the +0x8c slot
     * only through this table, via `ldr r3,[r4,#0xf70] ; blx r3`). */
    *(unsigned int*)(param_1+0x8c) = ADDR_imu_fusion_init_THUMB /*=0x25fad*/;
    *(unsigned int*)(param_1+0x90) = ADDR_imu_fusion_suspend_THUMB /*=0x25df9*/;
    *(unsigned int*)(param_1+0x94) = ADDR_imu_fusion_resume_THUMB /*=0x25dc5*/;
    *(unsigned int*)(param_1+0x98) = ADDR_set_imu_thread_delay_THUMB /*=0x25d8d*/;
    if (*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
        unsigned int sink = *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if (sink == 0) {
            log_message(((unsigned long)"%s(): exit\n\n") /*=0x9af2e*/,((unsigned long)"register_imu_funsion_context") /*=0x9fb15*/,param_3,sink,param_4);
        } else {
            debug_print(((unsigned long)"%s(): exit\n\n") /*=0x9af2e*/,((unsigned long)"register_imu_funsion_context") /*=0x9fb15*/,param_3,sink,param_4);
        }
    }
    return 0;
}
