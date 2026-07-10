/* named: FUN_00073f6c */
/* globals referenced:
//   0x2000b448  g_zephyr_kernel              
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
  int iVar3 = 0x2000b448;
  int iVar5 = 0x2000b490;
  (void)param_4;
  *(volatile int*)0x2000b484UL = *(volatile int*)(iVar3+8);
  if (param_1 == iVar5){
    printk(0x00099cbd,0x000f8584,0x000f82f4,0x35f);
    assert_post_action(0x000f82f4,0x35f);
    return;
  }
  if (z_spin_lock_valid(iVar5, param_2, 0x20, 0) == 0){
    printk(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    printk(0x000f0935,iVar5);
    assert_post_action(0x000f08c7,0x72);
    return;
  }
  z_spin_lock_set_owner(iVar5);
  pend_locked(*(volatile int*)(iVar3+8), param_3, param_5, param_6);
  if (z_spin_unlock_valid(param_1) == 0){
    printk(0x00099cbd,0x000f08f4,0x000f08c7,0x111);
    printk(0x000f090b,param_1);
    assert_post_action(0x000f08c7,0x111);
    return;
  }
  if (z_spin_unlock_valid(iVar5) == 0){
    printk(0x00099cbd,0x000f08f4,0x000f08c7,0x111);
    printk(0x000f090b,iVar5);
    assert_post_action(0x000f08c7,0x111);
    return;
  }
  FUN_000501d4(param_2);
}

