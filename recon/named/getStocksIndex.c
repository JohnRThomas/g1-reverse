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
    volatile unsigned char *base = (volatile unsigned char*)0x20004950UL;
    int iVar2 = *(volatile int*)0x2000230cUL;
    unsigned char b = *(volatile unsigned char*)0x2001b815UL;
    base[3] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x000a8ff3UL, 0x000a95d8UL);
        } else {
            debug_print(0x000a8ff3UL, 0x000a95d8UL);
        }
    }
    return base[3];
}

