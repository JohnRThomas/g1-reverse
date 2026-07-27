/* Reconstructed FUN_00018730 @ 0x18730  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint32_t FUN_00081526(unsigned long);
extern void FUN_00018334(void*,void*);
extern int FUN_000167a8(void);
extern int FUN_00032ee4(void);
extern int FUN_00086be4(int,void*,int);
extern void FUN_0005420c(int,int);
extern void FUN_00072880(int);
extern void DEBUG_PRINT(unsigned long, ...);

void FUN_00018730(unsigned param_1, unsigned param_2){
    unsigned char auStack_38[32];
    uint32_t *puVar1 = (uint32_t*)FUN_00081526(param_1);
    FUN_00018334(puVar1, auStack_38);
    int iVar2 = FUN_000167a8();
    if (*(char*)(iVar2+0x1071) != 0){
        iVar2 = FUN_000167a8();
        *(char*)(iVar2+0x1071) = 0;
    }
    int iVar5 = FUN_00032ee4();
    if (iVar5 == 0){
        iVar2 = FUN_000167a8();
        iVar2 = FUN_00086be4(iVar2+0x1069, puVar1, 7);
        if (iVar2 != 0){
            iVar2 = FUN_000167a8();
            FUN_0005420c(iVar5, iVar2+0x1069);
            iVar2 = FUN_000167a8();
            *(unsigned char*)(iVar2+0x1070) = (unsigned char)iVar5;
            iVar2 = FUN_000167a8();
            *(int*)(iVar2+0x104c) = iVar5;
            iVar2 = FUN_000167a8();
            FUN_00072880(iVar2+0x80);
        }
    }
    iVar2 = FUN_000167a8();
    *(int*)(iVar2+0x1069) = *(int*)puVar1;
    *(short*)(iVar2+0x106d) = *(short*)((char*)puVar1+4);
    *(unsigned char*)(iVar2+0x106f) = *(unsigned char*)((char*)puVar1+6);
    DEBUG_PRINT(0x0009a638, auStack_38, param_2, iVar2 + 0x1069);
    *(int*)0x20007514 += 1;
    *(unsigned char*)(*(int*)0x20006ab8 + 0x367) = 0;
}
