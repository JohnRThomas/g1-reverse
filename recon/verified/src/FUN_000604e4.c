/* Full reconstruction FUN_000604e4 @ 0x000604e4 (114-byte exact extent). */
#include <stdint.h>
#include <cmsis_gcc.h>

extern void FUN_0007e2fa(uintptr_t, uintptr_t, uintptr_t, uint32_t);
extern void FUN_0007e2ec(uintptr_t, uint32_t) __attribute__((noreturn));

int FUN_000604e4(uint8_t *device, uint8_t type, uint32_t owner)
{
    uint8_t *state = *(uint8_t **)(device + 0x10);
    if (type >= 4) {
        FUN_0007e2fa(0x00099cbdu, 0x000f5b16u, 0x000f5ad9u, 0x15du);
        FUN_0007e2ec(0x000f5ad9u, 0x15du);
    }

    uint32_t saved = __get_BASEPRI();
    __set_BASEPRI_MAX(0x20u);
    __ISB();
    uint32_t offset = 12u * type;
    uint32_t current = *(volatile uint32_t *)(state + offset + 0x88) & 0xc0u;
    if (current != 0 && current != owner) {
        __set_BASEPRI(saved);
        __ISB();
        return -1;
    }

    *(volatile uint32_t *)(state + offset + 0x88) = 1;
    __set_BASEPRI(saved);
    __ISB();
    void (*callback)(void) = *(void (**)(void))(*(uint8_t **)(device + 4) + offset + 4);
    callback();
    return 0;
}
