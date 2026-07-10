#include "g1_app_symbols.h"
/* named: getStocksIndex */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20004950  g_dashboard_widget_state     
//   0x20007554  g_log_use_alt_sink           
//   0x2001b815  g_stocks_widget_index_raw    
*/
/* Reconstructed getStocksIndex @ 0x370bc  (parity: 300/300 trials, PROVEN) */

extern void DEBUG_PRINT(unsigned int a, unsigned int b);
extern void debug_print(unsigned int a, unsigned int b);

unsigned char getStocksIndex(void)
{
    volatile unsigned char *base = (volatile unsigned char*)((uintptr_t)&g_dashboard_widget_state) /*=0x20004950*/;
    int iVar2 = *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    unsigned char b = *(volatile unsigned char*)((uintptr_t)&g_stocks_widget_index_raw) /*=0x2001b815*/;
    base[3] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s():  %s index = %d\n" /*=0xa8ff3*/, "getStocksIndex" /*=0xa95d8*/);
        } else {
            debug_print("%s():  %s index = %d\n" /*=0xa8ff3*/, "getStocksIndex" /*=0xa95d8*/);
        }
    }
    return base[3];
}

