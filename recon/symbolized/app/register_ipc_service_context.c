#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00025d40 @ 0x00025d40
 * public-name: register_ipc_service_context
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_25ae9                             @ 0x00025ae9
 *   ADDR_global_ipc_service_send_THUMB       @ 0x00025b79
 *   rodata_9af2e                             @ 0x0009af2e   [INLINED -- G6 literal batch]
 *   rodata_9f6c6                             @ 0x0009f6c6   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ipc0_endpoint                          @ 0x20007a84
 */
/* Reconstructed register_ipc_service_context @ 0x25d40  (parity: 300/300 trials, PROVEN) */

unsigned int register_ipc_service_context(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    *(unsigned int*)(param_1+0x60) = ADDR_global_ipc_service_send_THUMB /*=0x25b79*/;
    /* iteration 4: was ((unsigned long)&rodata_25ae9), the pinned 0x25ae9 --
     * an unrelocated original-image code pointer.  0x25ae8 is the IPC-service
     * registrar, now reconstructed as register_ipc_service_recv_callback and
     * bound through the pointer_rebind.md __asm__-alias so the reference is a
     * real R_ARM_ABS32 (gc-retention is relocation-backed, like the sibling
     * slot above). */
    *(unsigned int*)(param_1+0x64) = ADDR_register_ipc_service_recv_callback_THUMB /*=0x25ae9*/;
    *(volatile unsigned int*)((unsigned long)&g_ipc0_endpoint) /*=0x20007a84*/ = (unsigned int)param_1;
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1){
        unsigned int sink=*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if(sink==0){
            log_message(((unsigned long)"%s(): exit\n\n") /*=0x9af2e*/,((unsigned long)"register_ipc_service_context") /*=0x9f6c6*/,param_3,sink,param_4);
        } else {
            debug_print(((unsigned long)"%s(): exit\n\n") /*=0x9af2e*/,((unsigned long)"register_ipc_service_context") /*=0x9f6c6*/,param_3,sink,param_4);
        }
    }
    return 0;
}
