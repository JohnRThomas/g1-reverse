#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002bef4 @ 0x0002bef4
 * public-name: update_persist_task_status
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   display_close_screen                     <= FUN_00049858 @ 0x00049858
 * address symbols (name @ address):
 *   rodata_a2597                             @ 0x000a2597
 *   rodata_a25b9                             @ 0x000a25b9
 *   rodata_a25d9                             @ 0x000a25d9
 *   rodata_a2660                             @ 0x000a2660
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_persist_task_status_lock               @ 0x20018d9c
 *   g_persist_task_status                    @ 0x20018d9d
 */
/* Reconstructed update_persist_task_status @ 0x2bef4  (parity: 3/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
extern void DEBUG_PRINT(int,int,uint);
extern void debug_print(void);
extern void display_close_screen(int);
extern void FUN_0007cdf8(void);
uint update_persist_task_status(int param_1, uint param_2, uint param_3){
    volatile char* pcVar2=(volatile char*)((unsigned long)&g_persist_task_status_lock) /*=0x20018d9c*/;
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
    display_close_screen(*(volatile uint8_t*)(param_1+0xd5));
    if(param_3==2){
        if(param_2>0x10) goto L8a;
        if((int)(((uint)0x10050>>(param_2&0xff))<<0x1f) >= 0) goto L8a;
        goto L4a;
    }
L9e:
    if(param_3==3){
        if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>0){
            if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0) DEBUG_PRINT(((unsigned long)&rodata_a25b9) /*=0xa25b9*/,((unsigned long)&rodata_a2660) /*=0xa2660*/,param_2); else debug_print();
        }
    } else {
        if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>0){
            if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0) DEBUG_PRINT(((unsigned long)&rodata_a25d9) /*=0xa25d9*/,((unsigned long)&rodata_a2660) /*=0xa2660*/,param_2); else debug_print();
        }
    }
    goto Ltail;
L4a:
    if(*(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/>0){
        if(*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/==0) DEBUG_PRINT(((unsigned long)&rodata_a2597) /*=0xa2597*/,((unsigned long)&rodata_a2660) /*=0xa2660*/,param_2); else debug_print();
    }
    if(param_2==0x10){
        char cVar1=*(volatile char*)(param_1+0xf98);
        *(volatile char*)((unsigned long)&g_persist_task_status) /*=0x20018d9d*/=cVar1;
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
