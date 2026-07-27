#include "g1_app_symbols.h"
struct k_msgq;
#include <stddef.h>
#include "../../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_0002ebd8 @ 0x0002ebd8
 * public-name: init_dmic_msgq
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_impl_k_msgq_alloc_init                 <= FUN_00086448 @ 0x00086448
 * address symbols (name @ address):
 *   rodata_a3ee4                             @ 0x000a3ee4   [INLINED -- G6 literal batch]
 *   rodata_a41ff                             @ 0x000a41ff   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_dmic_msgq                              @ 0x20007b7c
 */
/* Reconstructed init_dmic_msgq @ 0x2ebd8  (parity: 300/300 trials, PROVEN) */

extern int z_impl_k_msgq_alloc_init(struct k_msgq *, size_t,  uint32_t);
int init_dmic_msgq(void){
    int iVar1 = z_impl_k_msgq_alloc_init(((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/,200,8);
    if(iVar1!=0 && *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>0){
        if(*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0){
            log_message(((unsigned long)"%s(): dmic init failed\n") /*=0xa3ee4*/,((unsigned long)"init_dmic_msgq") /*=0xa41ff*/);
        } else { debug_print(((unsigned long)"%s(): dmic init failed\n") /*=0xa3ee4*/,((unsigned long)"init_dmic_msgq") /*=0xa41ff*/); }
    }
    return iVar1;
}
