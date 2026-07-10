#include "g1_app_symbols.h"
/* named: net_buf_unref */
/* Reconstructed net_buf_unref @ 0x5f24c  (parity: 60/60 trials, PROVEN) */
#include <stdint.h>
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
extern void k_queue_prepend(int,int);
void net_buf_unref(int param_1){
  int iVar1=((uintptr_t)&acl_tx_pool) /*=0x20003a7c*/; char cVar2; int iVar4; void* pcVar3;
  if(param_1==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"buf" /*=0xf45be*/,"WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/,0x1d3);
    assert_post_action("WEST_TOPDIR/zephyr/subsys/net/buf.c" /*=0xf539a*/,0x1d3);
  }
  do{
    iVar4=*(int*)(param_1+4);
    cVar2=*(char*)(param_1+8)-1;
    *(char*)(param_1+8)=cVar2;
    if(cVar2!=0) return;
    if(*(int*)(param_1+0x14)!=0){
      if(((int)((unsigned int)*(unsigned char*)(param_1+9)<<0x1f))>=0){
        (**(void(***)(int))((unsigned int)*(unsigned char*)(param_1+10)*0x34+iVar1+0x2c))(param_1);
      }
      *(int*)(param_1+0x14)=0;
    }
    *(int*)(param_1+0xc)=0;
    *(int*)(param_1+4)=0;
    pcVar3=*(void**)((unsigned int)*(unsigned char*)(param_1+10)*0x34+iVar1+0x28);
    if(pcVar3==0) k_queue_prepend((int)((unsigned int)*(unsigned char*)(param_1+10)*0x34+iVar1),param_1);
    else ((void(*)(int))pcVar3)(param_1);
    param_1=iVar4;
  }while(iVar4!=0);
}

