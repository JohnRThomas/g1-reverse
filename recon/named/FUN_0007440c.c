/* named: FUN_0007440c */
/* Reconstructed FUN_0007440c @ 0x7440c  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_abort_thread_timeout(int);
extern void assert_post_action(int,int);
extern int printk(int,...);
int FUN_0007440c(int *param_1){
  int r=z_spin_lock_valid(0x2000b490);
  if(r==0){ printk(0x99cbd,0xf0920,0xf08c7,0x72); printk(0xf0935,0x2000b490); assert_post_action(0xf08c7,0x72); }
  z_spin_lock_set_owner(0x2000b490);
  int *piVar4=(int*)*param_1;
  if(param_1==piVar4) piVar4=0;
  else if(piVar4!=0) z_abort_thread_timeout((int)piVar4);
  r=z_spin_unlock_valid(0x2000b490);
  if(r!=0) return (int)piVar4;
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0); printk(0xf090b,0x2000b490); assert_post_action(0xf08c7,0xf0);
  return 0;
}

