/* Reconstructed update_persist_task_status @ 0x2bef4  (parity: 3/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT(int,int,uint);
extern void FUN_00019c70(void);
extern void FUN_00049858(int);
extern void FUN_0007cdf8(void);
uint update_persist_task_status(int param_1, uint param_2, uint param_3){
    volatile char* pcVar2=(volatile char*)0x20018d9c;
    while(*pcVar2!=0) FUN_0007cdf8();
    *pcVar2=1;
    int* p1054=*(int* volatile*)(param_1+0x1054);
    if(*(volatile uint*)p1054==param_2){
        uint uVar3=*(volatile uint8_t*)((int)p1054+4);
        if(uVar3==1 || uVar3==param_3) goto L8a;
    }
    { char d5=*(volatile char*)(param_1+0xd5);
      if(d5!=0 && d5!=1) goto elseb; }
    if(param_3!=2) goto L9e;
    goto L4a;
elseb:
    FUN_00049858(*(volatile uint8_t*)(param_1+0xd5));
    if(param_3==2){
        if(param_2>0x10) goto L8a;
        if((int)(((uint)0x10050>>(param_2&0xff))<<0x1f) >= 0) goto L8a;
        goto L4a;
    }
L9e:
    if(param_3==3){
        if(*(volatile int*)0x2000230c>0){
            if(*(volatile int*)0x20007554==0) DEBUG_PRINT(0xa25b9,0xa2660,param_2); else FUN_00019c70();
        }
    } else {
        if(*(volatile int*)0x2000230c>0){
            if(*(volatile int*)0x20007554==0) DEBUG_PRINT(0xa25d9,0xa2660,param_2); else FUN_00019c70();
        }
    }
    goto Ltail;
L4a:
    if(*(volatile int*)0x2000230c>0){
        if(*(volatile int*)0x20007554==0) DEBUG_PRINT(0xa2597,0xa2660,param_2); else FUN_00019c70();
    }
    if(param_2==0x10){
        char cVar1=*(volatile char*)(param_1+0xf98);
        *(volatile char*)0x20018d9d=cVar1;
        if(cVar1==1) *(volatile char*)(param_1+0xf98)=0;
    }
Ltail:
    *(volatile char*)(param_1+0xd5)=(char)param_2;
    **(int* volatile*)(param_1+0x1054)=(int)param_2;
    *(volatile char*)(*(int* volatile*)(param_1+0x1054)+1)=(char)param_3;
L8a:
    *pcVar2=0;
    return param_3;
}

