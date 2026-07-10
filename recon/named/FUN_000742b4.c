/* named: FUN_000742b4 */
/* Reconstructed FUN_000742b4 @ 0x742b4  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_abort_thread_timeout(int);
extern void FUN_00074d74(int);
extern void assert_post_action(int,int);
extern int printk(int,...);
void FUN_000742b4(int param_1,int param_2,int param_3,int param_4){
  int r=z_spin_lock_valid(0x2000b490);
  if(r==0){ printk(0x99cbd,0xf0920,0xf08c7,0x72,param_4); printk(0xf0935,0x2000b490); assert_post_action(0xf08c7,0x72); }
  z_spin_lock_set_owner(0x2000b490);
  if(*(int*)(param_1+8)!=0) z_abort_thread_timeout(param_1);
  r=z_spin_unlock_valid(0x2000b490);
  if(r!=0){ FUN_00074d74(param_1+0x18); return; }
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0,param_4); printk(0xf090b,0x2000b490); assert_post_action(0xf08c7,0xf0);
}

