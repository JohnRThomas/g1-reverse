/* Reconstructed FUN_00085b0c @ 0x85b0c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00074844(int,int);
extern int* FUN_00085734(uint32_t,int*,void*,uint32_t,int);
extern void FUN_000859b6(int);
extern int* FUN_00085aee(unsigned int, unsigned int);
extern void thunk_FUN_00072880(int);
typedef int (*fp0)(void);
int* FUN_00085b0c(int param_1, int* param_2, int param_3){
    int iVar5=param_1;
    uint32_t uStack_24=(uint32_t)param_2;
    int iVar1=(*(volatile fp0*)(*(volatile int*)(*(volatile int*)(param_1+0xa0)+0x20)+8))();
    if((iVar1<<0x1d)>=0) return 0;
    if(param_3!=0) param_3=15000;
    int addr58=param_1+0x58;
    int iVar4; int* piVar3;
    while(1){
        FUN_000859b6(addr58);
        piVar3=*(int* volatile*)(param_1+0xb4);
        iVar4=*(volatile int*)(*(volatile int*)(param_1+0xa0)+0x18);
        if(piVar3!=(int*)(param_1+0xb4) && piVar3!=0) break;
        if(iVar4==0){
            piVar3=FUN_00085734(*(volatile uint32_t*)(param_1+0xa8),param_2,(uint8_t*)&uStack_24+2,*(volatile uint32_t*)(param_1+0xa0),iVar5);
            if(piVar3!=0) goto L6a;
            if(*(volatile int16_t*)(*(volatile int*)(param_1+0xa8)+0x24)==0) goto L90;
            piVar3=FUN_00085aee(*(volatile uint32_t*)(param_1+0xb0),*(volatile uint32_t*)(param_1+0x94));
            *param_2=*(volatile int*)(param_1+0x94);
            uStack_24=uStack_24&0xffff;
            thunk_FUN_00072880(addr58);
            if(piVar3!=0) goto L70;
        } else {
L90:
            thunk_FUN_00072880(addr58);
        }
        if(param_3==0) return 0;
        FUN_00074844(0x21,0);
        param_3=param_3-1;
    }
    {
        int p3_0=*(volatile int*)piVar3;
        int p3_1=*(volatile int*)((int)piVar3+4);
        *(volatile int*)(p3_0+4)=p3_1;
        *(volatile int*)(p3_1)=p3_0;
        *(volatile int*)((int)piVar3)=(int)piVar3;
        *(volatile int*)((int)piVar3+4)=(int)piVar3;
        if(iVar4==0){ *param_2=*(volatile int*)(param_1+0x94); }
    }
L6a:
    thunk_FUN_00072880(addr58);
L70:
    *(volatile int*)((int)piVar3+8)=(int)(uStack_24>>0x10);
    *param_2=*(volatile int*)param_2-0x10;
    return (int*)((int)piVar3+0x10);
}

