/* net-core FUN_01033df0 @ 0x1033df0  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int FUN_01034458(unsigned int a);
extern int FUN_01034480(unsigned int a);
extern void FUN_0102e284(unsigned int a, unsigned int b, void *c, unsigned int d);

#define DAT_eb0 0x21006460u
#define DAT_eb4 0x0bad0000
#define DAT_eb8 0x2100645fu
#define DAT_ebc 0x2100645eu
#define DAT_ec0 0x2100645du
#define DAT_ec4 0x2100645cu
#define DAT_ec8 0x2100645bu
#define DAT_ecc 0x2100645au
#define DAT_ed0 0x0103e4afu
#define DAT_ed4 0x0103c05cu
#define DAT_ed8 0x41008000u
#define DAT_edc 0x4100f000u
#define DAT_ee0 0x0103e4d1u

unsigned int FUN_01033df0(void)
{
    int iStack_20;
    int iVar3 = DAT_eb4;
    unsigned char *pbVar2;
    int matched;

    iStack_20 = FUN_01034458(DAT_eb0);
    matched = 0;
    if (iStack_20 == iVar3) {
        iStack_20 = FUN_01034458(DAT_eb8);
        if (iStack_20 == iVar3) {
            iStack_20 = FUN_01034458(DAT_ebc);
            pbVar2 = (unsigned char *)DAT_ec0;
            if (iStack_20 == iVar3) {
                iStack_20 = FUN_01034458(DAT_ec0);
                if (iStack_20 == iVar3) {
                    iStack_20 = FUN_01034458(DAT_ec4);
                    if (iStack_20 == iVar3) {
                        iStack_20 = FUN_01034458(DAT_ec8);
                        if (iStack_20 == iVar3) {
                            matched = 1;
                        }
                    }
                }
            }
        }
    }

    if (matched) {
        int rv = FUN_01034480(DAT_ecc);
        if (rv == iStack_20) {
            unsigned char bVar1 = *pbVar2;
            *(volatile unsigned int *)(DAT_ed8 + 400) = (unsigned int)bVar1 | 0x80000000u;
            *(volatile unsigned int *)(DAT_edc + 0x504) = 1u << (unsigned int)bVar1;
            return 0;
        } else {
            struct { int a; unsigned int b; int c; } local;
            local.a = 3;
            local.b = DAT_ed0;
            local.c = rv;
            FUN_0102e284(DAT_ed4, 0x1840, &local, 0);
            return 0xffffffed;
        }
    } else {
        struct { int a; unsigned int b; int c; } local;
        local.a = 3;
        local.b = DAT_ee0;
        local.c = iStack_20;
        FUN_0102e284(DAT_ed4, 0x1840, &local, 0);
        return 0xffffffed;
    }
}

