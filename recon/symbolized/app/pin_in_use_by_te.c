#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00065460 @ 0x00065460
 * public-name: pin_in_use_by_te
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed pin_in_use_by_te @ 0x00065460 from configured NCS 2.5.1 nrfx_gpiote.c.
 * Identity/backmap: FUN_00065460.
 */
#include <stdbool.h>
#include <stdint.h>

extern uint32_t get_pin_idx(uint32_t pin); /* FUN_00065434 @ 0x00065434 */

bool pin_in_use_by_te(uint32_t pin)
{
    volatile const uint16_t *pin_flags =
        (volatile const uint16_t *)(uintptr_t)((unsigned long)g_gpiote_cb) /*=0x20002bc0*/;
    return (pin_flags[get_pin_idx(pin) + 8u] & UINT16_C(0x20)) != 0u;
}
