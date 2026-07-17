#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00049000 @ 0x00049000
 * public-name: setDelayExitValue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_efb0e                             @ 0x000efb0e
 *   rodata_f01c1                             @ 0x000f01c1
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_delayexitvalue                         @ 0x2000a094
 */
/* Reconstructed setDelayExitValue @ 0x49000  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int);
unsigned int setDelayExitValue(unsigned int param_1){
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2){
        if(*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0){
            DEBUG_PRINT(((unsigned long)&rodata_efb0e) /*=0xefb0e*/,((unsigned long)&rodata_f01c1) /*=0xf01c1*/,param_1);
        } else {
            debug_print(((unsigned long)&rodata_efb0e) /*=0xefb0e*/,((unsigned long)&rodata_f01c1) /*=0xf01c1*/,param_1);
        }
    }
    *(volatile unsigned int*)((unsigned long)&g_delayexitvalue) /*=0x2000a094*/ = param_1;
    return 0;
}
