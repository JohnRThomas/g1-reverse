/* readable reconstruction; identity: FUN_00018b6c @ 0x00018b6c
 * public-name: init_msgq_ancs
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_impl_k_msgq_alloc_init                 <= FUN_00086448 @ 0x00086448
 * address symbols (name @ address):
 *   rodata_9a949                             @ 0x0009a949
 *   rodata_9b1aa                             @ 0x0009b1aa
 *   g_log_level                              @ 0x2000230c
 *   g_ancs_msgq                              @ 0x20006a6c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed init_msgq_ancs @ 0x18b6c  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void log_message(unsigned int,unsigned int);
extern void debug_print(unsigned int,...);
int init_msgq_ancs(void){
    int iVar1 = z_impl_k_msgq_alloc_init(0x20006a6cUL,0x1b4,10);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL>0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            log_message(0x0009a949UL,0x0009b1aaUL);
        } else { debug_print(0x0009a949UL,0x0009b1aaUL); }
    }
    return iVar1;
}
