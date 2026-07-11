/* Full ABI-faithful reconstruction bt_send_enabled @ 0x17e3c. */
#include <stdint.h>

extern void DEBUG_PRINT(uintptr_t format, ...);
extern void FUN_00019c70(uintptr_t format, ...);

void bt_send_enabled(int32_t error)
{
    if (*(volatile int32_t *)0x2000230cu > 2) {
        if (*(volatile uint32_t *)0x20007554u == 0)
            DEBUG_PRINT(0x0009a143u, 0x0009a2cdu, error);
        else
            FUN_00019c70(0x0009a143u, 0x0009a2cdu, error);
    }

    *(volatile uint8_t *)(*(volatile uintptr_t *)0x20006a30u + 0x366u) =
        error == 0;
}
