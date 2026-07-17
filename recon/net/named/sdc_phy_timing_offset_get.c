/* readable reconstruction; identity: FUN_0100d58c @ 0x0100d58c
 * public-name: sdc_phy_timing_offset_get
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   sdc_phy_timing_offset_get                <= FUN_0100d58c @ 0x0100d58c
 */
/* FUN_0100d58c @ 0x0100d58c: select an operation timing constant. */
#include <stdnoreturn.h>
#include <stdint.h>

extern noreturn void sdc_assertion_fail(unsigned int module, unsigned int line);

uint32_t sdc_phy_timing_offset_get(int short_interval, uint32_t operation)
{
    switch (operation) {
    case 1:
        return short_interval == 0 ? 0x4e2u : 0x9c4u;
    case 2:
        return 0x9c4u;
    case 4:
    case 8:
        return 0xea6u;
    default:
        sdc_assertion_fail(0x29u, 0x270u);
    }
}
