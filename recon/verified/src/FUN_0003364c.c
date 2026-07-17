/* Reconstructed FUN_0003364c @ 0x0003364c, extent 0x00000054.
 * Readable identity: packet_transport_send_byte.
 * Raw/address backmap: packet_transport_send_byte <= FUN_0003364c @ 0x0003364c.
 * CFG_VERIFY_CALL_ARITIES=1,2,3,2
 */
#include <stdint.h>

extern int DEBUG_PRINT(uintptr_t format, ...);
extern void FUN_00074844(uint32_t delay, uint32_t flags);

int FUN_0003364c(void *transport, const uint8_t *value, const void *required)
{
    uint32_t *vtable;
    int result;

    if (transport == 0 || value == 0 || required == 0)
        return -1;
    vtable = *(uint32_t **)((uint8_t *)transport + 8);
    result = ((int (*)(uint32_t))vtable[1])(10000U);
    if (result != 0) {
        DEBUG_PRINT(0x000a7af2UL);
        return -2;
    }
    FUN_00074844(0x4000U, 0U);
    ((void (*)(void *, uint32_t))vtable[7])(transport, *value);
    FUN_00074844(3277U, 0U);
    return 0;
}
