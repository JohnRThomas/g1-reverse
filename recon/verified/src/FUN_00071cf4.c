/* Reconstructed FUN_00071cf4 @ 0x71cf4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00072040(int);
extern int FUN_0007205c(int);
extern void FUN_00072078(int);
extern void FUN_000738d4(void);
extern void FUN_000739f0(int,uint32_t);
extern int FUN_000744a4(int);
extern void FUN_0007e2ec(uint32_t,int);
extern void FUN_0007e2fa();
void FUN_00071cf4(int param_1, uint32_t* param_2){
    int iVar6=param_1+8;
    uint32_t uVar7=0;
    int iVar2=FUN_00072040(iVar6);
    if(iVar2==0){
        FUN_0007e2fa(); FUN_0007e2fa();
        FUN_0007e2ec(uVar7,0x72);
        goto mainp;
    }
    FUN_00072078(iVar6);
    {
        uint32_t* puVar5=*(uint32_t* volatile*)(param_1+0x14);
        int fail=0;
        if(param_2<puVar5) fail=1;
        else{
            uint32_t uVar4=*(volatile uint32_t*)(param_1+0x10);
            uint32_t diff=(uint32_t)((int)param_2-(int)puVar5);
            uint32_t q=uVar4?diff/uVar4:0;
            if(diff!=uVar4*q) fail=1;
            else if((uint32_t*)(uVar4*(*(volatile int*)(param_1+0xc)-1)+(int)puVar5)<param_2) fail=1;
        }
        if(fail){
            FUN_0007e2fa(); FUN_0007e2fa();
            FUN_0007e2ec(0,0x98);
            goto mainp;
        }
    }
mainp:;
    for(;;){
        int r8=*(volatile int*)(param_1+0x18);
        if(r8==0){
            int t=FUN_000744a4(param_1);
            if(t!=0){
                *(volatile int*)(t+0x90)=0;
                *(volatile uint32_t**)(t+0x14)=param_2;
                FUN_000738d4();
                FUN_000739f0(iVar6,uVar7);
                return;
            }
        }
        *param_2=*(volatile int*)(param_1+0x18);
        *(volatile uint32_t**)(param_1+0x18)=param_2;
        *(volatile int*)(param_1+0x1c)=*(volatile int*)(param_1+0x1c)-1;
        iVar2=FUN_0007205c(iVar6);
        if(iVar2!=0) return;
        FUN_0007e2fa(); FUN_0007e2fa();
        FUN_0007e2ec(0,0xf0);
    }
}

