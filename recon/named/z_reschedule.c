/* readable reconstruction; identity: FUN_000739f0 @ 0x000739f0
 * public-name: z_reschedule
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_000739f0 @ 0x739f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_unlock_valid(int);
extern void FUN_000501d4(int);
extern void assert_post_action(int,int);
extern void printk(int,...);
void z_reschedule(int param_1, int param_2){
  unsigned int r6;
  int r0v;
  if(param_2 == 0){
    __asm volatile("mrs %0, ipsr" : "=r"(r6));
    if(r6 == 0){
      volatile int *g = (volatile int*)0x2000b448UL;
      if(g[6] != g[2]){
        r0v = z_spin_unlock_valid(param_1);
        if(r0v != 0){ FUN_000501d4(r6); return; }
        printk(0x99cbd, 0xf08f4, 0xf08c7, 0x111);
        printk(0xf090b, param_1);
        assert_post_action(0xf08c7, 0x111);
        return;
      }
    }
  }
  r0v = z_spin_unlock_valid(param_1);
  if(r0v != 0){
    __asm volatile("msr basepri, %0" :: "r"(param_2));
    __asm volatile("isb");
    return;
  }
  printk(0x99cbd, 0xf08f4, 0xf08c7, 0xf0);
  printk(0xf090b, param_1);
  assert_post_action(0xf08c7, 0xf0);
}
