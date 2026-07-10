/* Reconstructed FUN_00081326 @ 0x81326  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void FUN_00055ba0(void*, int);
extern int FUN_0004fa34(void*, void*);
extern int FUN_00080058(int, void*, void*);
unsigned FUN_00081326(int param_1, int param_2, int param_3){
    unsigned char auStack_d0[16];
    unsigned char auStack_c0[180];
    if (param_1 != 0 && param_2 != 0 && param_3 != 0){
        FUN_00055ba0(auStack_d0, param_1);
        int iVar2 = FUN_0004fa34(auStack_c0, auStack_d0);
        if (iVar2 != 0){
            FUN_00055ba0(auStack_d0, param_2);
            iVar2 = FUN_00080058(param_3, auStack_d0, auStack_c0);
            if (iVar2 != 0){
                unsigned char *puVar4 = (unsigned char*)(param_3 - 1);
                unsigned char *puVar3 = (unsigned char*)(param_3 + 0x10);
                do {
                    puVar4 = puVar4 + 1;
                    unsigned char uVar1 = *puVar4;
                    puVar3 = puVar3 - 1;
                    *puVar4 = *puVar3;
                    *puVar3 = uVar1;
                } while (puVar4 != (unsigned char*)(param_3 + 7));
                return 0;
            }
        }
    }
    return 0xffffffea;
}

