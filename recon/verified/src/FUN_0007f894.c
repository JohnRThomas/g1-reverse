/* Full reconstruction FUN_0007f894 @ 0x7f894, exact extent 50 bytes. */
#include <stdint.h>

typedef void (*event_callback_t)(uintptr_t context, const uint32_t *payload,
                                 int32_t error, uint32_t length,
                                 uint32_t event);

uint32_t FUN_0007f894(uint32_t event, uintptr_t object,
                      const volatile uint16_t *payload, uint32_t length)
{
    uint32_t packed = 0;
    uint32_t callback_value = length;
    int32_t error = 0;
    event_callback_t callback =
        *(event_callback_t volatile *)(object + 0x1cu);

    if (callback != 0) {
        if (length == 4u) {
            packed = payload[0];
            callback_value = payload[1];
            packed |= callback_value << 16;
        } else {
            error = -22;
        }
        callback(object - 8u, &packed, error, callback_value, event);
    }

    return 1;
}
