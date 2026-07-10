/* net-core FUN_01031820 @ 0x1031820  (parity 300 trials PROVEN) */

extern void FUN_0102e000(void);
extern void FUN_0102e284(unsigned int a, unsigned int b, void *c, unsigned int d);
extern void FUN_0102f4ec(unsigned int a);
extern void FUN_01031814(void);

#define DAT_01031844 0x0103e16au
#define DAT_01031848 0x0103c064u

int FUN_01031820(unsigned int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    struct { unsigned int a; unsigned int b; } s;

    FUN_0102e000();
    s.a = 2;
    s.b = DAT_01031844;
    FUN_0102e284(DAT_01031848, 0x1040, &s, 0);
    FUN_0102f4ec(0);

    for (;;) {
        FUN_01031814();
    }
}

