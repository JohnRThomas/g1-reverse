#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0101fdd0 @ 0x0101fdd0
 * public-name: controller_radio_request_configure
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_request_configure       <= FUN_0101fdd0 @ 0x0101fdd0
 * address symbols (name @ address):
 *   g_net_radio_pending_reset_flag           @ 0x210014dc
 *   REG_41008000                             @ 0x41008000
 *   REG_4100e000                             @ 0x4100e000
 */
/* net-core controller_radio_request_configure @ 0x0101fdd0.
 * Raw backmap: FUN_0101fdd0@0x0101fdd0. */
#include <stdint.h>

extern void FUN_01020088(uint32_t);
extern void sdc_assertion_fail(uint32_t, uint32_t, uint32_t, uint32_t);

void controller_radio_request_configure(uint32_t mode, uint32_t context, uint32_t selector,
                  uint32_t channel, uint8_t power_index)
{
    volatile uint32_t *radio = (volatile uint32_t *)REG_4100e000 /*=0x4100e000*/;
    volatile uint32_t *timer = (volatile uint32_t *)0x4100f000u;
    volatile uint8_t *request = (volatile uint8_t *)((unsigned long)&g_net_radio_pending_reset_flag) /*=0x210014dc*/;
    uint32_t timer_value = 0x4100f000u;

    FUN_01020088(1);
    radio[0x141] = (mode & 3u) | (channel << 16) | 0x01000000u;
    radio[0x142] = context;
    radio[0x146] = (radio[0x146] & 0xffffff00u) | selector;
    radio[0x21] = 0;
    request[4] = (uint8_t)channel;
    timer[0x142] = 0x200;

    if ((mode & 0xfbu) == 0) {
        timer_value = 0x80000009u;
        radio[0x60] = timer_value;
        radio[0x21] = timer_value;
    }
    if (power_index > 2u) {
        sdc_assertion_fail(0x3c, 0x1d7, timer_value, ((unsigned long)&g_net_radio_pending_reset_flag) /*=0x210014dc*/);
        return;
    }

    radio[0x148] =
        ((volatile const uint8_t *)0x0103c4ccu)[power_index];
    if (mode == 1u) {
        ((volatile uint32_t *)REG_41008000 /*=0x41008000*/)[0x74] = 0x80000009u;
        radio[0x23] = 0x80000009u;
        request[1] = 1;
        request[3] = 1;
    } else {
        request[3] = (uint8_t)mode;
        request[1] = 1;
        if (mode > 2u) {
            return;
        }
    }
    request[0] = 1;
    radio[0x40] = 0;
    radio[0x80] = 0;
    radio[0] = 1;
}
