#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_010343e0 @ 0x010343e0
 * public-name: FUN_010343e0
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103e628                           @ 0x0103e628
 */
/* SDK resource_endpoint_enable @ 0x010343e0, exact extent 0x20.
 * Raw/address backmaps:
 *   FUN_010343e0@0x010343e0
 *   assert_print = FUN_01039bbe@0x01039bbe
 *   assert_post_action = FUN_01039bb0@0x01039bb0
 * Return is at 0x010343fe; literals begin at 0x01034400.
 */
#include <stdint.h>
#include "../../headers/g1_dedupe.h"
#define resource_endpoint_enable FUN_010343e0

extern void assert_print(uint32_t, uint32_t, uint32_t); /* FUN_01039bbe */
extern __attribute__((noreturn)) void
assert_post_action(uint32_t, uint32_t); /* FUN_01039bb0 */

void resource_endpoint_enable(uint32_t endpoint, uint8_t *owner)
{
    if (owner == 0) {
        G1_NET_ASSERT_FAIL((((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103e628) /*=0x103e628*/, 0x4au), (((unsigned long)&rodata_103e628) /*=0x103e628*/, 0x4au));
    }
    *(uint32_t *)(owner + 0x80) = endpoint | 0x80000000u;
}
