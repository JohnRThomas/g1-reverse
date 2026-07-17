/* readable reconstruction; identity: FUN_0101fbc8 @ 0x0101fbc8
 * public-name: FUN_0101fbc8
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   sdc_assertion_fail                       <= FUN_01008d00 @ 0x01008d00
 *   controller_typed_handle_lookup           <= FUN_01009d18 @ 0x01009d18
 * address symbols (name @ address):
 *   g_net_cb_handler_fn                      @ 0x21000528
 *   g_net_cb_registered_flag                 @ 0x2100052c
 */
/* net-core FUN_0101fbc8 @ 0x101fbc8 */
#include <stdint.h>
extern void sdc_assertion_fail(uint32_t, uint32_t);
extern int controller_typed_handle_lookup(uint16_t, uint32_t);
extern void FUN_01009d64(uint32_t, uint32_t);

void FUN_0101fbc8(uint32_t context, const uint8_t *state)
{
    void (*dispatch)(uint32_t, uint32_t) =
        *(void (**)(uint32_t, uint32_t))0x2100052c;
    uint16_t (*allocate)(void) = *(uint16_t (**)(void))0x21000528;

    FUN_01009d64(context, 6);
    if (dispatch == 0 || state[0x38] == 0)
        return;

    if (allocate == 0)
        sdc_assertion_fail(0x0d, 0x245);
    uint32_t ready;
    do {
        uint16_t handle = allocate();
        ready = (uint32_t)controller_typed_handle_lookup(handle, 9);
        if (ready != 0)
            break;
        sdc_assertion_fail(0x0d, 0x248);
    } while (1);

    dispatch(ready, 0x3e);
}
