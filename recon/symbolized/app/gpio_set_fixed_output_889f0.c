#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00017a04 @ 0x00017a04
 * public-name: gpio_set_fixed_output_889f0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gpio_set_fixed_output_889f0              <= FUN_00017a04 @ 0x00017a04
 *   gpio_pin_set_dt                          <= FUN_0007c084 @ 0x0007c084
 */
/* Reconstructed FUN_00017a04 @ 0x17a04 (uncatalogued exact GPIO tail entry). */

/* iteration 14: the descriptor address was a hardcoded numeric literal, so
 * the PROVIDE() rebind in g1_app_globals.ld could not apply and the wrapper
 * handed gpio_pin_set_dt a raw ORIGINAL-image flash address; the port
 * pointer inside it is garbage in our link and gpio_pin_set_checked
 * asserted.  Referencing the pinned symbol is what makes the rebind real. */
#include <stdint.h>

extern uint32_t gpio_pin_set_dt(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t gpio_set_fixed_output_889f0(uint32_t unused0, uint32_t unused1,
                      uint32_t arg2, uint32_t arg3)
{
    (void)unused0;
    (void)unused1;
    return gpio_pin_set_dt((unsigned long)&rodata_889f0 /*=0x889f0*/, 0U, arg2, arg3);
}
