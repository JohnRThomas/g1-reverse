/* readable reconstruction; identity: FUN_0002ebd8 @ 0x0002ebd8
 * public-name: init_dmic_msgq
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_impl_k_msgq_alloc_init                 <= FUN_00086448 @ 0x00086448
 * address symbols (name @ address):
 *   rodata_a3ee4                             @ 0x000a3ee4
 *   rodata_a41ff                             @ 0x000a41ff
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dmic_msgq                              @ 0x20007b7c
 */
/* Reconstructed init_dmic_msgq @ 0x2ebd8  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void log_message(unsigned int,unsigned int);
extern void debug_print(unsigned int,...);
int init_dmic_msgq(void){
    int iVar1 = z_impl_k_msgq_alloc_init(0x20007b7cUL,200,8);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL>0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            log_message(0x000a3ee4UL,0x000a41ffUL);
        } else { debug_print(0x000a3ee4UL,0x000a41ffUL); }
    }
    return iVar1;
}
