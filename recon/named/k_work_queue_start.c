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
    printk(0x00099cbd,0x000f586b,0x000f820f,0x2c8); uVar1=0x2c8;
    assert_post_action(0x000f820f,uVar1); return;
  } else if(param_2==0){
    printk(0x00099cbd,0x000f82a5,0x000f820f,0x2c9); uVar1=0x2c9;
    assert_post_action(0x000f820f,uVar1); return;
  } else {
    if((*(volatile unsigned*)(param_1+0xf0)&1)!=0){
      printk(0x00099cbd,0x000f82ab,0x000f820f,0x2ca);
      assert_post_action(0x000f820f,0x2ca);
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
    FUN_00071eac(param_1,param_2,param_3,0x00072ab1,param_1,0,0,param_4,0);
    if(param_5!=0 && *param_5!=0) posix_stub_enosys(param_1);
    sched_thread_ready(param_1); return;
  }
}

