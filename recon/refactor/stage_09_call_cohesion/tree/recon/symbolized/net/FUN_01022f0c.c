#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01022f0c @ 0x01022f0c
 * public-name: FUN_01022f0c
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01022f0c @ 0x01022f0c -- raw backmap retained. */
#include <stdint.h>

extern uint64_t FUN_0102445c(uint32_t, uint32_t);

uint64_t FUN_01022f0c(uint32_t index)
{
    volatile uint8_t *entry = (volatile uint8_t *)((unsigned long)&g_libc_tz_calc_state) /*=0x210016f0*/ + index * 0x20u;
    uint64_t base = FUN_0102445c(*(volatile uint32_t *)(entry + 0xd8),
                                 *(volatile uint32_t *)(entry + 0xdc));
    return base + *(volatile uint8_t *)(entry + 0xe4) +
           *(volatile uint16_t *)(entry + 0xe6) + 1u;
}
