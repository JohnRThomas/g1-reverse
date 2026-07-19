#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032fdc @ 0x00032fdc
 * public-name: get_click_dispatch_flag
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_click_dispatch_flag                  <= FUN_00032fdc @ 0x00032fdc
 * address symbols (name @ address):
 *   g_click_dispatch_flag                    @ 0x20019ef2
 */
/* Reconstructed FUN_00032fdc @ 0x32fdc (uncatalogued exact leaf entry). */

#include <stdint.h>

uint32_t get_click_dispatch_flag(void)
{
    return *(volatile uint8_t *)((unsigned long)&g_click_dispatch_flag) /*=0x20019ef2*/;
}
