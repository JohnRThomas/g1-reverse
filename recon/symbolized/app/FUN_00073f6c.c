#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00073f6c @ 0x00073f6c
 * public-name: FUN_00073f6c
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   pend_locked                              <= FUN_00073f3c @ 0x00073f3c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f8584                             @ 0x000f8584
 *   _kernel                                  @ 0x2000b448
 *   g_pend_locked_thread_tmp                 @ 0x2000b484
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_00073f6c @ 0x73f6c  (parity: 300/300 trials, PROVEN) */
extern int z_spin_lock_valid(int,int,int,int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void pend_locked(int,int,int,int);
extern void FUN_000501d4(int);
extern void printk(int,...);
extern void assert_post_action(int,...);
void FUN_00073f6c(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6){
  int iVar3 = ((unsigned long)&_kernel) /*=0x2000b448*/;
  int iVar5 = ((unsigned long)&sched_spinlock) /*=0x2000b490*/;
  (void)param_4;
  *(volatile int*)((unsigned long)&g_pend_locked_thread_tmp) /*=0x2000b484*/ = *(volatile int*)(iVar3+8);
  if (param_1 == iVar5){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f8584) /*=0xf8584*/,((unsigned long)&rodata_f82f4) /*=0xf82f4*/,0x35f);
    assert_post_action(((unsigned long)&rodata_f82f4) /*=0xf82f4*/,0x35f);
    return;
  }
  if (z_spin_lock_valid(iVar5, param_2, 0x20, 0) == 0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f0920) /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
    printk(((unsigned long)&rodata_f0935) /*=0xf0935*/,iVar5);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
    return;
  }
  z_spin_lock_set_owner(iVar5);
  pend_locked(*(volatile int*)(iVar3+8), param_3, param_5, param_6);
  if (z_spin_unlock_valid(param_1) == 0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f08f4) /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x111);
    printk(((unsigned long)&rodata_f090b) /*=0xf090b*/,param_1);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x111);
    return;
  }
  if (z_spin_unlock_valid(iVar5) == 0){
    printk(((unsigned long)&rodata_99cbd) /*=0x99cbd*/,((unsigned long)&rodata_f08f4) /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x111);
    printk(((unsigned long)&rodata_f090b) /*=0xf090b*/,iVar5);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x111);
    return;
  }
  FUN_000501d4(param_2);
}
