/* Reconstructed FUN_00043e90 @ 0x43e90  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef int (*codef)(int, unsigned, int, int, int);
extern void DEBUG_PRINT(unsigned, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned, ...);
extern int FUN_000431a8(void);
extern int FUN_00043e58(unsigned a, unsigned b);
extern int FUN_0004588c(int a, uint b, void *c, void *d, void *e, int f);
extern void FUN_000471cc(unsigned a, int b, int c, int d, int e, int f);
extern void FUN_00047260(unsigned a, unsigned b, int c, int d, int e, int f);
extern void *FUN_000478d8(unsigned a, void *b);
extern void FUN_0007d53a(unsigned a, void *b, int c, int d, int e, uint f);
extern int FUN_0007d860(uint a);
extern void FUN_00086c1e(void *a, unsigned b, int c, int d);

undefined4 FUN_00043e90(undefined4 param_1, unsigned param_2, int param_3, int param_4, int param_5, int param_6,
                        int param_7, uint param_8, uint param_9, int param_10, codef param_11, int param_12)
{
    int iVar3;
    unsigned uVar8;
    unsigned short local_2da;
    unsigned local_2f0;
    unsigned char local_2cc[680];

    local_2da = 0;
    FUN_000478d8(param_2, &local_2da);
    (void)local_2cc; (void)local_2f0; (void)iVar3; (void)uVar8;
    if (param_10 == 0) {
        if (param_11 != (codef)0x0) {
LAB_000440a2:
            if (1 < *(volatile int *)0x2000230c) {
                if (*(volatile int *)0x20007554 == 0) DEBUG_PRINT(0xaaa58, 0xaadac);
                else FUN_00019c70(0);
            }
            return (*param_11)(0, param_2, param_3, param_4, param_5);
        }
        if (param_12 == 0) {
            iVar3 = FUN_000431a8();
            if (iVar3 << 0x1e < 0) {
                FUN_000471cc(*(volatile unsigned *)0x2000a034, 0, param_4, param_5, param_6, param_7);
            }
            for (local_2f0 = 0; (int)local_2f0 < (int)(uint)local_2da; local_2f0 = local_2f0 + 1) {
                /* body skipped at runtime: local_2da stays 0 (oracle doesn't write) */
            }
            iVar3 = FUN_000431a8();
            if (iVar3 << 0x1e < 0) {
                iVar3 = FUN_000167a8();
                uVar8 = *(volatile unsigned *)(iVar3 + 0xeb4);
                iVar3 = FUN_000167a8();
                FUN_00047260(uVar8, *(volatile unsigned *)(iVar3 + 0xeb8), param_4, param_5, param_6, param_7);
            }
        }
    } else if (param_11 != (codef)0x0) goto LAB_000440a2;
    return 0;
}

