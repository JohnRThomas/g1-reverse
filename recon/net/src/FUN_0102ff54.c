/* net-core pool-buffer add/ref initializer @ 0x0102ff54.
 * Raw/address back-map: FUN_0102ff54 / 0x0102ff54.
 */
#include <stdint.h>

extern void assert_print(const void *, const void *, uint32_t);
extern __attribute__((noreturn)) void FUN_01039bb0(const void *, uint32_t);
extern void FUN_0103b1fa(uint32_t, uint32_t);
#define assert_post_action FUN_01039bb0
#define recovered_k_queue_append FUN_0103b1fa

void FUN_0102ff54(uint32_t queue, uint32_t buffer)
{
    if (queue == 0) {
        assert_print((const void *)0x0103d2a7u,
                     (const void *)0x0103de3fu, 0x1c7);
        assert_post_action((const void *)0x0103de3fu, 0x1c7);
    }
    if (buffer == 0) {
        assert_print((const void *)0x0103d2a7u,
                     (const void *)0x0103de3fu, 0x1c8);
        assert_post_action((const void *)0x0103de3fu, 0x1c8);
    }
    recovered_k_queue_append(queue, buffer);
}
