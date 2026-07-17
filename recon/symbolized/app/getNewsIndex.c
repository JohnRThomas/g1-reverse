#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0003719c @ 0x0003719c
 * public-name: getNewsIndex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a8ff3                             @ 0x000a8ff3
 *   rodata_a95ab                             @ 0x000a95ab
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_news_widget_index_raw                  @ 0x2001b814
 */
/* Reconstructed getNewsIndex @ 0x3719c  (parity: 300/300 trials, PROVEN) */

extern void log_message(unsigned int,unsigned int,unsigned int,unsigned int);
extern void debug_print(unsigned int,unsigned int,unsigned int,unsigned int);

unsigned char getNewsIndex(void)
{
    volatile unsigned char *base = (volatile unsigned char*)((unsigned long)&g_dashboard_widget_state) /*=0x20004950*/;
    int iVar2 = *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
    unsigned char b = *(volatile unsigned char*)((unsigned long)&g_news_widget_index_raw) /*=0x2001b814*/;
    base[5] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)&rodata_a8ff3) /*=0xa8ff3*/, ((unsigned long)&rodata_a95ab) /*=0xa95ab*/, ((unsigned long)&rodata_a95ab) /*=0xa95ab*/, b);
        } else {
            debug_print(((unsigned long)&rodata_a8ff3) /*=0xa8ff3*/, ((unsigned long)&rodata_a95ab) /*=0xa95ab*/, ((unsigned long)&rodata_a95ab) /*=0xa95ab*/, b);
        }
    }
    return base[5];
}
