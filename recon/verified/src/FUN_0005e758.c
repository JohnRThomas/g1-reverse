/* Reconstructed FUN_0005e758 @ 0x5e758  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef void (*fnptr)(unsigned int, unsigned int);
extern void FUN_0007e2ec(uint32_t, uint32_t);
extern void FUN_0007e2fa(unsigned long, ...);

void FUN_0005e758(unsigned short param_1, fnptr param_2, unsigned int param_3)
{
    if (param_2 == 0) {
        FUN_0007e2fa(0x00099cbdU, 0x000f52c0U, 0x000f5268U, 0xb3U);
        FUN_0007e2ec(0x000f5268U, 0xb3U);
        return;
    }
    uintptr_t base = 0x2000af4cUL;
    unsigned short m1 = *(volatile unsigned short*)(base + 0xe);
    if ((m1 & param_1) != 0) {
        param_2((unsigned int)base, param_3);
    }
    unsigned short m2 = *(volatile unsigned short*)(base + 0x6a);
    if ((m2 & param_1) != 0) {
        param_2(0x2000afa8UL, param_3);
        return;
    }
}
