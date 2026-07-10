/* Reconstructed FUN_00036d38 @ 0x36d38  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern unsigned FUN_00023ee0(void);
extern int FUN_000167a8(void);
extern int FUN_0007d3ee(void);
extern int FUN_0007d446(void);
extern void FUN_000471cc(int,int,int,int,int,int);
extern void FUN_00047260(int,int,int,int,int,int);
extern void FUN_00043e90(int,int,int,int,int,int,int,int,int,int,int,int);

void FUN_00036d38(void)
{
    volatile uint8_t *g = (volatile uint8_t*)0x20004968;
    unsigned uVar1;
    int iVar2, iVar3, iVar4, iVar5, iVar6;
    int uVar7, uVar8;

    uVar1 = FUN_00023ee0();
    if ((unsigned)*g != uVar1) {
        *g = (uint8_t)uVar1;
        iVar2 = FUN_000167a8();
        iVar3 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar6 = FUN_0007d446();
        FUN_000471cc(iVar2 + 0xb90, 0, iVar3 + 0x10a, iVar4 + 0x1c, iVar5 + 0x232, iVar6 + 0x88);
        iVar2 = FUN_000167a8();
        uVar7 = *(volatile int*)(iVar2 + 0xeb4);
        iVar2 = FUN_000167a8();
        uVar8 = *(volatile int*)(iVar2 + 0xeb8);
        iVar2 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_00047260(uVar7, uVar8, iVar2 + 0x10a, iVar3 + 0x1c, iVar4 + 0x232, iVar5 + 0x88);
    }
    if (uVar1 == 6) {
        iVar2 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_00043e90(0, 0x000a8ec6, 0, iVar2 + 0x134, iVar3 + 0x28, iVar4 + 0x236, iVar5 + 0x43, 1, 0, 0, 0, 0);
        iVar2 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar2 = iVar2 + 0x15a;
        uVar7 = 0x000a8edd;
        FUN_00043e90(0, uVar7, 0, iVar2, iVar4 + 0x43, iVar5 + 0x236, iVar3 + 0x5e, 1, 0, 0, 0, 0);
    } else {
        iVar2 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar4 = FUN_0007d3ee();
        iVar5 = FUN_0007d446();
        FUN_00043e90(0, 0x000a8ea1, 0, iVar2 + 0x144, iVar3 + 0x28, iVar4 + 0x236, iVar5 + 0x43, 1, 0, 0, 0, 0);
        iVar2 = FUN_0007d3ee();
        iVar4 = FUN_0007d446();
        iVar5 = FUN_0007d3ee();
        iVar3 = FUN_0007d446();
        iVar2 = iVar2 + 0x150;
        uVar7 = 0x000a8eb5;
        FUN_00043e90(0, uVar7, 0, iVar2, iVar4 + 0x43, iVar5 + 0x236, iVar3 + 0x5e, 1, 0, 0, 0, 0);
    }
}

