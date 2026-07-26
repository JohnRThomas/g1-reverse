#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032784 @ 0x00032784
 * public-name: get_glassbox_charge_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a7411                             @ 0x000a7411   [INLINED -- G6 literal batch]
 *   rodata_a7751                             @ 0x000a7751   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_glassbox_charge_status_byte            @ 0x20019ef4
 */
/* Reconstructed get_glassbox_charge_status @ 0x32784  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int);
unsigned char get_glassbox_charge_status(void){
    volatile unsigned char *pbVar1 = (volatile unsigned char*)((unsigned long)&g_glassbox_charge_status_byte) /*=0x20019ef4*/;
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2){
        unsigned int sink = *(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
        if(sink == 0){
            log_message(((unsigned long)"%s(): bIsCharging is :%d \n\n") /*=0xa7411*/, ((unsigned long)"get_glassbox_charge_status") /*=0xa7751*/,
                        (unsigned int)(*pbVar1 >> 7),sink);
        } else {
            debug_print(((unsigned long)"%s(): bIsCharging is :%d \n\n") /*=0xa7411*/, ((unsigned long)"get_glassbox_charge_status") /*=0xa7751*/,
                         (unsigned int)(*pbVar1 >> 7),sink);
        }
    }
    return *pbVar1 >> 7;
}
