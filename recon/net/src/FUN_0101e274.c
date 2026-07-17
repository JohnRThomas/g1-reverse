/* net-core FUN_0101e274 @ 0x101e274  (CFG-directed candidate) */

#include <stdint.h>
extern void controller_timing_defaults_apply(void *state, int32_t signed_mode); /* FUN_0101e1e4 @ 0x0101e1e4 */
/* Readable role: controller_timing_state_reset. Raw back-map: FUN_0101e274 @ 0x0101e274. */
void FUN_0101e274(void *owner_pointer)
{
    volatile uint8_t *state = *(uint8_t **)((uint8_t *)owner_pointer + 4);
    *(volatile uint32_t *)(state + 0x94) = 0;
    *(volatile uint32_t *)(state + 0x98) = 0;
    *(volatile uint32_t *)(state + 0x9c) = 0;
    *(volatile uint32_t *)(state + 0x8c) = 0;
    *(volatile uint32_t *)(state + 0x90) = 0;
    *(volatile uint32_t *)(state + 0x9f) = 0;
    *(volatile uint16_t *)(state + 0x1a4) = 0;
    state[0x1a6] = 0;
    *(volatile uint16_t *)(state + 0x1a7) = 0;
    state[0x1a9] = 0;
    state[0x95] = 0x7f;
    state[0x97] = 0x7f;
    state[0x99] = 0x7f;
    state[0x9b] = 0x7f;
    controller_timing_defaults_apply((void *)state, (int8_t)state[0x72]);
    *(volatile uint32_t *)(state + 0x9c) = 0xffffffffu;
}
