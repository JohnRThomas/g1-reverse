/* readable reconstruction; identity: FUN_00049000 @ 0x00049000
 * public-name: setDelayExitValue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_efb0e                             @ 0x000efb0e   [INLINED -- G6 literal batch]
 *   rodata_f01c1                             @ 0x000f01c1   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_delayexitvalue                         @ 0x2000a094
 */
#include "../headers/g1_log.h"
/* Reconstructed setDelayExitValue @ 0x49000  (parity: 300/300 trials, PROVEN) */

unsigned int setDelayExitValue(unsigned int param_1){
    if(*(volatile int*)0x2000230cUL > 2){
        if(*(volatile unsigned int*)0x20007554UL==0){
            log_message(0x000efb0eUL,0x000f01c1UL,param_1);
        } else {
            debug_print(0x000efb0eUL,0x000f01c1UL,param_1);
        }
    }
    *(volatile unsigned int*)0x2000a094UL = param_1;
    return 0;
}
