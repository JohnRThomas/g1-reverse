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

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int,unsigned int);
unsigned int register_ipc_service_context(int param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    *(unsigned int*)(param_1+0x60) = 0x00025b79UL;
    *(unsigned int*)(param_1+0x64) = 0x00025ae9UL;
    *(volatile unsigned int*)0x20007a84UL = (unsigned int)param_1;
    if(*(volatile int*)0x2000230cUL > 1){
        unsigned int sink=*(volatile unsigned int*)0x20007554UL;
        if(sink==0){
            log_message(((unsigned long)"%s(): exit\n\n"),0x0009f6c6UL,param_3,sink,param_4);
        } else {
            debug_print(((unsigned long)"%s(): exit\n\n"),0x0009f6c6UL,param_3,sink,param_4);
        }
    }
    return 0;
}
