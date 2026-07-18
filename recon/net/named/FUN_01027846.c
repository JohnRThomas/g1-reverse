/* readable reconstruction; identity: FUN_01027846 @ 0x01027846
 * public-name: FUN_01027846
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01027846 @ 0x1027846  (CFG-directed candidate) */

#include <stdint.h>
extern uint32_t FUN_010277c2(uint32_t, uint32_t);
extern uint32_t FUN_010277f2(uint32_t, uint32_t);
extern uint32_t FUN_01027822(uint32_t, uint32_t);
uint32_t FUN_01027846(uint32_t first_a, uint32_t first_b,
                      uint32_t second_a, uint32_t second_b)
{
    uint32_t first = FUN_010277c2(first_a & 0xffffu, second_a & 0xffffu);
    uint32_t second = FUN_010277f2(first_b & 0xffffu, second_b & 0xffffu);
    return FUN_01027822(first, second);
}
