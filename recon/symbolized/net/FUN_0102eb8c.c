#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102eb8c @ 0x0102eb8c
 * public-name: FUN_0102eb8c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d8c5                           @ 0x0103d8c5
 */
/* net-core FUN_0102eb8c @ 0x102eb8c */
#include <stdint.h>

extern void assert_print(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
extern int32_t FUN_01039bb0(uint32_t, uint32_t);

void FUN_0102eb8c(int8_t irq, uint32_t priority, uint32_t flags, uint32_t unused)
{
    uint32_t encoded;
    if (flags & 1u) {
        encoded = 0;
    } else {
        encoded = priority + 2u;
        if (encoded > 7u) {
            assert_print(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d8c5) /*=0x103d8c5*/, 0x5cu, flags << 31, unused);
            irq = (int8_t)FUN_01039bb0(((unsigned long)&rodata_103d8c5) /*=0x103d8c5*/, 0x5cu);
            encoded = 0; /* physical fall-through of the fatal-report path */
        }
    }

    uint8_t value = (uint8_t)(encoded << 5);
    if (irq >= 0)
        *(volatile uint8_t *)(uintptr_t)(0xe000e400u + (uint32_t)irq) = value;
    else
        *(volatile uint8_t *)(uintptr_t)(0xe000ed14u + ((uint32_t)irq & 15u)) = value;
}
