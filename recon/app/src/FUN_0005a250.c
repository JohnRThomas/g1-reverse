/* Reconstructed FUN_0005a250 @ 0x5a250  (parity: 300/300 trials, PROVEN) */

extern int FUN_0005307c(unsigned int a, unsigned int b);
extern void FUN_00082a42(unsigned int a, unsigned int b, void *c);

void FUN_0005a250(void)
{
    struct { unsigned int f0; unsigned int f1; unsigned int f2; } s;
    int r;
    r = FUN_0005307c(0x20006380UL, 0x10);
    if (r != 0) {
        s.f0 = 3;
        s.f1 = 0x000f4849UL;
        s.f2 = r;
        FUN_00082a42(0x00088128UL, 0x1840, &s);
    }
}

