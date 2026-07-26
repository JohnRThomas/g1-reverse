/* readable reconstruction; identity: FUN_010345f4 @ 0x010345f4
 * public-name: FUN_010345f4
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103df89                           @ 0x0103df89
 */
/* net-core FUN_010345f4 @ 0x10345f4 */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
extern uint64_t FUN_0103a8ea(uint32_t, uint32_t *);
extern void assert_print(uint32_t, uint32_t, uint32_t);
extern uint64_t assert_post_action(uint32_t, uint32_t);

uint32_t FUN_010345f4(uint32_t *configuration)
{
    uint32_t encoded = *configuration;
    uint64_t result = FUN_0103a8ea(encoded, configuration);
    uint32_t *destination = (uint32_t *)(uintptr_t)(uint32_t)(result >> 32);
    if ((uint32_t)result == 0) {
        assert_print(0x0103d2a7, 0x0103df89, 0x32f);
        result = assert_post_action(0x0103df89, 0x32f);
        destination = (uint32_t *)(uintptr_t)(uint32_t)(result >> 32);
        encoded = 0x32f;
    }
    for (;;) {
        *destination = encoded & 0x1f;
        if ((encoded >> 5) == 0) return G1_NRF_P0_NS_BASE;
        if ((encoded >> 5) == 1) return G1_NRF_P1_NS_BASE;
        assert_print(0x0103d2a7, 0x0103df89, 0x338);
        result = assert_post_action(0x0103df89, 0x338);
        destination = (uint32_t *)(uintptr_t)(uint32_t)(result >> 32);
        encoded = 0x338;
    }
}
