/* readable reconstruction; identity: FUN_0003364c @ 0x0003364c
 * public-name: packet_transport_send_byte
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   packet_transport_send_byte               <= FUN_0003364c @ 0x0003364c
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 * address symbols (name @ address):
 *   rodata_a7af2                             @ 0x000a7af2   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0003364c @ 0x0003364c, extent 0x00000054.
 * Readable identity: packet_transport_send_byte.
 * Raw/address backmap: packet_transport_send_byte <= FUN_0003364c @ 0x0003364c.
 * CFG_VERIFY_CALL_ARITIES=1,2,3,2
 */
#include <stdint.h>

extern int log_message(uintptr_t format, ...);
extern void k_sleep(uint32_t delay, uint32_t flags);

int packet_transport_send_byte(void *transport, const uint8_t *value, const void *required)
{
    uint32_t *vtable;
    int result;

    if (transport == 0 || value == 0 || required == 0)
        return -1;
    vtable = *(uint32_t **)((uint8_t *)transport + 8);
    result = ((int (*)(uint32_t))vtable[1])(10000U);
    if (result != 0) {
        log_message(0x000a7af2UL);
        return -2;
    }
    k_sleep(0x4000U, 0U);
    ((void (*)(void *, uint32_t))vtable[7])(transport, *value);
    k_sleep(3277U, 0U);
    return 0;
}
