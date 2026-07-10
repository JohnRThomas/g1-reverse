/* Reconstructed FUN_000821f4 @ 0x821f4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern long long FUN_000585f0(unsigned,int);
extern int tail_58568(void);
extern unsigned char* FUN_0005f5d0(int,int);
extern int FUN_000821a4(unsigned,int);
void FUN_000821f4(unsigned param_1, int param_2, unsigned short param_3, unsigned param_4){
    if (param_2 == 0) return;
    long long uVar5 = FUN_000585f0(param_1, 1);
    int iVar1 = (int)uVar5;
    if (iVar1 == 0){ tail_58568(); return; }
    unsigned char* puVar2 = FUN_0005f5d0(iVar1 + 0xc, 4);
    *(volatile unsigned char*)puVar2 = (unsigned char)param_2;
    *(volatile unsigned short*)(puVar2 + 1) = param_3;
    *(volatile unsigned char*)(puVar2 + 3) = (unsigned char)param_4;
    FUN_000821a4(param_1, iVar1);
}

