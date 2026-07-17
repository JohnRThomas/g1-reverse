/* net-core FUN_0102d69c @ 0x0102d69c */
#include <stdint.h>

typedef void (*endpoint_cb)(uint32_t);

extern int FUN_010354bc(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                        uint32_t, uint32_t);

void FUN_0102d69c(uint32_t state, uint32_t record, uint32_t data,
                   uint32_t length)
{
    int result = FUN_010354bc(
        record, state + 0xe0, data, 0xffffffffu, length,
        *(uint32_t *)(uintptr_t)(state + 0x1ac), 0x0103a749u);
    if (result == 0) {
        endpoint_cb callback;
        *(uint8_t *)(uintptr_t)(record + 0x64) = 1;
        callback = *(endpoint_cb *)(uintptr_t)(state + 0x1a8);
        if (callback != 0) {
            callback(record);
        }
    }
}
