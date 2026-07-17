/* readable reconstruction; identity: FUN_010312d0 @ 0x010312d0
 * public-name: FUN_010312d0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   REG_41016304                             @ 0x41016304
 */
/* net-core FUN_010312d0 @ 0x10312d0 */
#include <stdint.h>

uint32_t FUN_010312d0(uint32_t channel, uint32_t enable)
{
    if (!enable)
        return channel;
    uint32_t shift = channel & 255u;
    uint32_t bit = shift < 32u ? 1u << shift : 0u;
    uint32_t *enabled = (uint32_t *)0x2100496cu;
    (void)__atomic_fetch_or(enabled, bit, __ATOMIC_ACQ_REL);
    *(volatile uint32_t *)0x41016304u = shift < 16u ? 0x10000u << shift : 0u;
    uint32_t pending = *(volatile uint32_t *)0x21004964u;
    if (shift < 32u && ((pending >> shift) & 1u))
        *(volatile uint32_t *)0xe000e200u = 0x00400000u;
    /* The machine routine leaves the channel value in r0. */
    return channel;
}
