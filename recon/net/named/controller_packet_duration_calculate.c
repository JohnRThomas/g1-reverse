/* readable reconstruction; identity: FUN_010122b4 @ 0x010122b4
 * public-name: controller_packet_duration_calculate
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_packet_airtime_compute        <= FUN_010109ec @ 0x010109ec
 *   controller_packet_duration_calculate     <= FUN_010122b4 @ 0x010122b4
 */
/* net-core FUN_010122b4 @ 0x10122b4  (CFG-directed candidate) */
#include <stdint.h>
extern uint32_t controller_descriptor_octet_product(const void *descriptor); /* FUN_01012b24 */
extern uint32_t FUN_01012b50(uint32_t product, uint32_t flags, uint32_t length,
                             uint32_t preserved_r3);
extern uint32_t FUN_01010990(uint32_t product, uint32_t octets);
extern uint32_t controller_packet_airtime_compute(uint32_t timing, uint32_t product, uint32_t octets,
                             uint32_t mode, uint32_t flags);
uint32_t controller_packet_duration_calculate(const volatile uint8_t *state, uint32_t mode,
                      uint32_t unused_r2, uint32_t preserved_r3)
{
    uint32_t product = controller_descriptor_octet_product((const void *)(state + 0x28));
    uint32_t flags = *(const volatile uint16_t *)(state + 2);
    if ((flags & 0x10u) != 0u) {
        return FUN_01012b50(product, flags, 0x28u, preserved_r3);
    }
    uint32_t timing = *(const volatile uint16_t *)(state +
        (((flags & 2u) != 0u) ? 0x54u : 0x4cu));
    product = FUN_01010990(product, state[4]);
    return controller_packet_airtime_compute(timing, product, state[5], mode, flags);
}
