/* Reconstructed FUN_00065324 @ 0x65324  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_0007e2ec(void);
extern void FUN_0007e2fa(void);
extern void FUN_00065000(void);

void FUN_00065324(int param_1, int param_2)
{
    if (*(volatile uint8_t*)0x2000b320 == 0) {
        FUN_0007e2fa();
        FUN_0007e2ec();
    }
    FUN_00065000();
}

