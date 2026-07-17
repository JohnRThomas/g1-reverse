/* readable reconstruction; identity: FUN_0002ec1c @ 0x0002ec1c
 * public-name: clean_dmic_msgq
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_cleanup                           <= FUN_00086480 @ 0x00086480
 * address symbols (name @ address):
 *   rodata_a3efc                             @ 0x000a3efc
 *   rodata_a41ef                             @ 0x000a41ef
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dmic_msgq                              @ 0x20007b7c
 */
/* Reconstructed clean_dmic_msgq @ 0x2ec1c  (parity: 300/300 trials, PROVEN) */

extern int k_msgq_cleanup(unsigned int);
extern void log_message(unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int);
int clean_dmic_msgq(void){
    int iVar1 = k_msgq_cleanup(0x20007b7cUL);
    if(iVar1!=0 && *(volatile int*)0x2000230cUL > 0){
        if(*(volatile unsigned int*)0x20007554UL==0){
            log_message(0x000a3efcUL,0x000a41efUL);
        } else {
            debug_print(0x000a3efcUL,0x000a41efUL);
        }
    }
    return iVar1;
}
