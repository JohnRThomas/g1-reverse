/* Reconstructed FUN_00022974 @ 0x22974  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned uint;
extern int DEBUG_PRINT(int,...);
extern int FUN_000167a8(int,...);
extern int FUN_00019c70(int,...);
extern int FUN_0002ae84(int,...);
extern int FUN_0007da4a(int,...);
extern int FUN_0008638c(int,...);
extern int FUN_00086c78(int,...);

unsigned FUN_00022974(unsigned short *param_1, int param_2, uint param_3)
{
    volatile int *piVar1,*piVar3; unsigned *puVar2; unsigned short uVar4; int iVar5;
    unsigned uVar6,uVar8; int iVar7,iVar10; int(*pcVar11)(int,...); uint uVar9,uVar12;
    unsigned char local_428[1028];
    piVar3 = (volatile int*)0x2000230c;
    piVar1 = (volatile int*)0x20007554;
    if(*piVar3 < 3){
        if(param_1 == 0) return 0xffffffff;
        if(param_3 == 0) return 0xffffffff;
    } else {
        if(*piVar1 == 0){ DEBUG_PRINT(0x0009e484, 0x0009e4f9); }
        else { FUN_00019c70(0); }
        if(param_1 == 0 || param_3 == 0){
            if(*piVar3 < 3) return 0xffffffff;
            uVar6 = 0x0009e4a3;
            uVar8 = 0x0009e4f9;
            if(*piVar1 != 0){ FUN_00019c70(0); return 0xffffffff; }
            goto LAB_00022a22;
        }
    }
    uVar9 = (param_3 << 6) >> 0x10;
    if((param_3 & 0x3ff) != 0){ uVar9 = (uVar9 + 1) & 0xffff; }
    local_428[0] = 0xff; local_428[1]=0; local_428[2]=0; local_428[3]=0;
    FUN_00086c78((int)(local_428+4), 0, 0x3fc);
    puVar2 = (unsigned*)0x00087bf0;
    iVar5 = FUN_0008638c(0x00087bf0);
    uVar6 = 0x0009e4f9;
    piVar1 = (volatile int*)0x20007554;
    if(iVar5 != 0){
        iVar5 = param_2;
        while(1){
            if(iVar5 == param_2 + (int)(uVar9 * 0x400)){
                if(*(volatile char*)0x2000302c != 0 && *(volatile char*)0x20018d90 == 0){ FUN_0002ae84(0); }
                return 0;
            }
            iVar10 = (param_3 + param_2) - iVar5;
            if(0x3ff < iVar10){ iVar10 = 0x400; }
            iVar7 = FUN_000167a8(0);
            pcVar11 = *(int(**)(int,...))(iVar7 + 0x1030);
            uVar8 = FUN_000167a8(0);
            iVar7 = (*pcVar11)(uVar8, iVar5, (int)local_428, iVar10);
            if(iVar7 != 0) break;
            uVar12 = 0;
            while(1){
                iVar7 = *piVar3;
                if(iVar10 <= (int)(uVar12 & 0xff)) break;
                if(2 < iVar7){
                    if(*piVar1 == 0){ DEBUG_PRINT(0x0009e4e3, uVar6, (uint)local_428[uVar12 & 0xff]); }
                    else { FUN_00019c70(0x0009e4e3, uVar6); }
                }
                uVar12 = uVar12 + 1;
            }
            if(2 < iVar7){
                if(*piVar1 == 0){ DEBUG_PRINT(0x0009e4f0, uVar6); }
                else { FUN_00019c70(0); }
            }
            uVar4 = FUN_0007da4a(*param_1, (int)local_428, iVar10);
            iVar5 = iVar5 + 0x400;
            *param_1 = uVar4;
        }
        DEBUG_PRINT(0x0009e4c7, iVar5, iVar7);
        return 0xffffffff;
    }
    uVar8 = *puVar2;
    uVar6 = 0x000a40ec;
LAB_00022a22:
    DEBUG_PRINT(uVar6, uVar8);
    return 0xffffffff;
}

