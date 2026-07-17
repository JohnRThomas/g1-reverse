/* readable reconstruction; identity: FUN_0101fbc8 @ 0x0101fbc8
 * public-name: FUN_0101fbc8
 * durable-map: recon/catalogs/function_names_net.json
 * address symbols (name @ address):
 *   g_net_cb_handler_fn                      @ 0x21000528
 *   g_net_cb_registered_flag                 @ 0x2100052c
 */
/* net-core FUN_0101fbc8 @ 0x101fbc8 */
#include <stdint.h>
extern void FUN_01008d00(uint32_t, uint32_t);
extern int FUN_01009d18(uint16_t, uint32_t);
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
        FUN_01008d00(0x0d, 0x245);
    uint32_t ready;
    do {
        uint16_t handle = allocate();
        ready = (uint32_t)FUN_01009d18(handle, 9);
        if (ready != 0)
            break;
        FUN_01008d00(0x0d, 0x248);
    } while (1);

    dispatch(ready, 0x3e);
}
