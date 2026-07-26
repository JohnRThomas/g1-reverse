/* net-core FUN_010345f4 @ 0x10345f4 */
#include <stdint.h>
#include "../../headers/g1_nrf_regs.h"
extern uint64_t FUN_0103a8ea(uint32_t, uint32_t *);
extern void FUN_01039bbe(uint32_t, uint32_t, uint32_t);
extern uint64_t FUN_01039bb0(uint32_t, uint32_t);

uint32_t FUN_010345f4(uint32_t *configuration)
{
    uint32_t encoded = *configuration;
    uint64_t result = FUN_0103a8ea(encoded, configuration);
    uint32_t *destination = (uint32_t *)(uintptr_t)(uint32_t)(result >> 32);
    if ((uint32_t)result == 0) {
        FUN_01039bbe(0x0103d2a7, 0x0103df89, 0x32f);
        result = FUN_01039bb0(0x0103df89, 0x32f);
        destination = (uint32_t *)(uintptr_t)(uint32_t)(result >> 32);
        encoded = 0x32f;
    }
    for (;;) {
        *destination = encoded & 0x1f;
        if ((encoded >> 5) == 0) return G1_NRF_P0_NS_BASE;
        if ((encoded >> 5) == 1) return G1_NRF_P1_NS_BASE;
        FUN_01039bbe(0x0103d2a7, 0x0103df89, 0x338);
        result = FUN_01039bb0(0x0103df89, 0x338);
        destination = (uint32_t *)(uintptr_t)(uint32_t)(result >> 32);
        encoded = 0x338;
    }
}
