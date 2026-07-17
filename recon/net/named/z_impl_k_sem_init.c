/* readable reconstruction; identity: FUN_0103b224 @ 0x0103b224
 * public-name: z_impl_k_sem_init
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_sem_init                        <= FUN_0103b224 @ 0x0103b224
 */
/* net-core FUN_0103b224 @ 0x0103b224 */
#include <stdint.h>

int32_t z_impl_k_sem_init(uint32_t state, uint32_t lower, uint32_t upper)
{
    uint32_t inner;

    if (upper == 0u || upper < lower) {
        return -22;
    }
    inner = state + 0x10u;
    *(uint32_t *)(uintptr_t)(state + 8u) = lower;
    *(uint32_t *)(uintptr_t)(state + 0xcu) = upper;
    *(uint32_t *)(uintptr_t)state = state;
    *(uint32_t *)(uintptr_t)(state + 4u) = state;
    *(uint32_t *)(uintptr_t)(state + 0x10u) = inner;
    *(uint32_t *)(uintptr_t)(state + 0x14u) = inner;
    return 0;
}
