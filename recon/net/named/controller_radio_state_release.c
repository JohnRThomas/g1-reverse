/* readable reconstruction; identity: FUN_0100a7cc @ 0x0100a7cc
 * public-name: controller_radio_state_release
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_radio_state_release           <= FUN_0100a7cc @ 0x0100a7cc
 */
/* net-core FUN_0100a7cc @ 0x100a7cc  (CFG-directed candidate) */

#include <stdint.h>
extern int FUN_0102a1e2(void *state);
extern int sdc_assertion_fail(uint32_t group, uint32_t line);
void controller_radio_state_release(void)
{
    volatile uint8_t *state = (volatile uint8_t *)0x21000bf4u;
    int status = FUN_0102a1e2((void *)state);
    if (status != 0) {
        status = sdc_assertion_fail(0x1du, 0x30u);
    }
    state[1] = (uint8_t)status;
}
