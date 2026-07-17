/* SDK resource_endpoint_enable @ 0x010343e0, exact extent 0x20.
 * Raw/address backmaps:
 *   FUN_010343e0@0x010343e0
 *   assert_print = FUN_01039bbe@0x01039bbe
 *   assert_post_action = FUN_01039bb0@0x01039bb0
 * Return is at 0x010343fe; literals begin at 0x01034400.
 */
#include <stdint.h>
#define resource_endpoint_enable FUN_010343e0

extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void resource_endpoint_enable(uint32_t endpoint, uint8_t *owner)
{
    if (owner == 0) {
        assert_print(0x0103d2a7u, 0x0103e628u, 0x4au);
        assert_post_action(0x0103e628u, 0x4au);
    }
    *(uint32_t *)(owner + 0x80) = endpoint | 0x80000000u;
}
