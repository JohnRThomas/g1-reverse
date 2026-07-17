/* readable reconstruction; identity: FUN_00065448 @ 0x00065448
 * public-name: gpiote_pin_is_used
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_pin_idx                              <= FUN_00065434 @ 0x00065434
 *   gpiote_pin_is_used                       <= FUN_00065448 @ 0x00065448
 * address symbols (name @ address):
 *   g_gpiote_cb                              @ 0x20002bc0
 */
/* Reconstructed FUN_00065448 @ 0x65448  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
extern int get_pin_idx(void);

unsigned short gpiote_pin_is_used(void)
{
    int iVar1 = get_pin_idx();
    volatile uint16_t *base = (volatile uint16_t *)0x20002bc0UL;
    return base[iVar1 + 8] & 1;
}
