/* readable reconstruction; identity: FUN_01021b7c @ 0x01021b7c
 * public-name: FUN_01021b7c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01021b7c @ 0x01021b7c, exact Thumb extent 0x16c bytes. */
#include <stdint.h>

extern uint16_t FUN_010246d8(void);
#define controller_phy_timing_code_get FUN_010246d8

static int32_t controller_spacing_threshold(void)
{
    uint16_t code = controller_phy_timing_code_get();
    if (code == 0x356u) {
        return 0x1d;
    }
    if (code == 0x5f5u) {
        return 0x33;
    }
    if (code == 0x18cu) {
        return 0x0e;
    }
    return 1;
}

/* Find the record interval surrounding a requested controller time window. */
uint32_t FUN_01021b7c(const uint8_t *request, uint32_t bank,
                      uint8_t *previous_out, uint8_t *current_out)
{
    volatile uint8_t *const state = (volatile uint8_t *)0x210016f0u;
    uint8_t current = state[0x30u + bank * 3u];
    uint8_t previous = 0x20u;
    uint32_t request_low = *(const uint32_t *)(request + 0u);
    uint32_t request_high = *(const uint32_t *)(request + 4u);
    uint32_t request_span = *(const uint32_t *)(request + 8u);
    uint16_t request_flag = *(const uint16_t *)(request + 0x0eu);

    *previous_out = previous;
    if (current == 0x20u) {
        *current_out = current;
        return 1u;
    }

    for (;;) {
        volatile uint8_t *record = state + (uint32_t)current * 0x20u;
        uint32_t record_low = *(volatile uint32_t *)(record + 0xd8u);
        uint32_t record_high = *(volatile uint32_t *)(record + 0xdcu);
        uint32_t adjustment = *(volatile uint32_t *)(record + 0xe0u);
        uint32_t adjusted_low = record_low + adjustment;
        uint32_t adjusted_high = record_high + (adjusted_low < record_low);

        if (request_high < adjusted_high ||
            (request_high == adjusted_high && request_low < adjusted_low)) {
            break;
        }

        if (request_flag != 0u &&
            *(volatile uint16_t *)(record + 0xe6u) == 0u &&
            (int32_t)(request_low - record_low) <
                controller_spacing_threshold()) {
            break;
        }

        *previous_out = current;
        previous = current;
        current = state[0x51u +
                        ((uint32_t)current + bank * 0x20u) * 2u];
        if (current == 0x20u) {
            *current_out = previous;
            return 1u;
        }
    }

    *current_out = previous;
    for (;;) {
        volatile uint8_t *record = state + (uint32_t)current * 0x20u;
        uint32_t record_low = *(volatile uint32_t *)(record + 0xd8u);
        uint32_t record_high = *(volatile uint32_t *)(record + 0xdcu);
        uint32_t end_low = request_low + request_span;
        uint32_t end_high = request_high + (end_low < request_low);

        if (record_high > end_high ||
            (record_high == end_high && record_low >= end_low)) {
            uint16_t record_flag =
                *(volatile uint16_t *)(record + 0xe6u);
            if (record_flag == 0u || request_flag != 0u ||
                (int32_t)(record_low - request_low) >=
                    controller_spacing_threshold()) {
                return 1u;
            }
        }

        *current_out = current;
        if (state[0xe8u + (uint32_t)current * 0x20u] <= request[0x10]) {
            return 0u;
        }

        current = state[0x51u +
                        ((uint32_t)current + bank * 0x20u) * 2u];
        if (current == 0x20u) {
            return 1u;
        }
    }
}
