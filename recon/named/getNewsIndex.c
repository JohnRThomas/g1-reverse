/* readable reconstruction; identity: FUN_0003719c @ 0x0003719c
 * public-name: getNewsIndex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 * address symbols (name @ address):
 *   rodata_a8ff3                             @ 0x000a8ff3   [INLINED -- G6 literal batch]
 *   rodata_a95ab                             @ 0x000a95ab   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_dashboard_widget_state                 @ 0x20004950
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_news_widget_index_raw                  @ 0x2001b814
 */
#include "../headers/g1_log.h"
/* Reconstructed getNewsIndex @ 0x3719c  (parity: 300/300 trials, PROVEN) */


unsigned char getNewsIndex(void)
{
    volatile unsigned char *base = (volatile unsigned char*)0x20004950UL;
    int iVar2 = *(volatile int*)0x2000230cUL;
    unsigned char b = *(volatile unsigned char*)0x2001b814UL;
    base[5] = b;
    if (iVar2 > 2) {
        if (*(volatile int*)0x20007554UL == 0) {
            log_message(0x000a8ff3UL, 0x000a95abUL, 0x000a95abUL, b);
        } else {
            debug_print(0x000a8ff3UL, 0x000a95abUL, 0x000a95abUL, b);
        }
    }
    return base[5];
}
