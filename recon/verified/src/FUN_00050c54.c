/* Reconstructed FUN_00050c54 @ 0x50c54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#define S98 (*(volatile uint32_t*)0xe000ed98UL)
#define S9c (*(volatile uint32_t*)0xe000ed9cUL)
#define Sa0 (*(volatile uint32_t*)0xe000eda0UL)
extern void FUN_0004d944(int, int, int, int);
extern int FUN_00050bf0(unsigned, int);
extern int FUN_00050c24(void);
extern unsigned FUN_00080786(unsigned);
extern int FUN_00080798(unsigned, int);

unsigned FUN_00050c54(unsigned *param_1, int param_2, unsigned param_3)
{
    volatile int logbuf[8];
    unsigned uVar6 = 0;
    int local_3c = param_2;
    unsigned uVar2, uVar4, uVar5, uVar7, uVar8;
    int iVar3;

LOOP:
    if (local_3c <= (int)uVar6) return param_3;
    uVar4 = param_1[1];
    if (uVar4 == 0) goto NEXT;
    if (uVar4 <= 0x1f || (uVar4 & 0x1f) != 0) goto DO_LOG;
    uVar7 = param_1[0];
    if ((uVar7 & 0x1f) != 0) goto DO_LOG;
    uVar2 = FUN_00080786(uVar7);
    uVar4 = FUN_00080786(uVar4 + uVar7 - 1);
    if (uVar2 != uVar4) goto DO_LOG;
    if (uVar2 == 0xffffffea || (int)uVar2 >= (int)param_3) goto DO_LOG;
    S98 = uVar2;
    S98 = uVar2;
    uVar5 = Sa0 | 0x1f;
    uVar7 = param_1[0];
    uVar4 = param_1[1];
    uVar8 = uVar4 + uVar7 - 1;
    if ((S9c & 0xffffffe0) == uVar7) {
        if (uVar5 == uVar8) {
            FUN_00080798(uVar2 & 0xff, (int)(intptr_t)param_1);
            goto NEXT;
        }
        S98 = uVar2;
        S9c = (S9c & 0x1f) | ((uVar4 + uVar7) & 0xffffffe0);
        iVar3 = FUN_00080798(param_3 & 0xff, (int)(intptr_t)param_1);
        if (iVar3 == -0x16) return 0xffffffea;
    } else {
        uVar4 = (uVar7 - 1) & 0xffffffe0;
        S98 = uVar2;
        if (uVar5 == uVar8) {
            Sa0 = (Sa0 & 0x1f) | uVar4;
            iVar3 = FUN_00080798(param_3 & 0xff, (int)(intptr_t)param_1);
            if (iVar3 == -0x16) return 0xffffffea;
        } else {
            Sa0 = uVar4 | (Sa0 & 0x1f);
            iVar3 = FUN_00080798(param_3 & 0xff, (int)(intptr_t)param_1);
            if (iVar3 == -0x16) return 0xffffffea;
            S98 = uVar2;
            uVar4 = (iVar3 + 1U) & 0xff;
            if (7 < uVar4) {
                iVar3 = FUN_00050c24();
                if (iVar3 == -0x16) return 0xffffffea;
            } else {
                iVar3 = FUN_00050bf0(uVar4, (int)(intptr_t)logbuf);
            }
        }
    }
    param_3 = iVar3 + 1;
NEXT:
    uVar6 = uVar6 + 1;
    param_1 = param_1 + 3;
    goto LOOP;
DO_LOG:
    FUN_0004d944(0x00088228, 0x1840, (int)(intptr_t)logbuf, 0);
    return 0xffffffea;
}

