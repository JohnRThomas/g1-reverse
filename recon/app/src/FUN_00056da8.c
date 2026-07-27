/* Reconstructed FUN_00056da8 @ 0x56da8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_000819ea(void);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0007e2ec(unsigned,unsigned);
typedef void (*fp)(int,...);
void FUN_00056da8(int param_1, unsigned param_2, unsigned param_3, unsigned param_4){
    *(unsigned char*)(param_1 + 10) = *(unsigned char*)(param_1 + 9);
    FUN_000819ea();
    int iVar3 = *(volatile int*)0x2000ad1cUL;
    while (iVar3 != 0){
        fp pcVar2 = *(fp*)(iVar3 + 0x14);
        if (pcVar2 != 0){
            pcVar2(param_1, *(unsigned char*)(param_1+9), param_3, pcVar2, param_4);
        }
        iVar3 = *(int*)(iVar3 + 0x20);
    }
    unsigned uVar4 = 0x87fec;
    unsigned uVar1 = 0x88058;
    while (1){
        if (uVar1 < uVar4){
            FUN_0007e2fa(0x99cbd, 0xf3a8d, 0xf3a5d, 0x8ca);
            FUN_0007e2fa(0xf0d20);
            FUN_0007e2ec(0xf3a5d, 0x8ca);
        }
        if (uVar1 <= uVar4) break;
        if (*(fp*)(uVar4 + 0x14) != 0){
            (*(fp*)(uVar4 + 0x14))(param_1, *(unsigned char*)(param_1+9), param_3);
        }
        uVar4 = uVar4 + 0x24;
    }
}

