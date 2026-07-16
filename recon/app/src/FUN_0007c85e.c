/* Full reconstruction FUN_0007c85e @ 0x7c85e (exact extent 14 bytes). */
#include <stdint.h>
typedef int (*transfer_callback_t)(uint8_t *, void *, uint32_t, uint32_t);

int FUN_0007c85e(uint8_t *object, void *parts, uint32_t count, uint32_t operation)
{
    uint8_t *vtable = *(uint8_t **)(object + 8);
    transfer_callback_t callback = *(transfer_callback_t *)(vtable + 8);
    return callback(object, parts, count, operation);
}
