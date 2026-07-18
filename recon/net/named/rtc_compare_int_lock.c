/* readable reconstruction; identity: FUN_01031248 @ 0x01031248
 * public-name: rtc_compare_int_lock
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   rtc_compare_int_lock                     <= FUN_01031248 @ 0x01031248
 * address symbols (name @ address):
 *   REG_41016308                             @ 0x41016308
 */
/* Net-core channel disable primitive FUN_01031248 @ 0x01031248, 56 bytes. */
#include <stdint.h>

uint32_t rtc_compare_int_lock(uint32_t channel)
{
    uint32_t shift = channel & 0xffu;
    uint32_t enabled_bit = shift < 32u ? 1u << shift : 0u;
    volatile uint32_t *enabled = (volatile uint32_t *)0x2100496cu;

    uint32_t previous = __atomic_fetch_and(enabled, ~enabled_bit,
                                           __ATOMIC_RELAXED);

    /* Hardware task-clear register; the firmware follows this with DMB/ISB. */
    uint32_t task_bit = shift < 16u ? 0x10000u << shift : 0u;
    *(volatile uint32_t *)0x41016308u = task_bit;

    return (previous & enabled_bit) != 0u;
}
