#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_00037108 @ 0x00037108
 * public-name: handle_dashboard_action
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a8ff3                             @ 0x000a8ff3   [INLINED -- G6 literal batch]
 *   rodata_a95c9                             @ 0x000a95c9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_stocks_widget_index_raw                @ 0x2001b815
 */
/* Reconstructed handle_dashboard_action @ 0x37108  (parity: 300/300 trials, PROVEN) */

unsigned int handle_dashboard_action(unsigned int param_1, unsigned int param_2,
                                     unsigned int param_3, unsigned int param_4){
    unsigned int action = param_1 & 0xffu;
    *(volatile unsigned char*)(((unsigned long)&g_dashboard_widget_state) /*=0x20004950*/+3) = (unsigned char)action;
    *(volatile unsigned char*)((unsigned long)&g_stocks_widget_index_raw) /*=0x2001b815*/ = (unsigned char)action;
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2){
        if(*(volatile unsigned int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
            log_message(((unsigned long)"%s():  %s index = %d\n") /*=0xa8ff3*/, ((unsigned long)"setStocksIndex") /*=0xa95c9*/, ((unsigned long)"setStocksIndex") /*=0xa95c9*/,
                         action);
        } else {
            debug_print(((unsigned long)"%s():  %s index = %d\n") /*=0xa8ff3*/, ((unsigned long)"setStocksIndex") /*=0xa95c9*/, ((unsigned long)"setStocksIndex") /*=0xa95c9*/,
                         action);
        }
    }
    return 0;
}
