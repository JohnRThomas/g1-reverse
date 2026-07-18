/* readable reconstruction; identity: FUN_0102ff54 @ 0x0102ff54
 * public-name: FUN_0102ff54
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103de3f                           @ 0x0103de3f
 */
/* net-core pool-buffer add/ref initializer @ 0x0102ff54.
 * Raw/address back-map: FUN_0102ff54 / 0x0102ff54.
 */
#include <stdint.h>

extern void assert_print(const void *, const void *, uint32_t);
extern void assert_post_action(const void *, uint32_t);
extern void FUN_0103b1fa(uint32_t, uint32_t, uint32_t, uint32_t);

void FUN_0102ff54(uint32_t pool, uint32_t buffer, uint32_t data,
                  uint32_t caller_context)
{
    if (pool == 0) {
        assert_print((const void *)0x0103d2a7u,
                     (const void *)0x0103de3fu, 0x1c7);
        assert_post_action((const void *)0x0103de3fu, 0x1c7);
    }
    if (buffer == 0) {
        assert_print((const void *)0x0103d2a7u,
                     (const void *)0x0103de3fu, 0x1c8);
        assert_post_action((const void *)0x0103de3fu, 0x1c8);
    }
    FUN_0103b1fa(pool, buffer, data, caller_context);
}
