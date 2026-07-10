/* Reconstructed FUN_00036820 @ 0x36820  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern int FUN_000167a8(void);
extern void FUN_0003678c(void);
extern int FUN_00076d6c(void);
extern void FUN_00076d7c(void);
extern void FUN_000777f0(void);
extern int FUN_0007d1c8(void);
extern void FUN_00086c04(void);
extern void FUN_00086c78(void);
extern int FUN_00087036(void);

typedef int (*fnptr)(int,int,int,int);

void FUN_00036820(unsigned param_1)
{
    int puVar2 = FUN_00076d6c();
    if (puVar2 == 0) { DEBUG_PRINT(); return; }
    FUN_00086c78();
    if (4 < param_1) { DEBUG_PRINT(); param_1 = 0; }

    int r3a = FUN_000167a8();
    int fn = *(volatile int*)(r3a + 0x1030);
    FUN_000167a8();
    int iVar12 = (int)(param_1 * 0x3ebe + 0x180000);
    int iVar3 = ((fnptr)(intptr_t)fn)(0, iVar12, puVar2, 0x50);
    if (iVar3 != 0) { DEBUG_PRINT(); goto TAIL; }

    iVar3 = FUN_00087036();
    if (iVar3 != 0) { DEBUG_PRINT(); goto TAIL; }

    int iVar3b = FUN_0007d1c8();
    int iVar5 = FUN_0007d1c8();
    int iVar6 = FUN_0007d1c8();

    if (*(volatile uint16_t*)(puVar2 + 0x1c) != 1) {
        FUN_000777f0();
        goto TAIL;
    }

    {
        int iv5 = iVar5;
        int iVar10 = iv5 + 7;
        *(volatile int*)0x20009fc4 = 0;
        if (iVar10 < 0) iVar10 = iv5 + 0xe;
        *(volatile int*)0x20009fc8 = 0;
        int iVar11 = iv5 + 0x1f;
        if (iVar11 < 0) iVar11 = iv5 + 0x3e;
        iVar12 = iVar12 + iVar3b + (iVar6 - 1) * (iVar11 >> 5) * 4;
        for (int r7 = 0; r7 < iVar6; r7++) {
            *(volatile int*)0x20009fc4 = 0;
            FUN_00086c78();
            int r7a = FUN_000167a8();
            int fn2 = *(volatile int*)(r7a + 0x1030);
            FUN_000167a8();
            int iVar7 = ((fnptr)(intptr_t)fn2)(0, iVar12, puVar2, iVar10 >> 3);
            if (iVar7 != 0) { DEBUG_PRINT(); goto TAIL; }
            for (int fp = 0; fp < (iVar10 >> 3); fp++) {
                FUN_0003678c();
            }
            if (*(volatile int*)0x20009fcc != 0) {
                *(volatile int*)0x20009fc8 = 0;
                FUN_000167a8();
                FUN_00086c04();
            }
            iVar12 = iVar12 + (iVar11 >> 5) * -4;
        }
    }
TAIL:
    FUN_00076d7c();
    return;
}

