#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_0102946c @ 0x0102946c
 * public-name: FUN_0102946c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   controller_typed_handle_lookup           <= FUN_01009d18 @ 0x01009d18
 */
/* net-core FUN_0102946c @ 0x0102946c
 * Readable role: apply a byte-valued update to an active handle entry.
 *
 * Raw/address provenance:
 *   FUN_0101f8cc @ 0x0101f8cc -> controller-state snapshot
 *   FUN_01009d18 @ 0x01009d18 -> typed handle lookup
 *   FUN_0101e090 @ 0x0101e090 -> entry-to-active-context lookup
 *   FUN_0101e15c @ 0x0101e15c -> context state-transition tail
 *   code/ownership [0x0102946c, 0x010294a2)
 *   sole direct owner: FUN_010294a2 tail branch @ 0x010294aa
 */
#include <stdint.h>

extern uint64_t FUN_0101f8cc(void);
extern void *controller_typed_handle_lookup(uint16_t handle, unsigned type);
extern void *FUN_0101e090(void *entry);
extern unsigned FUN_0101e15c(void *context, void *entry, uint8_t value);

enum {
    CONTROLLER_HANDLE_UPDATES_READY = 0x20000000U,
    HANDLE_ENTRY_TYPE = 8,
    UPDATE_STATUS_INVALID_STATE = 0x0c,
    UPDATE_STATUS_HANDLE_NOT_FOUND = 2
};

unsigned FUN_0102946c(uint16_t handle, uint8_t value)
{
    uint32_t controller_state = (uint32_t)FUN_0101f8cc();
    if ((controller_state & CONTROLLER_HANDLE_UPDATES_READY) == 0)
        return UPDATE_STATUS_INVALID_STATE;

    void *entry = controller_typed_handle_lookup(handle, HANDLE_ENTRY_TYPE);
    if (entry == 0)
        return UPDATE_STATUS_HANDLE_NOT_FOUND;

    void *context = FUN_0101e090(entry);
    if (context == 0)
        return UPDATE_STATUS_INVALID_STATE;

    return FUN_0101e15c(context, entry, value);
}
