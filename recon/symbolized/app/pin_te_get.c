#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000654ac @ 0x000654ac
 * public-name: pin_te_get
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* NCS 2.5.1 pin_te_get @ 0x000654ac (FUN_000654ac). */
#include <stdint.h>

extern uint32_t get_pin_idx(uint32_t pin); /* FUN_00065434 */

int pin_te_get(unsigned long pin) {
    volatile const uint16_t *const pin_flags =
        (volatile const uint16_t *)((unsigned long)g_gpiote_cb) /*=0x20002bc0*/;
    return (uint8_t)(pin_flags[get_pin_idx(pin) + 8u] >> 13);
}
