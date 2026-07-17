#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00071eac @ 0x00071eac
 * public-name: FUN_00071eac
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sched_thread_ready                       <= FUN_00073a78 @ 0x00073a78
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_86661                             @ 0x00086661
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f7f4b                             @ 0x000f7f4b
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f8031                             @ 0x000f8031
 */
/* Reconstructed FUN_00071eac @ 0x71eac  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern void FUN_00071df8(int,int,int,int,int,int,int,int,int);
extern void sched_thread_ready(int);
extern void FUN_00074bf4(int,unsigned int,int,int,int,int,int,int,int,unsigned int);
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,unsigned int) __attribute__((noreturn));
int FUN_00071eac(int param_1,int p2,int p3,int p4,int s0,int s1,int s2,int s3,int s4,int s5,int s6,int s7){
  unsigned int uVar2=__get_IPSR() & 0x1f;
  if (uVar2 != 0) {
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f801f) /*=0xf801f*/,((unsigned long)&rodata_f7f4b) /*=0xf7f4b*/,0x28c);
    printk(((unsigned long)&rodata_f8031) /*=0xf8031*/);
    assert_post_action(((unsigned long)&rodata_f7f4b) /*=0xf7f4b*/,0x28c);
  }
  FUN_00071df8(param_1,p2,p3,p4,s0,s1,s2,s3,s4);
  if(s7!=-1 || s6!=-1){
    if(s7==0 && s6==0){
      sched_thread_ready(param_1);
    } else {
      FUN_00074bf4(param_1+0x18,((unsigned long)&rodata_86661) /*=0x86661*/,s6,s7,s0,s1,s2,s3,s4,uVar2);
    }
  }
  return param_1;
}
