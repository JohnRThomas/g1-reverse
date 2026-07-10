#include "g1_app_symbols.h"
/* named: log_process */
/* globals referenced:
//   0x000882b0  __settings_handler_static_list_start 
*/
/* Reconstructed log_process @ 0x4d594  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int log_dropped(uint32_t,uint32_t);
extern int mpsc_pbuf_claim(void);
extern int mpsc_pbuf_free(int);
extern void assert_post_action(uint32_t,int);
extern void printk();
extern int64_t thunk_FUN_00074f68(void);
extern int FUN_0004d588_tail(void);
int log_process(void){
    if(*(volatile char*)((uintptr_t)&log_process_active) /*=0x2001d44b*/==0) return 0;
    int iVar3=mpsc_pbuf_claim();
    if(iVar3!=0){
        *(volatile int*)((uintptr_t)&log_buffered_cnt) /*=0x2000a0d8*/=*(volatile int*)((uintptr_t)&log_buffered_cnt) /*=0x2000a0d8*/-1;
        uint32_t* puVar6=(uint32_t*)((uintptr_t)&tbl_880d8) /*=0x882a0*/;
        uint32_t* puVar1=(uint32_t*)((uintptr_t)&__settings_handler_static_list_start) /*=0x882b0*/;
        while(1){
            if(puVar1<puVar6){ printk(); printk(); assert_post_action("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,0x1c5); }
            if(puVar1<=puVar6) break;
            if(*(volatile char*)(*(volatile int*)(puVar6+1)+5)!=0){
                (*(void(* volatile*)(void*,int))(*(volatile int*)puVar6))(puVar6,iVar3);
            }
            puVar6=puVar6+4;
        }
        mpsc_pbuf_free(iVar3);
    }
    volatile uint32_t* puVar2=(volatile uint32_t*)((uintptr_t)&log_process_timestamp) /*=0x200056a0*/;
    if(*(volatile int*)((uintptr_t)&log_backend_count) /*=0x2000a0d4*/>0){
        int64_t lVar8=thunk_FUN_00074f68();
        uint64_t prod=(uint64_t)lVar8*1000;
        uint32_t hi=(uint32_t)(prod>>32);
        uint32_t uVar5=((uint32_t)prod>>0xf)|(hi<<17);
        uint32_t p2_0=puVar2[0];
        uint32_t p2_1=puVar2[1];
        uint32_t uVar4=((hi>>0xf)-p2_1)-(uint32_t)(uVar5<p2_0);
        int bVar7=(1000<(uVar5-p2_0));
        if(uVar4!=0 || uVar4<(uint32_t)bVar7){ log_dropped(p2_1,uVar4-!bVar7); }
    }
    uint32_t uVar4=puVar2[0];
    puVar2[0]=uVar4+1000;
    puVar2[1]=puVar2[1]+(uint32_t)(0xfffffc17u<uVar4);
    return FUN_0004d588_tail();
}

