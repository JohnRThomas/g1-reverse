/* Reconstructed FUN_0004396c @ 0x4396c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(unsigned long, ...);
extern int64_t FUN_000431a8(void);
extern void FUN_00043484(int,int,int,int,int,int);
extern void FUN_000471cc(int,int,int,int,int,int);
extern void FUN_00047260(int,int,int,int,int,int);
uint32_t FUN_0004396c(uint param_1,int param_2,uint param_3,int param_4,uint32_t param_5,uint8_t param_6){
    uint32_t uVar1;
    if(param_1==param_3 && param_2<=param_4){
        uint uVar4=param_6;
        uint8_t uVar5=((param_1&1)==0)?0xf0:0xf;
        if(uVar4>99) uVar4=100;
        int64_t uVar6=FUN_000431a8();
        if((uVar6&2)!=0) FUN_000471cc(*(volatile int*)0x2000a034,0,param_1-6,(int)((uint64_t)uVar6>>32),param_1+6,param_4);
        int piVar3=*(volatile int*)0x2000a034 + param_2*4;
        for(int i=0;i<param_4-param_2;i++){
            *(volatile uint8_t*)(*(volatile int*)piVar3 + (int)param_1/2)=uVar5;
            piVar3+=4;
        }
        int iVar2=(int)FUN_000431a8();
        if((iVar2<<0x1e)<0){
            iVar2=FUN_000167a8(); uint32_t u=*(volatile uint32_t*)(iVar2+0xeb4);
            iVar2=FUN_000167a8();
            FUN_00047260(u,*(volatile uint32_t*)(iVar2+0xeb8),param_1-6,param_2-0xe,param_3+6,param_4+0xe);
        }
        uVar1=0;
        FUN_00043484(0x17,param_1-4,(int)(uVar4*((param_4-param_2)-0xd))/100+param_2,0,0,0);
    } else {
        if(*(volatile int*)0x2000230c>1){
            if(*(volatile int*)0x20007554==0) DEBUG_PRINT(0xaa96d,0xaacee,param_3,0,param_1,param_2,param_3);
            else FUN_00019c70(0xaa96d,0xaacee,param_3,
                              *(volatile int*)0x20007554,
                              param_1,param_2,param_3);
        }
        uVar1=0xffffffff;
    }
    return uVar1;
}
