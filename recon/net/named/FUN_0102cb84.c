/* readable reconstruction; identity: FUN_0102cb84 @ 0x0102cb84
 * public-name: FUN_0102cb84
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_poll_signal_raise               <= FUN_010388c8 @ 0x010388c8
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3e3                           @ 0x0103d3e3
 */
/* net-core FUN_0102cb84 @ 0x102cb84 */
#include <stdint.h>

extern void z_impl_k_poll_signal_raise(uint32_t object, uint32_t completion);
extern void assert_print(const void *module, const void *file, unsigned line);
extern void assert_post_action(const void *file, unsigned line);

int FUN_0102cb84(uint32_t state[3], uint32_t completion)
{
    uint32_t mode = state[1] & 3u;
    uint32_t object;

    state[2] = completion;
    switch (mode) {
    case 1:
        state[1] = 0;
        return 0;
    case 2:
        object = state[0];
        state[1] = 0;
        if (object != 0)
            z_impl_k_poll_signal_raise(object, completion);
        return 0;
    case 3:
        object = state[0];
        state[1] = 0;
        return (int)object;
    default:
        assert_print((const void *)0x0103d2a7u,
                     (const void *)0x0103d3e3u, 0x45);
        assert_post_action((const void *)0x0103d3e3u, 0x45);
        return 0;
    }
}
