/* readable reconstruction; identity: FUN_00074844 @ 0x00074844
 * public-name: k_sleep
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_thread_suspend                         <= FUN_000741a4 @ 0x000741a4
 *   z_tick_sleep                             <= FUN_000746fc @ 0x000746fc
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
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
extern int z_thread_suspend(int);
extern int z_tick_sleep(void);
extern int assert_post_action(int,int);
extern int printk(int,...);
uint32_t k_sleep(int param_1,int param_2,int param_3,int param_4){
  uint32_t ipsr;
  __asm volatile("mrs %0, ipsr":"=r"(ipsr));
  if(ipsr != 0){
    printk(0x00099cbd, 0x000f801f, 0x000f82f4, 0x5c1, param_4);
    printk(0x000f53ff);
    assert_post_action(0x000f82f4, 0x5c1);
  }
  if(param_2==-1 && param_1==-1){
    z_thread_suspend(*(volatile int*)(0x2000b448UL+8));
    return 0xffffffff;
  }
  int iVar2 = z_tick_sleep();
  return (uint32_t)(((int64_t)iVar2 * 1000) >> 15);
}
