/* Reconstructed FUN_0004e474 @ 0x4e474
 * Readable identity: settings_store_init.
 * Raw/address backmap: settings_store_init <= FUN_0004e474 @ 0x0004e474.
 */

#include <stdint.h>

void FUN_0004e474(void)
{
    volatile uint32_t *const settings_load_srcs =
        (volatile uint32_t *)0x2000a104UL;

    settings_load_srcs[0] = 0U;
    settings_load_srcs[1] = 0U;
}
