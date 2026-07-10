#include "g1_app_symbols.h"
/* named: k_work_queue_start */
/* Reconstructed k_work_queue_start @ 0x730e8  (parity: 300/300 trials, PROVEN) */
extern void printk(int,...);
extern void assert_post_action(int,...);
extern void FUN_00071eac(int,int,unsigned,int,int,int,int,unsigned,int);
extern void posix_stub_enosys(int);
extern void sched_thread_ready(int);
void k_work_queue_start(int param_1,int param_2,unsigned param_3,unsigned param_4,int *param_5){
  unsigned uVar1;
  if(param_1==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"queue" /*=0xf586b*/,"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x2c8); uVar1=0x2c8;
    assert_post_action("WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,uVar1); return;
  } else if(param_2==0){
    printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"stack" /*=0xf82a5*/,"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x2c9); uVar1=0x2c9;
    assert_post_action("WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,uVar1); return;
  } else {
    if((*(volatile unsigned*)(param_1+0xf0)&1)!=0){
      printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"!flag_test(&queue->flags, K_WORK_QUEUE_STARTED_BIT)" /*=0xf82ab*/,"WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x2ca);
      assert_post_action("WEST_TOPDIR/zephyr/kernel/work.c" /*=0xf820f*/,0x2ca);
    }
    *(volatile unsigned*)(param_1+0xd8)=0;
    *(volatile unsigned*)(param_1+0xdc)=0;
    *(volatile int*)(param_1+0xe0)=param_1+0xe0;
    *(volatile int*)(param_1+0xe4)=param_1+0xe0;
    *(volatile int*)(param_1+0xe8)=param_1+0xe8;
    *(volatile int*)(param_1+0xec)=param_1+0xe8;
    if(param_5==0) uVar1=1;
    else { uVar1=0x101; if((char)param_5[1]==0) uVar1=1; }
    *(volatile unsigned*)(param_1+0xf0)=uVar1;
    FUN_00071eac(param_1,param_2,param_3,((uintptr_t)&tbl_72a68) /*=0x72ab1*/,param_1,0,0,param_4,0);
    if(param_5!=0 && *param_5!=0) posix_stub_enosys(param_1);
    sched_thread_ready(param_1); return;
  }
}

