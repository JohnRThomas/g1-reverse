#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0100ac34 @ 0x0100ac34
 * public-name: FUN_0100ac34
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_work_update_or_enqueue        <= FUN_0100efc8 @ 0x0100efc8
 *   sdc_llcp_note_unsupported_pdu            <= FUN_01020500 @ 0x01020500
 * address symbols (name @ address):
 *   g_net_radio_drv_ctx                      @ 0x21000c48
 */
/* net-core FUN_0100ac34 @ 0x100ac34 */
#include <stdint.h>

extern void sdc_llcp_note_unsupported_pdu(void);
extern void FUN_0101ff4c(void);
extern void controller_work_update_or_enqueue(void *, const void *, unsigned);

void FUN_0100ac34(void)
{
    volatile uint8_t *const state = (volatile uint8_t *)((unsigned long)&g_net_radio_drv_ctx) /*=0x21000c48*/;
    sdc_llcp_note_unsupported_pdu();
    FUN_0101ff4c();
    ((void (*)(uint16_t, unsigned))*(volatile uintptr_t *)(state + 0x34))(
        *(volatile uint16_t *)(state + 0x30), 0);
    if (state[0x18] != 0) {
        *(volatile uint32_t *)(state + 0x0c) = *(volatile uint32_t *)(state + 0x00);
        *(volatile uint32_t *)(state + 0x10) = *(volatile uint32_t *)(state + 0x04);
        *(volatile uint32_t *)(state + 0x14) = *(volatile uint32_t *)(state + 0x08);
        controller_work_update_or_enqueue((void *)(state + 0x19), (const void *)0x0100b381U, 2);
    }
    ((void (*)(uint8_t, uint8_t))*(volatile uintptr_t *)(state + 0x40))(
        state[0x3e], state[0x3d]);
    state[0x44] = 0;
}
