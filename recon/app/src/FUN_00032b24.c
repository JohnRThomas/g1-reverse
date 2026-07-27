/* Reconstructed FUN_00032b24 @ 0x32b24  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern int FUN_0007d16a(int *, unsigned char *);
typedef int (*fp5)(void*,int,void*,void*,uint32_t);
uint32_t FUN_00032b24(int param_1, char* param_2, int param_3, uint32_t* param_4, uint8_t* param_5, uint32_t param_6){
    if(param_2==0 || param_3==0 || param_4==0 || param_5==0 || param_1==2){
        DEBUG_PRINT(0x000a74b9U); return 0xffffffff;
    }
    int iVar3=0;
    uint8_t cVar1=*(volatile uint8_t*)param_2;
    char* pcVar5=(char*)(uintptr_t)0x8a208U;
    while(*(volatile uint8_t*)pcVar5 != cVar1 || *(void* volatile*)(pcVar5+4)==0){
        iVar3++; pcVar5+=8;
        if(iVar3==0x2d){
            uint8_t* p=(uint8_t*)(uintptr_t)*(volatile uint32_t*)param_4;
            *(volatile uint8_t*)(p+1)=1; *(volatile uint8_t*)(p+3)=1; *(volatile uint8_t*)(p+0)=cVar1; *(volatile uint8_t*)(p+2)=3; *(volatile uint8_t*)(p+4)=2;
            *param_5=5;
            goto L68;
        }
    }
    (*(volatile fp5*)(pcVar5+4))(param_2,param_3,param_4,param_5,param_6);
L68:;
    volatile uint8_t* puVar2=(volatile uint8_t*)(uintptr_t)0x20019ef5U;
    if(param_1!=0){
        if(param_1!=1) return 0;
        uint8_t original_length = *(volatile uint8_t*)param_5;
        uint8_t* puVar4=(uint8_t*)(uintptr_t)*(volatile uint32_t*)param_4;
        volatile uint8_t* puVar6=(volatile uint8_t*)(uintptr_t)0x20019ef5U;
        for(iVar3=0; iVar3<(int)original_length; iVar3++){
            *puVar6=*(volatile uint8_t*)(puVar4+iVar3); puVar6++;
        }
        /* The shipped STR may target an unaligned packet buffer.  A fixed
         * four-byte memcpy preserves that store without alignment UB. */
        uint32_t header = ((uint32_t)original_length << 24) | 0x00ffa55aU;
        __builtin_memcpy(puVar4, &header, sizeof(header));
        for (iVar3 = 0; iVar3 < (int)original_length; iVar3++) {
            puVar4[4 + iVar3] = puVar2[iVar3];
        }
        *param_5 = (uint8_t)(original_length + 4U);
    }
    { int r=FUN_0007d16a(param_4,param_5); if(r==0) return 0; return 0xfffffffc; }
}
