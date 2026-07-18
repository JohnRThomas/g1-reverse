/* readable reconstruction; identity: FUN_01030dd0 @ 0x01030dd0
 * public-name: FUN_01030dd0
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103df89                           @ 0x0103df89
 */
/* net-core FUN_01030dd0 @ 0x1030dd0 */
#include <stdint.h>

extern void assert_print(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern void assert_post_action(uint32_t, uint32_t);

uint32_t FUN_01030dd0(uint32_t *descriptor, uint32_t a1, uint32_t a2, uint32_t a3)
{
    uint32_t word = *descriptor;
    uint32_t group = word >> 5;
    uint32_t result;

    if (group == 0 && word == 0) {
        result = 0x418c0500u;
    } else if (group == 1 && (word & 31u) == 0) {
        word &= 31u;
        result = 0x418c0800u;
    } else {
        assert_print(0x0103d2a7u, 0x0103df89u, 0x32fu, word, a3);
        assert_post_action(0x0103df89u, 0x32fu);
        /* Both reporters are fatal in production. */
        return 0;
    }
    *descriptor = word;
    return result;
}
