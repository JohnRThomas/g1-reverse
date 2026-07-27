/* Reconstructed FUN_00055094 @ 0x55094  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00053cd4(int,...);
extern int FUN_00053d70(int,...);
extern int FUN_00055710(int,...);
extern int FUN_000566a4(void);
extern int FUN_00056f08(int,...);
extern int FUN_0005e758(int,...);
extern int FUN_0005f5d0(int,...);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(int,...) __attribute__((noreturn));
extern int FUN_00080fc4(int,...);
extern int FUN_0008104a(int,...);
extern int FUN_00081050(int,...);

void FUN_00055094(int param_1)
{
    unsigned char bVar1; int iVar2,iVar3; unsigned uVar4;
    unsigned local_48,local_44; int iStack_40; unsigned local_28,local_24;
    iVar2 = 0x20002000;
    if(param_1==0) return;
    bVar1 = *(volatile unsigned char*)0x20002121U;
    if(*(volatile unsigned char*)0x20002120U == 0){
        if(bVar1==0){
            FUN_0007e2fa(0x00099cbd,0x000f369a,0x000f3509,0x433);
            FUN_0007e2ec(0x000f3509,0x433);
        }
    } else if((unsigned)bVar1 <= *(volatile unsigned char*)0x20002120U + 1){
        iVar3 = FUN_00056f08(0,0,6);
        if(iVar3 != 0){
            __atomic_fetch_or((unsigned *)(uintptr_t)(iVar2 + 0xd4), 0x8000,
                              __ATOMIC_RELAXED);
            *(unsigned char*)(param_1+8) |= 2;
            FUN_000566a4();
            return;
        }
        FUN_00055710(0x000810ab,0);
        iVar3 = FUN_00081050(0);
        if(iVar3==0){
            if(*(volatile unsigned char*)(iVar2+0x120) < *(volatile unsigned char*)(iVar2+0x121)){
                *(volatile unsigned char*)(iVar2+0x121) = *(volatile unsigned char*)(iVar2+0x121) - 1;
                uVar4 = 0x00081035;
                *(unsigned char*)(param_1+8) &= 0xfb;
                FUN_0005e758(2,uVar4,0);
            } else {
                iVar3 = FUN_00053cd4(0x2028,7);
                if(iVar3!=0){
                    uVar4 = FUN_0005f5d0(iVar3+0xc,7);
                    FUN_00080fc4(uVar4,param_1+1);
                    iVar3 = FUN_00053d70(0x2028,iVar3,0);
                    if(iVar3==0){
                        *(char*)(iVar2+0x121) = *(char*)(iVar2+0x121) - 1;
                        *(unsigned char*)(param_1+8) &= 0xfb;
                        goto LAB_00055142;
                    }
                }
                local_24 = 0x000f36e0;
                local_28 = 2;
                FUN_0008104a(0x00088150,0x1040,&local_28);
            }
        } else {
            local_44 = 0x000f36b3;
            local_48 = 3;
            iStack_40 = iVar3;
            FUN_0008104a(0x00088150,0x1840,&local_48);
        }
LAB_00055142:
        if(*(char*)(iVar2+0x121) != 0){
            FUN_00081050(1);
        }
        FUN_00055710(0x00081081,0);
        return;
    }
    *(volatile unsigned char*)0x20002121U = bVar1 - 1;
    *(unsigned char*)(param_1+8) &= 0xfb;
    return;
}
