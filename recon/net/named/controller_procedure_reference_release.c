/* readable reconstruction; identity: FUN_0100f7b0 @ 0x0100f7b0
 * public-name: controller_procedure_reference_release
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_procedure_reference_release   <= FUN_0100f7b0 @ 0x0100f7b0
 */
/* net-core FUN_0100f7b0 @ 0x100f7b0  (CFG-directed candidate) */
/* net-core FUN_0100f7b0 @ 0x0100f7b0
 * Readable role: release one controller procedure reference and assert on underflow.
 * Address back-map: sdc_assertion_fail = FUN_01008d00 @ 0x01008d00.
 */
#include <stdint.h>

extern void sdc_assertion_fail(uint32_t file_id, uint32_t line,
                               const void *context, int32_t value);

void controller_procedure_reference_release(void *owner)
{
    uint8_t *controller = *(uint8_t **)((uint8_t *)owner + 4);
    int8_t references = (int8_t)(controller[0x104] - 1U);

    controller[0x104] = (uint8_t)references;
    if (references < 0) {
        sdc_assertion_fail(0x4aU, 0x35U, controller + 0xa8, references);
    }
}
