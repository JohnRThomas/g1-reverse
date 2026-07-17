/* readable reconstruction; identity: FUN_0101e0a4 @ 0x0101e0a4
 * public-name: controller_handle_update_state_apply
 * durable-map: recon/catalogs/function_names_net.json
 */
/* net-core controller_handle_update_state_apply @ 0x0101e0a4.
 * Exact reachable extent [0x0101e0a4,0x0101e10c), including three fatal
 * tails; 0x0101e10c begins a separate pushed function. No literal pool.
 * Raw backmap: FUN_0101e0a4@0x0101e0a4. */
#include <stdint.h>

extern void sdc_assertion_fail(unsigned module, unsigned line)
    __attribute__((noreturn)); /* FUN_01008d00@0x01008d00 */
extern void *controller_typed_handle_lookup(uint16_t handle, unsigned type); /* FUN_01009d18@0x01009d18 */
extern void controller_entry_links_release(void *target, void *entry); /* FUN_0101df84@0x0101df84 */

enum {
    UPDATE_CONTEXT_STATE_OFFSET = 0xc6,
    UPDATE_CONTEXT_GUARD_OFFSET = 0x104,
    UPDATE_CONTEXT_VALUE_OFFSET = 0x14a,
    UPDATE_CONTEXT_KIND_OFFSET = 0x14b,
    UPDATE_ENTRY_HANDLE_OFFSET = 0x17e,
    UPDATE_HANDLE_TYPE = 7,
    UPDATE_STATE_READY = 0x2a,
    UPDATE_STATE_NO_VALUE = 0x2b,
    UPDATE_STATE_APPLIED = 0x30,
    UPDATE_KIND_APPLIED = 0x1f,
    UPDATE_STATUS_OK = 0,
    UPDATE_STATUS_INVALID_STATE = 0x0c,
};

unsigned controller_handle_update_state_apply(volatile uint8_t *context,
                                              uint8_t *entry,
                                              uint8_t value)
{
    if (context == 0)
        sdc_assertion_fail(0x1a, 0xb1);
    if (context[UPDATE_CONTEXT_STATE_OFFSET] != UPDATE_STATE_READY)
        return UPDATE_STATUS_INVALID_STATE;

    if (value == 0) {
        context[UPDATE_CONTEXT_STATE_OFFSET] = UPDATE_STATE_NO_VALUE;
    } else {
        context[UPDATE_CONTEXT_VALUE_OFFSET] = value;
        context[UPDATE_CONTEXT_KIND_OFFSET] = UPDATE_KIND_APPLIED;
        context[UPDATE_CONTEXT_STATE_OFFSET] = UPDATE_STATE_APPLIED;
        if (entry != 0) {
            uint16_t handle = *(uint16_t *)(entry + UPDATE_ENTRY_HANDLE_OFFSET);
            void *target = controller_typed_handle_lookup(
                handle, UPDATE_HANDLE_TYPE);
            if (target == 0)
                sdc_assertion_fail(0x1a, 0xd3);
            controller_entry_links_release(target, entry);
        }
    }

    if ((int8_t)context[UPDATE_CONTEXT_GUARD_OFFSET] < 0)
        sdc_assertion_fail(0x1a, 0xd8);
    return UPDATE_STATUS_OK;
}
