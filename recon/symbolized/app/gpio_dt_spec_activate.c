#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000179ec @ 0x000179ec
 * public-name: gpio_dt_spec_activate
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_dt_spec_activate                    <= FUN_000179ec @ 0x000179ec
 * address symbols (name @ address):
 *   rodata_889f8                             @ 0x000889f8
 */
/* Reconstructed FUN_000179ec @ 0x179ec  (parity: 300/300 trials, PROVEN) */

extern void FUN_0007c084(unsigned int, unsigned int, unsigned int, unsigned int);

void gpio_dt_spec_activate(unsigned int unused0, unsigned int unused1,
                  unsigned int arg2, unsigned int arg3)
{
  (void)unused0;
  (void)unused1;
  FUN_0007c084(((unsigned long)&rodata_889f8) /*=0x889f8*/, 1, arg2, arg3);
}
