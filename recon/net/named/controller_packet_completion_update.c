/* readable reconstruction; identity: FUN_0100aba4 @ 0x0100aba4
 * public-name: controller_packet_completion_update
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_completion_update      <= FUN_0100aba4 @ 0x0100aba4
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 */
/* net-core FUN_0100aba4 @ 0x100aba4 */

#include <stdint.h>

typedef void (*callback0_t)(void);
typedef void (*callback2_t)(uint32_t event, uint32_t status);

void controller_packet_completion_update(uint8_t *completion_flag)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000c48u;
    volatile uint8_t *packet = *(volatile uint8_t * volatile *)(state + 0x2cu);
    volatile uint8_t *context =
        *(volatile uint8_t * volatile *)(state + 0x28u) + 0xa8u;
    uint32_t mode = packet[0] & 3u;

    if (mode == 3u) {
        context[0x10u] = 1u;
        *(volatile uint16_t *)(state + 0x32u) |= 1u;
        *(volatile uint16_t *)(state + 0x30u) |= 0x800u;
        ((callback0_t)*(volatile uintptr_t *)(state + 0x34u))();
        packet = *(volatile uint8_t * volatile *)(state + 0x2cu);
    } else if (mode != 0u && packet[1] != 0u) {
        uint8_t length = packet[1];
        *(volatile uint16_t *)(state + 0x30u) |= 0x800u;
        if (*(volatile uint32_t *)(state + 0x38u) == 0u) {
            return;
        }
        if (length > 0xfbu) {
            state[0x3du] |= 0x10u;
            return;
        }
        if (state[0x3cu] != 0u) {
            ((callback2_t)*(volatile uintptr_t *)(state + 0x34u))(0x20u, 0u);
            return;
        }
        *completion_flag = 1u;
    }

    context[0x18u] = (uint8_t)((uint8_t)(context[0x18u] - 1u) != 0u);
    if (packet[1] != 0u) {
        *(volatile uint64_t *)(context + 0x80u) += 1u;
    }
}
