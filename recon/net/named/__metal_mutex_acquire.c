/* readable reconstruction; identity: FUN_0103ad4a @ 0x0103ad4a
 * public-name: __metal_mutex_acquire
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   __metal_mutex_acquire                    <= FUN_0103ad4a @ 0x0103ad4a
 */
/* net-core FUN_0103ad4a @ 0x103ad4a */
#include <stdint.h>
extern void FUN_0103689c(uint32_t, uint32_t, uint32_t, uint32_t);
void __metal_mutex_acquire(uint32_t object, uint32_t value)
{
    FUN_0103689c(object, value, 0xffffffffu, 0xffffffffu);
}
