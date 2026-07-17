#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101a070 @ 0x0101a070
 * public-name: sdc_llcp_decode_control_pdu
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_llcp_decode_control_pdu              <= FUN_0101a070 @ 0x0101a070
 */
/* net-core FUN_0101a070 @ 0x101a070 */
#include <stdint.h>

extern uint8_t FUN_0100e04c(const uint8_t *packet);
extern uint8_t FUN_0100e064(const uint8_t *packet);
extern void FUN_01019f9c(const uint8_t *packet, void *description);

void sdc_llcp_decode_control_pdu(const uint8_t *packet, void *description)
{
    volatile uint8_t *out = (volatile uint8_t *)description;
    uint8_t kind = packet[0] & 0x0fU;
    uint32_t value;

    if (kind == 7) {
        FUN_01019f9c(packet, description);
        return;
    }
    out[0x11] = FUN_0100e04c(packet);
    out[0x12] = FUN_0100e064(packet);

    switch (kind) {
    case 0: case 2: case 4: case 6:
        out[1] = 1;
        *(volatile uintptr_t *)(out + 4) = (uintptr_t)(packet + 3);
        *(volatile uint32_t *)(out + 8) = 0;
        value = (uint8_t)(packet[1] - 6U);
        out[0x10] = (uint8_t)value;
        if (value != 0) {
            *(volatile uintptr_t *)(out + 0x0c) = (uintptr_t)(packet + 9);
            return;
        }
        break;
    case 1:
        out[1] = 3;
        out[0x10] = 0;
        *(volatile uint32_t *)(out + 0x0c) = 0;
        *(volatile uintptr_t *)(out + 4) = (uintptr_t)(packet + 3);
        *(volatile uintptr_t *)(out + 8) = (uintptr_t)(packet + 9);
        return;
    default:
        value = 0;
        out[1] = 0;
        out[0x10] = 0;
        *(volatile uint32_t *)(out + 4) = 0;
        *(volatile uint32_t *)(out + 8) = 0;
        break;
    }
    *(volatile uint32_t *)(out + 0x0c) = value;
}
