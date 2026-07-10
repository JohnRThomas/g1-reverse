/* Reconstructed FUN_0003384c @ 0x3384c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(void);
extern void FUN_0000ef12(void);
extern int FUN_000167a8(void);
extern int FUN_00019c70(void);
extern int FUN_00033730(void);
extern int FUN_00087036(void);

int FUN_0003384c(int param_1)
{
    int iVar4;
    int cVar5;

    if (param_1 == 0) return 0;
    cVar5 = 9;
    do {
        FUN_0000ef12();
        iVar4 = FUN_00087036();
        if (iVar4 == 0) {
            if (*(volatile int*)0x20007554 == 0) return DEBUG_PRINT();
            return FUN_00019c70();
        }
        cVar5 = (cVar5 - 1) & 0xff;
    } while (cVar5 != 0);
    FUN_000167a8();
    return FUN_00033730();
}

