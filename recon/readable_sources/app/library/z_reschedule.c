#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   0x00073a64       => struct g1_layout_z_kernel_sched_state__global_1405      [global_1405; library]
 * Raw function identity: 0x000739f0.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_000739f0 @ 0x000739f0
 * public-name: z_reschedule
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_swap                                <= FUN_000501d4 @ 0x000501d4
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_reschedule                             <= FUN_000739f0 @ 0x000739f0
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   _kernel                                  @ 0x2000b448
 */
/* Reconstructed FUN_000739f0 @ 0x739f0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_unlock_valid(int);
extern void arch_swap(int);
extern void assert_post_action(int,int);
extern void printk(int,...);
void z_reschedule(int param_1, int param_2){
  unsigned int r6;
  int r0v;
  if(param_2 == 0){
    __asm volatile("mrs %0, ipsr" : "=r"(r6));
    if(r6 == 0){
      volatile int *g = (volatile int*)((unsigned long)&_kernel) /*=0x2000b448*/;
      if(g[6] != g[2]){
        r0v = z_spin_unlock_valid(param_1);
        if(r0v != 0){ arch_swap(r6); return; }
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x111);
        printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, param_1);
        assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0x111);
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
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/, ((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/, ((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
  printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/, param_1);
  assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/, 0xf0);
}
