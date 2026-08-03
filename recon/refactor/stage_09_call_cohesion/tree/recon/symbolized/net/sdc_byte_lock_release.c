#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102a208 @ 0x0102a208
 * public-name: sdc_byte_lock_release
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_byte_lock_release                    <= FUN_0102a208 @ 0x0102a208
 */
/* FUN_0102a208 @ 0x0102a208: release a byte lock under a PRIMASK critical section. */
#include <stdint.h>

static inline uint32_t primask_get(void)
{
    uint32_t value;
    __asm volatile("mrs %0, primask" : "=r"(value));
    return value;
}

uint32_t sdc_byte_lock_release(volatile uint8_t *lock)
{
    uint32_t saved_primask = primask_get();
    __asm volatile("cpsid i" ::: "memory");
    *lock = 0u;
    if (saved_primask == 0u) {
        __asm volatile("cpsie i" ::: "memory");
    }
    return 0u;
}

/* Raw identity/back-map: FUN_0102a208 @ 0x0102a208, true extent 0x12. */
extern __typeof(sdc_byte_lock_release) FUN_0102a208
    __attribute__((alias("sdc_byte_lock_release")));
