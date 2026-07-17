/* net-core FUN_01012b50 @ 0x01012b50 */
#include <stdint.h>

/* Raw/address backmaps:
 * controller_fatal = FUN_01008d00@0x01008d00
 * packet_duration_table = 0x0103c1d4
 */
extern void FUN_01008d00(uint32_t module, uint32_t line)
    __attribute__((noreturn));

uint32_t FUN_01012b50(uint32_t product, uint32_t packet_type)
{
    volatile const uint16_t * const packet_duration_table =
        (volatile const uint16_t *)0x0103c1d4u;
    uint32_t product_index = product - 1u;

    if (product_index > 2u) {
        FUN_01008d00(0x2fu, 0xcau);
    }
    if (packet_type == 16u) {
        return packet_duration_table[product_index];
    }
    if (packet_type == 18u || packet_type == 19u) {
        return packet_duration_table[8u + product_index];
    }
    if (packet_type == 21u) {
        return packet_duration_table[4u + product_index];
    }
    FUN_01008d00(0x2fu, 0xd8u);
}
