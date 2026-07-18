#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0103b244 @ 0x0103b244
 * public-name: flag_test_and_clear
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   flag_test_and_clear                      <= FUN_0103b244 @ 0x0103b244
 */
/* Zephyr work-queue flag_test_and_clear @ 0x0103b244,
 * exact extent 0x16.
 * Raw/address backmap: FUN_0103b244@0x0103b244. */
#include <stdbool.h>
#include <stdint.h>
#define flag_test_and_clear flag_test_and_clear

bool flag_test_and_clear(uint32_t *flags, uint32_t bit)
{
    uint32_t prior = *flags;

    *flags = prior & ~(1u << bit);
    return ((prior >> bit) & 1u) != 0u;
}
