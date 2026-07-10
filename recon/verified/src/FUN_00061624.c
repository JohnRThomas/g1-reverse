/* Reconstructed FUN_00061624 @ 0x61624  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0006567c(int,...);
extern int FUN_000657e4(int,...);
extern int FUN_000658e8(int,...);
extern int FUN_000659cc(int,...);
extern int FUN_00065b18(int,...);
extern int FUN_0007e2ec(int,...) __attribute__((noreturn));
extern int FUN_0007e2fa(int,...);

unsigned FUN_00061624(int param_1, unsigned param_2, unsigned param_3, unsigned param_4)
{
    unsigned uVar1; int iVar2,iVar3; unsigned uVar4,uVar5,uVar6,uVar8; unsigned char bVar7; int iVar9; int bVar10;
    unsigned uStack_24, local_20, uStack_1c;
    iVar9 = *(int*)(param_1+4);
    uVar8 = (param_2 & 0x1f) | ((unsigned)*(unsigned char*)(iVar9+0xc) << 5);
    uStack_24 = param_2;
    local_20 = param_3;
    uStack_1c = param_4;
    iVar2 = FUN_000658e8(uVar8, (int)&uStack_24 + 3, param_3, (unsigned)*(unsigned char*)(iVar9+0xc), param_1);
    if((param_3 & 0x30000) == 0){
        FUN_00065b18(uVar8);
        if(iVar2 == 0x0bad0000){
            iVar9 = FUN_000659cc((unsigned char)(uStack_24>>24));
            if(iVar9 != iVar2){
                FUN_0007e2fa(0x00099cbd, 0x000f0ac7, 0x000f5e79, 0x6c);
                uVar4 = 0x6c;
LAB_00061674:
                FUN_0007e2ec(0x000f5e79, uVar4);
            }
        }
LAB_00061734:
        uVar4 = 0;
    } else {
        local_20 = 0; uStack_1c = 0;
        iVar3 = FUN_0006567c(uVar8, 0, &local_20);
        if(iVar3 != 0x0bad0000) goto LAB_000616ce;
        if(iVar2 == iVar3){
            iVar3 = FUN_000659cc((unsigned char)(uStack_24>>24));
            if(iVar3 != iVar2){
                FUN_0007e2fa(0x00099cbd, 0x000f0ac7, 0x000f5e79, 0x7f);
                uVar4 = 0x7f;
                goto LAB_00061674;
            }
        }
        uVar1 = local_20;
        if((int)(param_3 << 0xe) < 0){
            uVar5 = param_3 & 0x306;
            if(uVar5 == 0x106){
                uVar5 = 7;
LAB_000616f8:
                if((int)(param_3 << 0x1b) < 0){ uVar6 = 3; }
                else { uVar6 = (param_3 << 0x1a) >> 0x1f; }
                *((unsigned char*)&local_20 + 3) = (unsigned char)(uVar1 >> 24);
                *((unsigned char*)&local_20 + 0) = (unsigned char)uVar5;
                *((unsigned char*)&local_20 + 1) = (unsigned char)(((param_3 ^ 0x10000) << 0xf) >> 0x1f);
                *((unsigned char*)&local_20 + 2) = (unsigned char)uVar6;
                if((int)(param_3 << 0xc) < 0){
                    *(int*)(*(int*)(iVar9+4)+8) = 1 << (param_2 & 0xff);
                } else {
                    iVar2 = param_3 << 0xd;
                    bVar10 = iVar2 < 0;
                    if(bVar10){ iVar2 = *(int*)(iVar9+4); uVar6 = 1 << (param_2 & 0xff); }
                    if(bVar10){ *(unsigned*)(iVar2+0xc) = uVar6; }
                }
                iVar2 = FUN_000657e4(uVar8, &local_20, 0);
                goto LAB_0006172e;
            }
            if(0x106 < uVar5){
                if(uVar5 == 0x202){ uVar5 = 5; }
                else if(uVar5 == 0x300){ uVar5 = 3; }
                else { if(uVar5 != 0x200) goto LAB_000616ce; uVar5 = 2; }
                goto LAB_000616f8;
            }
            if(uVar5 == 6) goto LAB_000616f8;
            if(uVar5 < 7){
                if(uVar5 != 0){ if(uVar5 != 2) goto LAB_000616ce; uVar5 = 4; }
                goto LAB_000616f8;
            }
            if(uVar5 == 0x100){ uVar5 = 1; goto LAB_000616f8; }
        } else {
            if((int)(param_3 << 0x1b) < 0){ bVar7 = 3; }
            else { bVar7 = (unsigned char)((param_3 << 0x1a) >> 0x1f); }
            *((unsigned char*)&local_20) = bVar7;
            iVar2 = FUN_0006567c(uVar8, &local_20, 0);
LAB_0006172e:
            if(iVar2 == 0x0bad0000) goto LAB_00061734;
        }
LAB_000616ce:
        uVar4 = 0xffffffea;
    }
    return uVar4;
}

