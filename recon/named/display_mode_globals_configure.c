/* readable reconstruction; identity: FUN_0004372c @ 0x0004372c
 * public-name: display_mode_globals_configure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   display_mode_globals_configure           <= FUN_0004372c @ 0x0004372c
 * address symbols (name @ address):
 *   rodata_aa951                             @ 0x000aa951
 *   rodata_aad1a                             @ 0x000aad1a
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0004372c @ 0x0004372c, extent 0xc8.
 * Readable identity: display_mode_globals_configure.
 * Raw/address backmap: display_mode_globals_configure <= FUN_0004372c @ 0x0004372c.
 * CFG_VERIFY_CALL_ARITIES=2
 */
#include <stdint.h>

extern void log_message(uintptr_t format, ...);
extern void debug_print(uintptr_t format, ...);

int display_mode_globals_configure(unsigned mode, ...)
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
                debug_print(0x000aa951UL, 0x000aad1aUL);
            else
                log_message(0x000aa951UL, 0x000aad1aUL);
        }
        break;
    }
    return -1;
}
