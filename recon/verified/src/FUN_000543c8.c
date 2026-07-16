/* Reconstructed FUN_000543c8 @ 0x543c8, exact extent 10 bytes. */
#include <stdint.h>

typedef uint32_t (*dispatch_fn_t)(void);

uint32_t FUN_000543c8(void)
{
    uintptr_t object = *(volatile uintptr_t *)0x20002168u;
    dispatch_fn_t dispatch = *(dispatch_fn_t volatile *)(object + 0x14u);
    return dispatch();
}
