/* Reconstructed FUN_00046b80 @ 0x46b80  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(int,...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000431b4(int,...);
extern int FUN_000431c0(int,...);
extern int FUN_000432d0(int,...);
extern int FUN_000432ec(int,...);
extern int FUN_00043308(int,...);
extern int FUN_000436f8(int,...);
extern int FUN_0004382c(int,...);
extern int FUN_000469bc(int,...);
extern int FUN_00047260(int,...);
extern int FUN_0007d3dc(int,...);

unsigned FUN_00046b80(int param_1, unsigned param_2, int param_3)
{
    unsigned char bVar1,bVar2; int iVar4,iVar6,iVar8,iVar9,iVar12;
    unsigned char *puVar7; unsigned uVar10,uVar11;
    union { struct { unsigned local_30; int iStack_2c; }; unsigned char b[8]; } u;
    unsigned char auStack_28[4];
    volatile char *pcVar3 = (volatile char*)0x2001cf8f;
    volatile int *puVar5;

    FUN_000167a8(0);
    FUN_000431b4(param_1 + 0x24);
    FUN_000432d0(0);
    if(*pcVar3 == 0){
        if(param_3 == 1){
            if(pcVar3[1] != 0) return 0;
            FUN_0007d3dc(0);
            FUN_000431c0(0);
            FUN_000436f8(0);
            pcVar3[0]=0; pcVar3[1]=0; pcVar3[2]=0;
            pcVar3[1]=1;
            FUN_00043308(0);
            *pcVar3 = 1;
            FUN_000432ec(0);
            puVar5 = (volatile int*)0x000a8e98;
            iVar9 = 0;
            do {
                FUN_000469bc(0);
                uVar10 = 0;
                u.local_30 = *puVar5;
                do {
                    iVar8 = 0;
                    u.iStack_2c = puVar5[1];
                    do {
                        iVar4 = 0x000aae20;
                        iVar12 = *(int*)(param_1 + 0x24 + uVar10*4);
                        bVar2 = *(unsigned char*)(iVar12 + iVar8);
                        puVar7 = auStack_28;
                        iVar6 = u.iStack_2c;
                        if(bVar2 != 0){
                            bVar1 = *(volatile unsigned char*)((unsigned)u.b[iVar9]*0x140 + (uVar10%0x1a)*0xa00 + 0x000aae20 + iVar8);
                            puVar7 = (unsigned char*)(unsigned)bVar1;
                            *(unsigned char*)(iVar12+iVar8) = bVar2 & bVar1;
                            iVar6 = iVar4;
                        }
                        iVar8 = iVar8+1;
                    } while(iVar8 != 0x140);
                    uVar10 = uVar10+1;
                } while(uVar10 != 199);
                iVar8 = FUN_000167a8(u.local_30, iVar6, puVar7);
                uVar11 = *(unsigned*)(iVar8 + 0xeb4);
                iVar8 = FUN_000167a8(0);
                iVar9 = iVar9+1;
                FUN_00047260(uVar11, *(unsigned*)(iVar8+0xeb8), 0,0,0x280,199);
            } while(iVar9 != 8);
            FUN_000432d0(0);
            return 0;
        }
        if(param_3 != 2) return 0;
        if(2 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x000d71ad,0x000d71e3);
            else FUN_00019c70(0);
        }
        FUN_000431c0(0);
    } else {
        if(*pcVar3 != 1) return 0;
        if(param_3 == 1){ FUN_000469bc(0); return 0; }
        if(param_3 != 2) return 0;
        if(2 < *(volatile int*)0x2000230c){
            if(*(volatile int*)0x20007554 == 0) DEBUG_PRINT(0x000d71ad,0x000d71e3);
            else FUN_00019c70(0);
        }
        FUN_0004382c(0);
    }
    FUN_0007d3dc(0);
    pcVar3[0]=0; pcVar3[1]=0; pcVar3[2]=0;
    return 0;
}

