#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101e1e4 @ 0x0101e1e4
 * public-name: controller_timing_defaults_apply
 * durable-map: recon/catalogs/function_names_net.json
 */
/* CPUNET controller timing default propagation @ 0x0101e1e4.
 * Raw back-map: FUN_0101e1e4@0x0101e1e4; extent 0x90. */
#include <stdint.h>

extern int FUN_01021920(int value, void *scratch, unsigned scale, unsigned round);
extern uint32_t FUN_0101f8cc(void);

void controller_timing_defaults_apply(uint8_t *state, int requested)
{
    uint8_t scratch[8];
    int upper = FUN_01021920(0x7f, scratch, 0x988, 1);
    int lower = FUN_01021920(-0x80, scratch, 0x988, 1);
    uint8_t flags = (uint8_t)(requested == lower);
    uint32_t snapshot;
    unsigned mask;

    if (requested == upper)
        flags |= 2;
    snapshot = FUN_0101f8cc();
    if (snapshot & (1u << 8)) {
        mask = (snapshot & (1u << 11)) ? 0x0f : 0x03;
    } else {
        mask = ((snapshot & (1u << 8)) || (snapshot & (1u << 11)))
             ? 0x0d : 0x01;
    }
    state[0x8d] = (uint8_t)requested;
    state[0x8c] = flags;
    if (mask & 2u) {
        state[0x8f] = (uint8_t)requested;
        state[0x8e] = flags;
    }
    if (mask & 4u) {
        state[0x91] = (uint8_t)requested;
        state[0x90] = flags;
    }
    if (mask & 8u) {
        state[0x93] = (uint8_t)requested;
        state[0x92] = flags;
    }
}
