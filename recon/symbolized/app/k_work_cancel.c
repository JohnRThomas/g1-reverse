#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00072fe8 @ 0x00072fe8
 * public-name: k_work_cancel
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_work_cancel                            <= FUN_00072fe8 @ 0x00072fe8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   cancel_async_locked                      <= FUN_00086596 @ 0x00086596
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f820f                             @ 0x000f820f
 *   rodata_f8262                             @ 0x000f8262
 *   rodata_f82e0                             @ 0x000f82e0
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_00072fe8 @ 0x72fe8  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
#include "../../headers/g1_log.h"
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void assert_post_action(uint32_t,uint32_t);
extern uint32_t cancel_async_locked(int);

uint32_t k_work_cancel(int param_1, uint32_t param_2, uint32_t param_3, uint32_t param_4){
  uint32_t sb, uVar4;
  int iVar3;
  if (param_1 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f82e0) /*=0xf82e0*/,((unsigned long)&rodata_f820f) /*=0xf820f*/,0x221,param_4);
    assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/,0x221);
  }
  if ((int32_t)((uint32_t)*(int*)(param_1+0xc) << 0x17) < 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)&rodata_f8262) /*=0xf8262*/,((unsigned long)&rodata_f820f) /*=0xf820f*/,0x222,param_4);
    assert_post_action(((unsigned long)&rodata_f820f) /*=0xf820f*/,0x222);
  }
  __asm volatile("mrs %0, basepri" : "=r"(sb));
  __asm volatile("msr basepri_max, %0" :: "r"((uint32_t)0x20));
  __asm volatile("isb sy");
  iVar3 = z_spin_lock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
  if (iVar3 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72,param_4);
    printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/,((unsigned long)&timer_spinlock) /*=0x2000b480*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
  }
  z_spin_lock_set_owner(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
  uVar4 = cancel_async_locked(param_1);
  iVar3 = z_spin_unlock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
  if (iVar3 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0,param_4);
    printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/,((unsigned long)&timer_spinlock) /*=0x2000b480*/);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
  }
  __asm volatile("msr basepri, %0" :: "r"(sb));
  __asm volatile("isb sy");
  return uVar4;
}
