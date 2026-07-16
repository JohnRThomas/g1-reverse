/* Full reconstruction of FUN_00082594 @ 0x82594, exact extent 24 bytes. */
#include <stdint.h>

extern uintptr_t FUN_00081aca(uint32_t, uint32_t, uint32_t, uint32_t);

uint32_t FUN_00082594(uint32_t arg0, uint32_t ignored, uint32_t arg2,
                      uint32_t arg3)
{
    (void)ignored;
    uintptr_t object = FUN_00081aca(arg0, 4, arg2, arg3);
    if (object == 0)
        return 0;
    return (__atomic_load_n((uint32_t *)(object + 0x118), __ATOMIC_ACQUIRE) >> 5) & 1;
}
