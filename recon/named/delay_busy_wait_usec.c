/* readable reconstruction; identity: FUN_0004c254 @ 0x0004c254
 * public-name: delay_busy_wait_usec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   delay_busy_wait_usec                     <= FUN_0004c254 @ 0x0004c254
 * address symbols (name @ address):
 *   g_20002bb8                               @ 0x20002bb8
 */
/* Reconstructed FUN_0004c254 @ 0x4c254
 * CFG_VERIFY_CALL_ARITIES=1
 * Readable identity: delay_scaled_busy_wait.
 * Raw/address backmap: delay_scaled_busy_wait <= FUN_0004c254 @ 0x0004c254.
 */

#include <stdint.h>

typedef void (*busy_wait_fn_t)(uint32_t cycles);

void delay_busy_wait_usec(uint32_t usec)
{
    volatile uint32_t *const cycles_per_second =
        (volatile uint32_t *)0x20002bb8UL;
    busy_wait_fn_t const busy_wait = (busy_wait_fn_t)0x00088841UL;

    if (usec != 0U) {
        busy_wait(usec * (*cycles_per_second / 1000000U));
    }
}
