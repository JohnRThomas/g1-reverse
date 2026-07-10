#include "g1_net_symbols.h"
/* net-core FUN_0102dcf4 @ 0x102dcf4  (parity 300 trials PROVEN) */

typedef unsigned int uint;
extern unsigned int FUN_0102dc90(unsigned int);
extern void FUN_0102e23c(int*, unsigned int, unsigned int);
extern void FUN_01037c64(unsigned int, unsigned int);
extern void FUN_01039bb0(unsigned int,unsigned int);
extern void FUN_01039bbe(unsigned int,unsigned int,unsigned int);
extern int FUN_0103a294(unsigned int);

unsigned int FUN_0102dcf4(int param_1, int param_2)
{
    int *piVar5 = (int *)((uintptr_t)&rodata_103c0ec) /*=0x103c0ec*/; /* DAT_0102ddac */
    int *piVar1 = (int *)((uintptr_t)&rodata_103c0fc) /*=0x103c0fc*/; /* DAT_0102dda8 */

    if ((unsigned int)((int)piVar1 - (int)piVar5) < 0xa0) {
        int iVar2 = FUN_0103a294(((uintptr_t)&g_net_cb_list_lock) /*=0x2100466c*/); /* DAT_0102ddb8 */
        if (iVar2 != 0) {
            return 0;
        }
        unsigned int uVar3 = 0;
        unsigned int uVar6 = 0;
        for (; piVar5 <= piVar1; piVar5 = piVar5 + 4) {
            if (piVar1 <= piVar5) {
                if (param_1 != 0) {
                    while (uVar3 != 0) {
                        uVar3 = FUN_0102dc90(uVar3);
                        if (param_2 != 0) {
                            FUN_01037c64(0x148, 0);
                        }
                    }
                    return 0;
                }
                return uVar3;
            }
            if ((char)piVar5[3] != 0) {
                void (*cb0)(int*) = *(volatile void(**)(int*))(*piVar5 + 0xc);
                if (cb0 != 0) {
                    cb0(piVar5);
                }
                int (*cb1)(int*) = *(volatile int(**)(int*))(*piVar5 + 0x10);
                if (cb1 == 0 || cb1(piVar5) == 0) {
                    FUN_0102e23c(piVar5, *(volatile unsigned int*)piVar5[1], 4);
                } else {
                    uVar3 = uVar3 | (1u << (uVar6 & 0xff));
                }
                uVar6 = uVar6 + 1;
            }
        }
        FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, " type: %u" /*=0x103d5d7*/, 0x126);
        FUN_01039bb0(" type: %u" /*=0x103d5d7*/, 0x126);
        __builtin_unreachable();
    } else {
        FUN_01039bbe("acking error (context area might be not valid)" /*=0x103d2a7*/, " type: %u" /*=0x103d5d7*/, 0x119);
        FUN_01039bb0(" type: %u" /*=0x103d5d7*/, 0x119);
        __builtin_unreachable();
    }
}

