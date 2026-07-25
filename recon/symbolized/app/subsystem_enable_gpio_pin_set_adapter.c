#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000179f8 @ 0x000179f8
 * public-name: subsystem_enable_gpio_pin_set_adapter
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* CPUAPP subsystem-enable helper @ 0x000179f8.
 * Raw/back-map identity: FUN_000179f8, exact extent 0x0c bytes.
 * The fixed GPIO descriptor at 0x000889f0 is P0.21. */
/* iteration 14: the descriptor address was a hardcoded numeric literal, so
 * the PROVIDE() rebind in g1_app_globals.ld could not apply and the wrapper
 * handed gpio_pin_set_dt a raw ORIGINAL-image flash address; the port
 * pointer inside it is garbage in our link and gpio_pin_set_checked
 * asserted.  Referencing the pinned symbol is what makes the rebind real. */
#include <stdint.h>

extern uint32_t gpio_pin_set_dt(uint32_t descriptor, uint32_t value,
                             uint32_t arg2, uint32_t arg3);

uint32_t subsystem_enable_gpio_pin_set_adapter(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return gpio_pin_set_dt((unsigned long)&rodata_889f0 /*=0x889f0*/, 1u, arg2, arg3);
}
