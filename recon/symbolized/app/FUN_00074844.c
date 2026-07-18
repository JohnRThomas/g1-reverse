#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00074844 @ 0x00074844
 * public-name: FUN_00074844
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f82f4                             @ 0x000f82f4
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_00074844 @ 0x74844  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000741a4(int);
extern int FUN_000746fc(void);
extern int assert_post_action(int,int);
extern int printk(int,...);
uint32_t FUN_00074844(int param_1,int param_2,int param_3,int param_4){
  uint32_t ipsr;
  __asm volatile("mrs %0, ipsr":"=r"(ipsr));
  if(ipsr != 0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/, ((unsigned long)&rodata_f801f) /*=0xf801f*/, ((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x5c1, param_4);
    printk(((unsigned long)&rodata_f53ff) /*=0xf53ff*/);
    assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/, 0x5c1);
  }
  if(param_2==-1 && param_1==-1){
    FUN_000741a4(*(volatile int*)(((unsigned long)&_kernel) /*=0x2000b448*/+8));
    return 0xffffffff;
  }
  int iVar2 = FUN_000746fc();
  return (uint32_t)(((int64_t)iVar2 * 1000) >> 15);
}
