/* Reconstructed FUN_0003f2a8 @ 0x3f2a8  full 0xca-byte body */
#include <stdint.h>

extern int FUN_00023ee0(void);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern void FUN_00043e90(int, uint32_t, int, int, int, int, int,
                         int, int, int, int, int);

void FUN_0003f2a8(void)
{
    int a, b, c, d;
    uint32_t format;

    if (FUN_00023ee0() == 6) {
        a = FUN_0007d3ee();
        b = FUN_0007d446();
        c = FUN_0007d3ee();
        d = FUN_0007d446();
        FUN_00043e90(0, UINT32_C(0x000aa056), 0,
                     a + 0xa8, b + 0x37, c + 0x23a, d + 0x52,
                     1, 0, 0, 0, 0);

        a = FUN_0007d3ee();
        b = FUN_0007d446();
        c = FUN_0007d3ee();
        d = FUN_0007d446();
        a += 0xb4;
        b += 0x52;
        c += 0x23a;
        d += 0x6d;
        format = UINT32_C(0x000a9da3);
    } else {
        a = FUN_0007d3ee();
        b = FUN_0007d446();
        c = FUN_0007d3ee();
        d = FUN_0007d446();
        a += 0x58;
        b += 0x37;
        c += 0x23a;
        d += 0x88;
        format = UINT32_C(0x000aa02b);
    }

    FUN_00043e90(0, format, 0, a, b, c, d, 1, 0, 0, 0, 0);
}
