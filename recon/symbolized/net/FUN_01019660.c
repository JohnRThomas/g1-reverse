#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01019660 @ 0x01019660
 * public-name: FUN_01019660
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_work_submit                          <= FUN_0100ef88 @ 0x0100ef88
 *   sdc_buffer_payload_get                   <= FUN_010270d2 @ 0x010270d2
 *   sdc_buffer_descriptor_resolve            <= FUN_0102714a @ 0x0102714a
 * address symbols (name @ address):
 *   g_2100109c                               @ 0x2100109c
 */
/* Reconstructed net-core setup routine @ 0x01019660. */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t, uint32_t);
extern void *FUN_0100a5a0(void);
extern uint32_t FUN_0100a5b4(void);
extern void sdc_work_submit(void *, const void *, uint32_t);
extern uint32_t FUN_01026d3e(void *);
extern uint32_t FUN_01026f32(void *, uint16_t, uint32_t);
extern uint8_t *sdc_buffer_payload_get(void *);
extern void sdc_buffer_descriptor_resolve(void *, void *, void *);

void FUN_01019660(void)
{
    uint16_t auxiliary;
    void *handle;
    void *controller = FUN_0100a5a0();
    uint8_t *entry;
    uint8_t initial_flag;

    sdc_buffer_descriptor_resolve(controller, &handle, &auxiliary);
    entry = sdc_buffer_payload_get(handle);
    initial_flag = entry[0x1f];

    if (initial_flag == 0) {
        if (FUN_01026d3e(controller) == 1)
            return;
        if (FUN_01026f32(controller, (uint16_t)FUN_0100a5b4(), 1) == 0) {
            sdc_assertion_fail(0x33, 0x2ba);
            return;
        }
        if (FUN_01026d3e(controller) == 0) {
            sdc_assertion_fail(0x33, 0x2be);
            sdc_assertion_fail(0x33, 0x2ba);
            return;
        }
        entry[8] = initial_flag;
        sdc_work_submit(entry, (const void *)0x01019a9d, 6);
    } else if (FUN_01026d3e(controller) == 0) {
        sdc_assertion_fail(0x33, 0x2be);
        sdc_assertion_fail(0x33, 0x2ba);
        return;
    }

    *(volatile uint16_t *)((unsigned long)&g_2100109c) /*=0x2100109c*/ = 0;
}
