/* Reconstructed FUN_0004d594 @ 0x4d594  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004d4a8(uint32_t,uint32_t);
extern int FUN_0004d56c(void);
extern int FUN_0004d578(int);
extern void FUN_0007e2ec(uint32_t,int);
extern void FUN_0007e2fa();
extern int64_t thunk_FUN_00074f68(void);
extern int FUN_0004d588_tail(void);
int FUN_0004d594(void){
    if(*(volatile char*)0x2001d44b==0) return 0;
    int iVar3=FUN_0004d56c();
    if(iVar3!=0){
        *(volatile int*)0x2000a0d8=*(volatile int*)0x2000a0d8-1;
        uint32_t* puVar6=(uint32_t*)0x000882a0;
        uint32_t* puVar1=(uint32_t*)0x000882b0;
        while(1){
            if(puVar1<puVar6){ FUN_0007e2fa(); FUN_0007e2fa(); FUN_0007e2ec(0x99cbd,0x1c5); }
            if(puVar1<=puVar6) break;
            if(*(volatile char*)(*(volatile int*)(puVar6+1)+5)!=0){
                (*(void(* volatile*)(void*,int))(*(volatile int*)puVar6))(puVar6,iVar3);
            }
            puVar6=puVar6+4;
        }
        FUN_0004d578(iVar3);
    }
    volatile uint32_t* puVar2=(volatile uint32_t*)0x200056a0;
    if(*(volatile int*)0x2000a0d4>0){
        int64_t lVar8=thunk_FUN_00074f68();
        uint64_t prod=(uint64_t)lVar8*1000;
        uint32_t hi=(uint32_t)(prod>>32);
        uint32_t uVar5=((uint32_t)prod>>0xf)|(hi<<17);
        uint32_t p2_0=puVar2[0];
        uint32_t p2_1=puVar2[1];
        uint32_t uVar4=((hi>>0xf)-p2_1)-(uint32_t)(uVar5<p2_0);
        int bVar7=(1000<(uVar5-p2_0));
        if(uVar4!=0 || uVar4<(uint32_t)bVar7){ FUN_0004d4a8(p2_1,uVar4-!bVar7); }
    }
    uint32_t uVar4=puVar2[0];
    puVar2[0]=uVar4+1000;
    puVar2[1]=puVar2[1]+(uint32_t)(0xfffffc17u<uVar4);
    return FUN_0004d588_tail();
}

