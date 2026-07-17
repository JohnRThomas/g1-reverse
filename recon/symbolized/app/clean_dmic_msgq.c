#include "g1_app_symbols.h"
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
extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int);
int clean_dmic_msgq(void){
    int iVar1 = k_msgq_cleanup(((unsigned long)&g_dmic_msgq) /*=0x20007b7c*/);
    if(iVar1!=0 && *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 0){
        if(*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0){
            DEBUG_PRINT(((unsigned long)&rodata_a3efc) /*=0xa3efc*/,((unsigned long)&rodata_a41ef) /*=0xa41ef*/);
        } else {
            debug_print(((unsigned long)&rodata_a3efc) /*=0xa3efc*/,((unsigned long)&rodata_a41ef) /*=0xa41ef*/);
        }
    }
    return iVar1;
}
