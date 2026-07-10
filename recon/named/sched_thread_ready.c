/* named: sched_thread_ready */
/* Reconstructed sched_thread_ready @ 0x73a78  (parity: 300/300 trials, PROVEN) */

extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void sched_ready_queue_insert(int);
extern void z_reschedule(int,int);
extern void assert_post_action(int,int);
extern int printk(int,...);
void sched_thread_ready(int param_1,int param_2,int param_3,int param_4){
  int r=z_spin_lock_valid(0x2000b490);
  if(r==0){ printk(0x99cbd,0xf0920,0xf08c7,0x72,param_4); printk(0xf0935,0x2000b490); assert_post_action(0xf08c7,0x72); }
  z_spin_lock_set_owner(0x2000b490);
  unsigned char b=*(volatile unsigned char*)(param_1+0xd);
  if((int)((unsigned)b<<0x1d) < 0){
    *(volatile unsigned char*)(param_1+0xd) = b & 0xfb;
    sched_ready_queue_insert(param_1);
    z_reschedule(0x2000b490, 0);
    return;
  }
  r=z_spin_unlock_valid(0x2000b490);
  if(r!=0) return;
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0,param_4); printk(0xf090b,0x2000b490); assert_post_action(0xf08c7,0xf0);
}

