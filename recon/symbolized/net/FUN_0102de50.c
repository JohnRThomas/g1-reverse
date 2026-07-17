#include "g1_net_symbols.h"
/* net-core FUN_0102de50 @ 0x102de50  (parity 300 trials PROVEN) */

extern unsigned int FUN_0102de38(void);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c);
extern void FUN_01039bb0(unsigned int a, unsigned int b);

typedef void (*fnptr)(int*, unsigned int);

void FUN_0102de50(void)
{
    unsigned int uVar2 = FUN_0102de38();
    int *piVar1 = (int *)((unsigned long)&rodata_103c0fc) /*=0x103c0fc*/;
    int *piVar3 = (int *)((unsigned long)&rodata_103c0ec) /*=0x103c0ec*/;
    while (1) {
        if (piVar1 < piVar3) {
            FUN_01039bbe(((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/, ((unsigned long)&rodata_103d5d7) /*=0x103d5d7*/, 0x1d1);
            FUN_01039bb0(((unsigned long)&rodata_103d5d7) /*=0x103d5d7*/, 0x1d1);
        }
        if (piVar1 <= piVar3) break;
        if ((*(volatile char *)(piVar3[1] + 5) != 0) && (*(volatile unsigned int *)(piVar3[0] + 4) != 0)) {
            fnptr fn = (fnptr)(*(unsigned int *)(piVar3[0] + 4));
            fn(piVar3, uVar2);
        }
        piVar3 = piVar3 + 4;
    }
}
