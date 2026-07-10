/* Reconstructed FUN_00010fc8 @ 0x10fc8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT();
extern uint32_t FUN_0000d804(uint32_t);
extern uint32_t FUN_0000d848(uint32_t);
extern void FUN_0000d8f8(uint32_t,uint32_t,uint32_t,uint32_t);
extern uint32_t FUN_0000db4c(uint32_t,uint32_t,uint32_t,uint32_t);
extern uint32_t FUN_0000dea8(void);
extern int FUN_000167a8(void);
extern void FUN_00019c70(void);
extern uint32_t FUN_0002e648(int);
uint32_t FUN_00010fc8(uint32_t param_1, uint32_t param_2, uint32_t* param_3, uint8_t* param_4){
    DEBUG_PRINT();
    if(param_3==0 || param_4==0){ DEBUG_PRINT(); return 0xffffffff; }
    uint8_t* puVar3 = (uint8_t*)*(volatile uint32_t*)param_3;
    *(volatile uint8_t*)(puVar3+1)=1; *(volatile uint8_t*)(puVar3+0)=0x20; *(volatile uint8_t*)(puVar3+2)=3; *(volatile uint8_t*)(puVar3+3)=0x20;
    uint32_t uVar1 = FUN_0002e648(0);
    *(volatile uint32_t*)(puVar3+4)=uVar1;
    int iVar2;
    iVar2=FUN_000167a8(); *(volatile uint32_t*)(puVar3+8)=*(volatile uint32_t*)(iVar2+0xfa0);
    iVar2=FUN_000167a8(); *(volatile uint32_t*)(puVar3+0xc)=*(volatile uint32_t*)(iVar2+0xfa4);
    iVar2=FUN_000167a8(); *(volatile uint32_t*)(puVar3+0x10)=*(volatile uint32_t*)(iVar2+0xfa8);
    iVar2=FUN_000167a8(); *(volatile uint32_t*)(puVar3+0x14)=*(volatile uint32_t*)(iVar2+0xf94);
    iVar2=FUN_000167a8(); *(volatile uint32_t*)(puVar3+0x18)=*(volatile uint32_t*)(iVar2+0xfb0);
    iVar2=FUN_000167a8(); *(volatile uint32_t*)(puVar3+0x1c)=*(volatile uint32_t*)(iVar2+0xfb4);
    iVar2=FUN_000167a8();
    uint32_t u4=FUN_0000d848(*(volatile uint32_t*)(iVar2+0xfb0));
    u4=FUN_0000db4c(u4,0,0,0);
    uint32_t u5=FUN_0000d804(uVar1);
    FUN_0000d8f8(u4,0,u5,0);
    uVar1=FUN_0000dea8();
    int gv=*(volatile int*)0x2000230c;
    *(volatile uint32_t*)(puVar3+0x20)=uVar1;
    if(gv>2){
        if(*(volatile int*)0x20007554==0){ DEBUG_PRINT(); }
        else { FUN_00019c70(); }
    }
    *param_4=0x24;
    return 0;
}

