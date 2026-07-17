/* net-core FUN_0100f48c @ 0x100f48c  (CFG-directed candidate) */

#include <stdint.h>
extern void sdc_assertion_fail(uint32_t module, uint32_t line) __attribute__((noreturn));

static inline __attribute__((always_inline)) uint16_t radio_packet_time(uint8_t phy, uint16_t payload_length)
{
    if ((phy & 0x0cu) != 0u) {
        uint16_t time = (uint16_t)((uint32_t)payload_length * 64u + 0x3d0u);
        return time > 0xa90u ? 0xa90u : time;
    }
    if (phy == 1u) {
        return (uint16_t)((uint32_t)(payload_length + 0x0eu) * 8u);
    }
    if (phy == 2u) {
        return (uint16_t)((uint32_t)(payload_length + 0x0fu) * 4u);
    }
    sdc_assertion_fail(6u, 0x1e2u);
}

static inline __attribute__((always_inline)) uint32_t radio_minimum_time(uint8_t phy)
{
    if ((phy & 0x0cu) != 0u) {
        return 0xe90u;
    }
    if (phy == 1u) {
        return 0x1c8u;
    }
    if (phy == 2u) {
        return 0xe8u;
    }
    sdc_assertion_fail(6u, 0x1e2u);
}

void sdc_conn_radio_overhead_set(void *connection, uint32_t fixed_overhead)
{
    uint8_t *ctx = (uint8_t *)connection;
    uint8_t first_phy = ctx[0x6e];
    uint8_t second_phy = ctx[0x6f];
    uint32_t interval_margin = *(uint32_t *)(ctx + 0x14) < 0x1d4cu ? 0x4du : 0x96u;

    uint32_t first_time = radio_packet_time(first_phy, *(uint16_t *)(ctx + 0x38));
    if ((first_phy & 0x0cu) == 0u) {
        uint32_t cap = *(uint16_t *)(ctx + 0x4a);
        uint32_t second_cap = *(uint16_t *)(ctx + 0x4e);
        if (second_cap <= cap) {
            cap = second_cap;
        }
        if (first_time <= cap) {
            cap = first_time;
        }
        first_time = cap;
    }

    uint32_t second_time = radio_packet_time(second_phy, *(uint16_t *)(ctx + 0x40));
    if ((second_phy & 0x0cu) == 0u) {
        uint32_t cap = *(uint16_t *)(ctx + 0x42);
        if (cap <= second_time) {
            second_time = cap;
        }
    }

    if (*(volatile uint8_t *)0x21000ef2u != 0u) {
        uint32_t minimum = radio_minimum_time(second_phy);
        if (second_time < minimum) {
            second_time = minimum;
        }
        minimum = radio_minimum_time(first_phy);
        if (first_time < minimum) {
            first_time = minimum;
        }
    }

    *(uint32_t *)(ctx + 0x34) = second_time + first_time + interval_margin + fixed_overhead + 6u;
}
