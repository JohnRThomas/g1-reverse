#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100a5c8 @ 0x0100a5c8
 * public-name: controller_descriptor_array_encode
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_descriptor_array_encode       <= FUN_0100a5c8 @ 0x0100a5c8
 * address symbols (name @ address):
 *   g_21000be4                               @ 0x21000be4
 *   g_21000be8                               @ 0x21000be8
 */
/* net-core FUN_0100a5c8 @ 0x100a5c8 */

#include <stdint.h>

extern void sdc_assertion_fail(uint32_t group, uint32_t line);
extern int FUN_01027742(uint32_t type, uint32_t field, uint32_t value);
extern void FUN_010276e6(uintptr_t destination, uint32_t stride, uint32_t type,
                         uint32_t field, uint32_t value);

int controller_descriptor_array_encode(uintptr_t destination, uint32_t count_arg, uint32_t value_arg)
{
    uint8_t count = (uint8_t)count_arg;
    uint8_t value = (uint8_t)value_arg;
    uint16_t stride = (uint16_t)((uint16_t)(FUN_01027742(0xf7u, 5u, value) + 3) & 0xfffcu);

    if (destination != 0u) {
        if ((destination & 3u) != 0u) {
            sdc_assertion_fail(0x19u, 0x95u);
        }
        *(volatile uintptr_t *)((unsigned long)&g_21000be4) /*=0x21000be4*/ = destination;
        *(volatile uint16_t *)((unsigned long)&g_21000be8) /*=0x21000be8*/ = stride;
        for (uint16_t index = 0; index < count; ++index) {
            FUN_010276e6(*(volatile uintptr_t *)((unsigned long)&g_21000be4) /*=0x21000be4*/ +
                             (uint32_t)*(volatile uint16_t *)((unsigned long)&g_21000be8) /*=0x21000be8*/ * index,
                         stride, 0xf7u, 5u, value);
        }
    }
    return (uint32_t)stride * count;
}
