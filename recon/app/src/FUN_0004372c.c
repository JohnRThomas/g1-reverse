/* Reconstructed FUN_0004372c @ 0x0004372c, extent 0xc8.
 * Readable identity: display_mode_globals_configure.
 * Raw/address backmap: display_mode_globals_configure <= FUN_0004372c @ 0x0004372c.
 * CFG_VERIFY_CALL_ARITIES=2
 */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);

int FUN_0004372c(unsigned mode, ...)
{
    volatile uint32_t *const first = (volatile uint32_t *)0x2000a014UL;
    volatile uint32_t *const second = (volatile uint32_t *)0x2000a010UL;
    volatile uint32_t *const third = (volatile uint32_t *)0x2000a00cUL;
    volatile uint32_t *const fourth = (volatile uint32_t *)0x2000a008UL;
    volatile uint8_t *const fifth = (volatile uint8_t *)0x2001cdd6UL;
    volatile uint32_t *const sixth = (volatile uint32_t *)0x2000a004UL;
    volatile uint32_t *const seventh = (volatile uint32_t *)0x2000a000UL;
    volatile uint32_t *const eighth = (volatile uint32_t *)0x20009ffcUL;
    volatile uint32_t *const ninth = (volatile uint32_t *)0x20009ff8UL;
    volatile uint8_t *const tenth = (volatile uint8_t *)0x2001cdd5UL;
    __builtin_va_list ap;
    uint32_t arg1, arg2;

    __builtin_va_start(ap, mode);
    arg1 = __builtin_va_arg(ap, uint32_t);
    arg2 = __builtin_va_arg(ap, uint32_t);
    __builtin_va_end(ap);

    switch (mode) {
    case 4:
        *first = arg1;
        *second = arg2;
        *third = 0;
        *fourth = 4;
        *fifth = 0;
        *sixth = 0;
        *seventh = 0;
        *eighth = 1;
        break;
    case 5:
        *first = 0;
        *second = 0;
        *third = 3;
        *fourth = 5;
        *fifth = 0;
        *sixth = 0;
        *ninth = 0;
        *seventh = 0;
        *eighth = 1;
        break;
    case 6:
        *third = 2;
        *fourth = 6;
        *fifth = 0;
        *sixth = 0;
        *ninth = 0;
        *seventh = 0;
        *eighth = 1;
        break;
    case 8:
        *first = 0;
        *second = 0;
        *third = 0;
        *fourth = 0;
        *fifth = 0;
        *sixth = 0;
        *seventh = 0;
        *eighth = 0;
        *ninth = 0;
        *tenth = 0;
        break;
    default:
        if (*(volatile int32_t *)0x2000230cUL > 0) {
            if (*(volatile uint32_t *)0x20007554UL != 0)
                FUN_00019c70(0x000aa951UL, 0x000aad1aUL);
            else
                DEBUG_PRINT(0x000aa951UL, 0x000aad1aUL);
        }
        break;
    }
    return -1;
}
