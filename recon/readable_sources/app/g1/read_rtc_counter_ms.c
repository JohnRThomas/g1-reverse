#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0007d0aa @ 0x0007d0aa
 * public-name: read_rtc_counter_ms
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   attr_store_get                           <= FUN_000302f8 @ 0x000302f8
 *   read_rtc_counter_ms                      <= FUN_0007d0aa @ 0x0007d0aa
 */
/* Reconstructed FUN_0007d0aa @ 0x7d0aa  (parity: 300/300 trials, PROVEN) */

extern void attr_store_get(unsigned int, int*);

void read_rtc_counter_ms(int *param_1)
{
    attr_store_get(0x1c04, param_1);
    *(volatile int*)param_1 = *(volatile int*)param_1 >> 10;
}
