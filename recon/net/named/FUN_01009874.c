/* readable reconstruction; identity: FUN_01009874 @ 0x01009874
 * public-name: FUN_01009874
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_slot_offsets_recompute        <= FUN_010095c0 @ 0x010095c0
 * address symbols (name @ address):
 *   g_net_bump_alloc_state                   @ 0x21000ba8
 *   g_net_bump_alloc_cursor                  @ 0x21000bac
 *   g_net_bump_alloc_offset                  @ 0x21000bb0
 */
/* net-core FUN_01009874 @ 0x1009874  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t a, uint32_t b);
extern void controller_slot_offsets_recompute(void);

int32_t FUN_01009874(void)
{
    volatile uint8_t * const p1 = (uint8_t *)0x21000ba8;
    volatile uint32_t * const p2 = (uint32_t *)0x21000bb0;
    volatile uint32_t * const p3 = (uint32_t *)0x21000bac;
    int32_t iVar1;

    if (*p1 != 1 && *p1 != 3) {
        sdc_assertion_fail(0x17, 0x146);
    }

    if (*p1 == 3) {
        if (*p2 != *p3) {
            sdc_assertion_fail(0x17, 0x149);
        }
        controller_slot_offsets_recompute();
        *p1 = 4;
        iVar1 = 0;
    } else {
        *p1 = 2;
        iVar1 = (int32_t)*p3;
    }
    return iVar1;
}
