/* readable reconstruction; identity: FUN_01028034 @ 0x01028034
 * public-name: FUN_01028034
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core FUN_01028034 @ 0x01028034, exact executable extent 0x8a. */
/*
 * Retained private-controller reconstruction.
 * Raw entry/backmap: FUN_01028034 @ 0x01028034, exact extent 0x8a.
 */
#include <stdint.h>

extern uint32_t FUN_01027ad2(uint8_t side);

#define controller_active_slot_value_get FUN_01028034

__attribute__((optimize("O0")))
uint16_t controller_active_slot_value_get(const void *link, uint8_t side)
{
    const volatile uint8_t *bytes = (const volatile uint8_t *)link;
    const volatile uint16_t *halfwords = (const volatile uint16_t *)link;
    uint8_t slot = (uint8_t)FUN_01027ad2(side);

    if (bytes[0x14u + slot] == 2u) {
        return halfwords[0x0cu + slot];
    }
    if (bytes[0x15u + slot] == 2u) {
        return halfwords[0x0du + slot];
    }
    if (bytes[0x14u + slot] == 3u) {
        return halfwords[0x0cu + slot];
    }
    if (bytes[0x15u + slot] == 3u) {
        return halfwords[0x0du + slot];
    }
    return 0u;
}
