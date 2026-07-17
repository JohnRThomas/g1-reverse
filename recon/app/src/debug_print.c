/* Reconstructed debug_print @ 0x19c70  (parity: 300/300 trials, PROVEN) */

#include <stdarg.h>
#include <stdint.h>

extern uintptr_t FUN_000181fc(void);
extern void FUN_00086c78(void *dst, int val, unsigned int len);
extern void FUN_00077c30(void *dst, unsigned int size, unsigned int fmt, va_list args);
extern void FUN_00019bfc(void *buf);
extern void thunk_FUN_00072880(uintptr_t arg);

void debug_print(unsigned int format, ...)
{
    va_list arguments;
    va_start(arguments, format);

    uintptr_t context = FUN_000181fc();
    unsigned char message[200];

    FUN_00086c78(message, 0, sizeof(message));
    FUN_00077c30(message, sizeof(message), format, arguments);
    FUN_00019bfc(message);
    message[0] = 0;

    if ((*(volatile unsigned char *)(context + 0x248) == 0) &&
        (*(volatile unsigned int *)(context + 0x220) == 0)) {
        *(volatile unsigned int *)0x20007550UL = 1;
        thunk_FUN_00072880(context + 0x218);
    }
    va_end(arguments);
}
