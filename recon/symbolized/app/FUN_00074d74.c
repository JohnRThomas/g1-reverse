#include "g1_app_symbols.h"
/* named: FUN_00074d74 */
/* Reconstructed FUN_00074d74 @ 0x74d74  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void remove_timeout(int);
extern void assert_post_action(int,int);
extern int printk(int,...);
int FUN_00074d74(int *param_1,int param_2,int param_3,int param_4){
  int uVar4;
  int r=z_spin_lock_valid(((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
  if(r==0){ printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_lock_valid(l)" /*=0xf0920*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72,param_4); printk("\tInvalid spinlock %p\n" /*=0xf0935*/,((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/); assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0x72); }
  z_spin_lock_set_owner(((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
  if(*param_1==0) uVar4=0xffffffea; else { remove_timeout((int)param_1); uVar4=0; }
  r=z_spin_unlock_valid(((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/);
  if(r!=0) return uVar4;
  printk("ASSERTION FAIL [%s] @ %s:%d\n" /*=0x99cbd*/,"z_spin_unlock_valid(l)" /*=0xf08f4*/,"WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0,param_4); printk("\tNot my spinlock %p\n" /*=0xf090b*/,((uintptr_t)&g_timeout_list_spinlock) /*=0x2000b498*/); assert_post_action("WEST_TOPDIR/zephyr/include/zephyr/spinlock.h" /*=0xf08c7*/,0xf0);
  return 0;
}

