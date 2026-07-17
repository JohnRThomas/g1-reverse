#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100af3c @ 0x0100af3c
 * public-name: FUN_0100af3c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 */
/* net-core FUN_0100af3c @ 0x0100af3c, exact Thumb extent 0xb4 bytes. */
#include <stdint.h>

extern void FUN_010202fc(void);
extern void FUN_01020764(uint32_t value);
extern void FUN_0101ff4c(void);
extern void FUN_0101fe98(uint32_t first, uint32_t second,
                         uint32_t third, uint32_t fourth);
extern void FUN_01020820(uint32_t mode);
extern void FUN_010208f0(uint32_t state, uint32_t zero, uint32_t selector);

#define CONTROLLER_STATE ((volatile uint8_t *)((unsigned long)&g_net_radio_drv_ctx) /*=0x21000c48*/)

void FUN_0100af3c(uint32_t force_refresh, uint32_t unused_r1,
                  uint32_t unused_r2, uint32_t preserved_r3)
{
    (void)unused_r1;
    (void)unused_r2;
    volatile uint8_t *record =
        *(volatile uint8_t * const volatile *)(CONTROLLER_STATE + 0x28);
    uint8_t extended = record[0xcb];
    uint8_t phase = CONTROLLER_STATE[0x7a];
    *(volatile uint32_t *)(CONTROLLER_STATE + 0x2c) =
        *(volatile uint32_t *)(CONTROLLER_STATE + 0xb8);
    if (extended != 0u) {
        phase = (uint8_t)(phase + 4u);
    }
    if (phase != 0xffu || force_refresh != 0u || record[0x6f] != record[0x6e]) {
        FUN_010202fc();
        extended = record[0xcb];
    }

    if (extended == 0u) {
        FUN_01020764(*(volatile uint32_t *)(CONTROLLER_STATE + 0x2c));
        FUN_0101ff4c();
    } else {
        uint32_t second = *(volatile uint32_t *)(CONTROLLER_STATE + 0x84);
        FUN_01020764(second);
        CONTROLLER_STATE[0xa0] = CONTROLLER_STATE[0x24] != 0u;
        uint32_t third = *(volatile uint32_t *)(record + 0x128);
        uint32_t fourth = *(volatile uint32_t *)(record + 0x12c);
        *(volatile uint32_t *)(CONTROLLER_STATE + 0x98) = third;
        *(volatile uint32_t *)(CONTROLLER_STATE + 0x9c) = fourth;
        FUN_0101fe98(*(volatile uint32_t *)(CONTROLLER_STATE + 0x2c),
                     second, third, fourth);
    }

    if (force_refresh == 0u) {
        uint32_t mode = record[0x6f] & 0x0cu;
        FUN_01020820(mode == 0u ? 0u : 0x28u);
    }
    FUN_010208f0(*(volatile uint32_t *)(record + 0x14) < 0x1d4cu,
                  0u, record[0x6e]);
    CONTROLLER_STATE[0x44] = 2u;
    (void)preserved_r3;
}
