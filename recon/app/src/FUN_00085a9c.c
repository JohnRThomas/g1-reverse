/* Reconstructed FUN_00085a9c @ 0x85a9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0008567c(int,int,int,int,int);
extern int FUN_000857a8(int,int);
extern int FUN_000857e0(int);
extern int FUN_000859b6(int);
extern int thunk_FUN_00072880(int);
int FUN_00085a9c(char *param_1, char *param_2){
    uint32_t uVar2 = *(volatile uint32_t*)(param_2 - 8);
    FUN_000859b6((int)(param_1+0x58));
    int uVar1 = FUN_000857a8(*(volatile int*)(param_1+0xa4), uVar2 & 0xffff);
    if(*(volatile int*)(*(volatile int*)(param_1+0xa0)+0x18)==0){
        FUN_0008567c(*(volatile int*)(param_1+0xa4), (int)(param_2-0x10), 0, 1, uVar1);
    }
    FUN_000857e0(*(volatile int*)(param_1+0xa4));
    return thunk_FUN_00072880((int)(param_1+0x58));
}

