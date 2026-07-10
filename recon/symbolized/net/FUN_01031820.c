#include "g1_net_symbols.h"
/* net-core FUN_01031820 @ 0x1031820  (parity 300 trials PROVEN) */

extern void FUN_0102e000(void);
extern void FUN_0102e284(unsigned int a, unsigned int b, void *c, unsigned int d);
extern void FUN_0102f4ec(unsigned int a);
extern void FUN_01031814(void);

#define DAT_01031844 "ndling\n" /*=0x103e16a*/
#define DAT_01031848 ((uintptr_t)&rodata_103c064) /*=0x103c064*/

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

