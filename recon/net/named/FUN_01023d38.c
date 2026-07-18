/* readable reconstruction; identity: FUN_01023d38 @ 0x01023d38
 * public-name: FUN_01023d38
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_libc_tz_calc_state                     @ 0x210016f0
 */
/* net-core FUN_01023d38 @ 0x01023d38 -- raw backmap retained. */
#include <stdint.h>

extern uint64_t FUN_0102445c(uint32_t, uint32_t);
extern void FUN_01024524(uint32_t, uint32_t, uint32_t *, uint32_t *, uint8_t *);
extern int FUN_010250d0(uint32_t, ...);
extern __attribute__((noreturn)) void FUN_010256dc(uint32_t, uint32_t, ...);
#define controller_fault FUN_010256dc

void FUN_01023d38(uint32_t offset)
{
    volatile uint8_t *const controller = (volatile uint8_t *)0x210016f0u;
    if (controller[0x4a] == 0x20)
        controller_fault(0x70, 0xb45);
    if (*(volatile int32_t *)(controller + 0x0c) != -1 ||
        *(volatile int32_t *)(controller + 0x08) != -1)
        controller_fault(0x70, 0xb46);

    volatile uint8_t *slot = controller + controller[0x4a] * 0x20u;
    uint64_t deadline = FUN_0102445c(*(volatile uint32_t *)(slot + 0xd8),
                                     *(volatile uint32_t *)(slot + 0xdc));
    deadline += (uint32_t)*(volatile uint16_t *)(slot + 0xe6) +
                slot[0xe4] + 1u + offset;

    uint32_t scratch;
    uint32_t converted[2];
    uint8_t remainder;
    FUN_01024524((uint32_t)deadline, (uint32_t)(deadline >> 32),
                 &scratch, converted, &remainder);
    uint64_t armed = ((uint64_t)converted[1] << 32) | converted[0];
    armed += remainder > 0x0f;
    *(volatile uint32_t *)(controller + 8) = (uint32_t)armed;
    *(volatile uint32_t *)(controller + 12) = (uint32_t)(armed >> 32);

    if (controller[0x37] != 0 && FUN_010250d0(5) == 0)
        controller_fault(0x70, 0xb5b);
}
