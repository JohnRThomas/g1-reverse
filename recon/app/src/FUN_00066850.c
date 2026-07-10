/* Reconstructed FUN_00066850 @ 0x66850  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000500ac(int);
extern int FUN_0006666c(int,int);
extern int FUN_00066784(int);
extern int FUN_000667e0(void);

unsigned int FUN_00066850(unsigned int *param_1)
{
    volatile int *piVar1 = (volatile int *)0x2000b348;

    if ((*(char *)((int)param_1 + 0x29) == '\0') || (*(char *)((int)param_1 + 0x2a) == '\0')) {
        if (param_1[1] == 0xff) return 0x0bad0004;
        if (param_1[2] == 0xff) return 0x0bad0004;
        if (param_1[3] == 0xff) return 0x0bad0004;
        if (param_1[4] != 0xe) return 0x0bad0004;
        if (param_1[1] != 0x11) return 0x0bad0004;
        if (param_1[2] != 0x12) return 0x0bad0004;
        if (param_1[3] != 0xd) return 0x0bad0004;
        if ((param_1[5] != 0xff) && (param_1[5] != 0xf)) return 0x0bad0004;
        if ((param_1[6] != 0xff) && (param_1[6] != 0x10)) return 0x0bad0004;
        if (*(char *)((int)param_1 + 0x29) == '\0') {
            FUN_0006666c(0x11, 3);
            FUN_0006666c(param_1[2], 3);
            FUN_0006666c(param_1[3], 3);
            FUN_0006666c(param_1[4], 3);
            if (param_1[5] != 0xff) FUN_0006666c(param_1[5], 3);
            if (param_1[6] != 0xff) FUN_0006666c(param_1[6], 3);
        }
        if (*(char *)((int)param_1 + 0x2a) == '\0') {
            FUN_00066784((int)(param_1 + 1));
        }
    }
    *(volatile int *)(0x2000b348 + 0x34) = param_1[9];
    *(volatile unsigned char *)(0x2000b348 + 0x3a) = *(unsigned char *)((int)param_1 + 0x29);
    *(volatile int *)(0x5002b000 + 0x308) = 1;
    FUN_000667e0();
    *(volatile unsigned int *)(0x5002b000 + 0x540) = *param_1;
    *(volatile unsigned int *)(0x5002b000 + 0x544) =
         (unsigned int)*(unsigned char *)((int)param_1 + 0x1e) << 6 |
         (unsigned int)*(unsigned char *)((int)param_1 + 0x1d) << 3 |
         (unsigned int)*(unsigned char *)((int)param_1 + 0x1c) |
         (unsigned int)*(unsigned char *)((int)param_1 + 0x1f) << 7;
    {
        unsigned int uVar3;
        if (*(char *)((int)param_1 + 0x23) == '\0') {
            uVar3 = *(volatile unsigned int *)(0x5002b000 + 0x544) | 0x30000;
        } else {
            uVar3 = (*(volatile unsigned int *)(0x5002b000 + 0x544) & 0xfffdffff) | 0x10000;
        }
        *(volatile unsigned int *)(0x5002b000 + 0x544) = uVar3;
    }
    *(volatile int *)(0x5002b000 + 0x640) = 0x600;
    *(volatile unsigned int *)(0x5002b000 + 0x600) =
         (unsigned int)*(unsigned char *)((int)param_1 + 0x20) |
         (*(volatile unsigned int *)(0x5002b000 + 0x600) & 0xffff00) |
         (unsigned int)*(unsigned char *)((int)param_1 + 0x21) << 0x18 |
         (unsigned int)*(unsigned char *)((int)param_1 + 0x22) << 0x19 |
         (unsigned int)*(unsigned char *)((int)param_1 + 0x23) << 0x1c;
    if (*piVar1 != 0) {
        FUN_000500ac(0x2b);
    }
    return 0x0bad0000;
}

