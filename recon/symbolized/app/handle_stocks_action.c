#include "g1_app_symbols.h"
/* named: handle_stocks_action */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20004950  g_dashboard_widget_state     
//   0x20007554  g_log_use_alt_sink           
//   0x2001b814  g_news_widget_index_raw      
*/
/* Reconstructed handle_stocks_action @ 0x371e8  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(void);
extern void debug_print(void);

unsigned int handle_stocks_action(unsigned char param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    *(volatile unsigned char*)(((uintptr_t)&g_dashboard_widget_state) /*=0x20004950*/+5) = param_1;
    *(volatile unsigned char*)((uintptr_t)&g_news_widget_index_raw) /*=0x2001b814*/ = param_1;
    if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT();
        } else {
            debug_print();
        }
    }
    return 0;
}

