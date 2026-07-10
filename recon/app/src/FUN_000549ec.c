/* Reconstructed FUN_000549ec @ 0x549ec  (parity: 300/300 trials, PROVEN) */

extern void FUN_00080ea2(unsigned int a, unsigned int b, void *c);
extern void FUN_00080e6a(unsigned int a, unsigned int b, unsigned int c, unsigned int d);
extern void FUN_000548b8(void);

unsigned int FUN_000549ec(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    volatile unsigned char *base = (volatile unsigned char*)0x20002000UL;
    unsigned char flag = base[7];
    if (flag == 0) {
        struct { unsigned int f0; unsigned int f1; } s;
        s.f0 = 2;
        s.f1 = 0x000f322eUL;
        FUN_00080ea2(0x00088138UL, 0x10c0, &s);
    } else {
        FUN_00080e6a(0x20002000UL + 0xd4, 8, param_3, flag);
        FUN_000548b8();
    }
    return 0;
}

