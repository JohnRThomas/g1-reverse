/* Reconstructed FUN_00065190 @ 0x65190  (parity: 300/300 trials, PROVEN)
 * Readable namespace target: g1_nrfx_clock_init_checked.
 */

#include <stdint.h>

extern void FUN_0007e2fa(unsigned long, ...);
extern __attribute__((noreturn)) void FUN_0007e2ec(uint32_t, uint32_t);

uint32_t FUN_00065190(uintptr_t event_handler)
{
    volatile uintptr_t *handler = (volatile uintptr_t *)0x2000b31cUL;
    volatile uint8_t *initialized = (volatile uint8_t *)0x2000b320UL;

    if (event_handler == 0) {
        FUN_0007e2fa(0x00099cbdUL, 0x000f6abfUL, 0x000f6a4eUL, 0x115);
        FUN_0007e2ec(0x000f6a4eUL, 0x115);
    }

    if (*initialized != 0) {
        return 0x0bad000cUL;
    }

    *handler = event_handler;
    *initialized = 1;
    return 0x0bad0000UL;
}
