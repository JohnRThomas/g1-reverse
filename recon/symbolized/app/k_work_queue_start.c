#include "g1_app_symbols.h"
#include "../../headers/g1_log.h"
/* readable reconstruction; identity: FUN_000730e8 @ 0x000730e8
 * public-name: k_work_queue_start
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_impl_k_thread_create                   <= FUN_00071eac @ 0x00071eac
 *   k_work_queue_start                       <= FUN_000730e8 @ 0x000730e8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   posix_stub_enosys                        <= FUN_00086412 @ 0x00086412
 * address symbols (name @ address):
 *   rodata_72ab1                             @ 0x00072ab1
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f586b                             @ 0x000f586b
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f82a5                             @ 0x000f82a5
 *   rodata_f82ab                             @ 0x000f82ab
 */
/* Reconstructed FUN_000730e8 @ 0x730e8  (parity: 300/300 trials, PROVEN) */
extern int assert_post_action(int, int);
extern void z_impl_k_thread_create(int,int,unsigned,int,int,int,int,unsigned,int);
extern void posix_stub_enosys(int);
extern void FUN_0008641c(int);
void k_work_queue_start(unsigned int param_1, unsigned int param_2, unsigned long param_3, unsigned long param_4, unsigned long param_5) {
  unsigned uVar1;
  if(param_1==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f586b) /*=0xf586b*/,((unsigned long)&rodata_f820f) /*=0xf820f*/,0x2c8); uVar1=0x2c8;
    assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/,uVar1); return;
  } else if(param_2==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f82a5) /*=0xf82a5*/,((unsigned long)&rodata_f820f) /*=0xf820f*/,0x2c9); uVar1=0x2c9;
    assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/,uVar1); return;
  } else {
    if((*(volatile unsigned*)(param_1+0xf0)&1)!=0){
      printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f82ab) /*=0xf82ab*/,((unsigned long)&rodata_f820f) /*=0xf820f*/,0x2ca);
      assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/,0x2ca);
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
    z_impl_k_thread_create(param_1,param_2,param_3,((unsigned long)&rodata_72ab1) /*=0x72ab1*/,param_1,0,0,param_4,0);
    if(param_5!=0 && *param_5!=0) posix_stub_enosys(param_1);
    FUN_0008641c(param_1); return;
  }
}
