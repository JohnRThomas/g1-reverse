/* Reconstructed FUN_0002bdf0 @ 0x0002bdf0, extent 0x00000060.
 * Readable identity: active_mode_shutdown.
 * Raw/address backmap: active_mode_shutdown <= FUN_0002bdf0 @ 0x0002bdf0.
 * CFG_VERIFY_CALL_ARITIES=4,1,4,1
 */
#include <stdint.h>

extern int FUN_00019c70(uintptr_t format, ...);
extern int DEBUG_PRINT(uintptr_t format, ...);

int FUN_0002bdf0(uint8_t *device)
{
    volatile int *const log_level = (volatile int *)0x2000230cUL;
    volatile int *const log_backend = (volatile int *)0x20007554UL;
    uint8_t phase = device[0xfe6];

    if ((phase & 0xfbU) != 1U)
        return 0;
    device[0xfe6] = 3U;
    if (*log_level > 1) {
        if (*log_backend != 0)
            FUN_00019c70(0x000a24ebUL, 0x000a2505UL);
        else
            DEBUG_PRINT(0x000a24ebUL, 0x000a2505UL);
    }
    ((void (*)(void *))(*(uint32_t *)(device + 0xb74)))(device + 0xb6c);
    if (*log_level > 1) {
        if (*log_backend != 0)
            FUN_00019c70(0x000a24f9UL, 0x000a2505UL);
        else
            DEBUG_PRINT(0x000a24f9UL, 0x000a2505UL);
    }
    device[0xfe6] = 0U;
    return 0;
}
