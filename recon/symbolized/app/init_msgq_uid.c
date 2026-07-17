#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00018e04 @ 0x00018e04
 * public-name: init_msgq_uid
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_impl_k_msgq_alloc_init                 <= FUN_00086448 @ 0x00086448
 * address symbols (name @ address):
 *   rodata_9a949                             @ 0x0009a949
 *   rodata_9b182                             @ 0x0009b182
 *   g_log_level                              @ 0x2000230c
 *   g_uid_pipe                               @ 0x20006a38
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed init_msgq_uid @ 0x18e04  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(unsigned int,int,int);
extern void log_message(unsigned int,unsigned int);
extern void debug_print(unsigned int,...);
int init_msgq_uid(void){
    int iVar1 = z_impl_k_msgq_alloc_init(((unsigned long)&g_uid_pipe) /*=0x20006a38*/,8,10);
    if(iVar1!=0 && *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>0){
        if(*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0){
            log_message(((unsigned long)&rodata_9a949) /*=0x9a949*/,((unsigned long)&rodata_9b182) /*=0x9b182*/);
        } else { debug_print(((unsigned long)&rodata_9a949) /*=0x9a949*/,((unsigned long)&rodata_9b182) /*=0x9b182*/); }
    }
    return iVar1;
}
