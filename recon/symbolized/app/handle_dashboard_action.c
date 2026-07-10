#include "g1_app_symbols.h"
/* named: handle_dashboard_action */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20004950  g_dashboard_widget_state     
//   0x20007554  g_log_use_alt_sink           
//   0x2001b815  g_stocks_widget_index_raw    
*/
/* Reconstructed handle_dashboard_action @ 0x37108  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int);
unsigned int handle_dashboard_action(unsigned char param_1,unsigned int param_2,unsigned int param_3,unsigned int param_4){
    *(volatile unsigned char*)(((uintptr_t)&g_dashboard_widget_state) /*=0x20004950*/+3) = param_1;
    *(volatile unsigned char*)((uintptr_t)&g_stocks_widget_index_raw) /*=0x2001b815*/ = param_1;
    if(*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2){
        if(*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0){
            DEBUG_PRINT("%s():  %s index = %d\n" /*=0xa8ff3*/, "setStocksIndex" /*=0xa95c9*/);
        } else {
            debug_print("%s():  %s index = %d\n" /*=0xa8ff3*/, "setStocksIndex" /*=0xa95c9*/);
        }
    }
    return 0;
}

