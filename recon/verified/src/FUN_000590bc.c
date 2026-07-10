/* Reconstructed FUN_000590bc @ 0x590bc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern short* FUN_0005f594(int,int);
extern void FUN_00081cee(int,int,int,void*);
extern void FUN_000821f4(int*,int,int,int);
extern int FUN_00082236(void*,int);
extern int FUN_00082ec8(int,int);
extern void FUN_00086c78(void*,int,int);
uint32_t FUN_000590bc(int* param_1, int param_2){
    short* psVar5=(short*)FUN_0005f594(param_2+0xc,4);
    short sVar2=*psVar5;
    (void)psVar5[1];
    int iVar6=FUN_00082ec8(*(volatile int*)*param_1,1);
    if(iVar6==0){
        iVar6=FUN_00082236((void*)(param_1+0x48),5);
        if(iVar6==0) return 0x12;
        return 0;
    }
    if((uint16_t)sVar2==0) return 1;
    char stackbuf[0x30];
    FUN_00086c78(stackbuf,0,0x14);
    FUN_00081cee(sVar2,sVar2,0x588b5,stackbuf);
    FUN_000821f4(param_1,0x16,sVar2,1);
    return 0;
}

