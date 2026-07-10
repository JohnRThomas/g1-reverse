/* named: FUN_00032b24 */
/* Reconstructed FUN_00032b24 @ 0x32b24  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT();
extern int FUN_0007d16a(void*,void*);
typedef int (*fp5)(void*,int,void*,void*,uint32_t);
uint32_t FUN_00032b24(int param_1, char* param_2, int param_3, int* param_4, uint8_t* param_5, uint32_t param_6){
    if(param_2==0 || param_3==0 || param_4==0 || param_5==0 || param_1==2){
        DEBUG_PRINT(); return 0xffffffff;
    }
    int iVar3=0;
    uint8_t cVar1=*(volatile uint8_t*)param_2;
    char* pcVar5=(char*)0x8a208;
    while(*(volatile uint8_t*)pcVar5 != cVar1 || *(void* volatile*)(pcVar5+4)==0){
        iVar3++; pcVar5+=8;
        if(iVar3==0x2d){
            uint8_t* p=(uint8_t*)*(volatile int*)param_4;
            *(volatile uint8_t*)(p+1)=1; *(volatile uint8_t*)(p+3)=1; *(volatile uint8_t*)(p+0)=cVar1; *(volatile uint8_t*)(p+2)=3; *(volatile uint8_t*)(p+4)=2;
            *param_5=5;
            goto L68;
        }
    }
    (*(volatile fp5*)(pcVar5+4))(param_2,param_3,param_4,param_5,param_6);
L68:;
    volatile uint8_t* puVar2=(volatile uint8_t*)0x20019ef5;
    if(param_1!=0){
        if(param_1!=1) return 0;
        uint32_t local_24=((uint32_t)(*(volatile uint8_t*)param_5)<<24)|0xffa55a;
        uint8_t* puVar4=(uint8_t*)*(volatile int*)param_4;
        volatile uint8_t* puVar6=(volatile uint8_t*)0x20019ef5;
        for(iVar3=0; iVar3<(int)(uint32_t)*(volatile uint8_t*)param_5; iVar3++){
            *puVar6=*(volatile uint8_t*)(puVar4+iVar3); puVar6++;
        }
        puVar6=(volatile uint8_t*)(puVar4+3);
        *(volatile uint32_t*)puVar4=local_24;
        while((int)(puVar6+(-3-(int)puVar4))<(int)(uint32_t)*(volatile uint8_t*)param_5){
            puVar6++; *puVar6=*puVar2; puVar2++;
        }
        *param_5=*(volatile uint8_t*)param_5+4;
    }
    { int r=FUN_0007d16a(param_4,param_5); if(r==0) return 0; return 0xfffffffc; }
}

