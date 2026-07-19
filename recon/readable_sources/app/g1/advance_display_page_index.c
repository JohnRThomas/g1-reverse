#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000369f8 @ 0x000369f8
 * public-name: advance_display_page_index
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   advance_display_page_index               <= FUN_000369f8 @ 0x000369f8
 * address symbols (name @ address):
 *   g_display_page_index                     @ 0x2001b810
 *   g_display_page_dirty_flag                @ 0x2001b811
 */
/* Reconstructed FUN_000369f8 @ 0x369f8  (parity: 300/300 trials, PROVEN) */

void advance_display_page_index(void)
{
    *(volatile unsigned char*)((unsigned long)&g_display_page_dirty_flag) /*=0x2001b811*/ = 1;
    unsigned char bVar1 = (unsigned char)(*(volatile unsigned char*)((unsigned long)&g_display_page_index) /*=0x2001b810*/ + 1);
    if (bVar1 >= 5) {
        bVar1 = 0;
    }
    *(volatile unsigned char*)((unsigned long)&g_display_page_index) /*=0x2001b810*/ = bVar1;
}
