/* Reconstructed FUN_0004a9ec @ 0x4a9ec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000167a8(void);
extern unsigned FUN_0007dac0(void);
extern unsigned long long FUN_0007daa4(void);
extern void FUN_00019c70(unsigned long, ...);
extern void DEBUG_PRINT(unsigned long, ...);

void FUN_0004a9ec(void){
    int iVar1 = FUN_000167a8();
    if (*(char*)(iVar1+0x1092) != 1){
        unsigned uVar2 = FUN_0007dac0();
        if (uVar2 < 7){
            iVar1=FUN_000167a8(); *(char*)(iVar1+0x1092)=1;
            iVar1=FUN_000167a8(); *(char*)(iVar1+0x1093)=(char)uVar2;
            iVar1=FUN_000167a8(); *(unsigned long long*)(iVar1+0x1094)=FUN_0007daa4();
            iVar1=FUN_000167a8(); { int a = (int)(uVar2*0xc) + iVar1; *(int*)(a+0x113a) += 1; }
            iVar1=FUN_000167a8(); *(int*)(iVar1+0x10d6) += 1;
            if (1 < *(int*)0x2000230c){
                if (*(int*)0x20007554 != 0){
                    iVar1=FUN_000167a8();
                    FUN_00019c70(0x000f038d,0x000f0475,*(unsigned*)(iVar1+0x1094),*(unsigned*)(iVar1+0x1098));
                    return;
                }
                iVar1=FUN_000167a8();
                DEBUG_PRINT(0x000f038d,0x000f0475,*(unsigned*)(iVar1+0x1094),*(unsigned*)(iVar1+0x1098));
                return;
            }
        }
    }
}

