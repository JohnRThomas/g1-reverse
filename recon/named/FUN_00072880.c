/* named: FUN_00072880 */
/* Reconstructed FUN_00072880 @ 0x72880  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(int);
extern void z_spin_lock_set_owner(int);
extern void z_ready_thread_locked(void);
extern void z_reschedule(int,int);
extern int z_unpend_first_thread(int);
extern void assert_post_action(int,int);
extern void printk(int,...);
extern void z_handle_obj_poll_events(int,int);
void FUN_00072880(int param_1, int param_2, int param_3, int param_4){
  unsigned int r5;
  int r3v = 0x20;
  __asm volatile("mrs %0, basepri" : "=r"(r5));
  __asm volatile("msr basepri_max, %0" :: "r"(r3v));
  __asm volatile("isb");
  int r0 = z_spin_lock_valid(0x2000b474);
  if(r0 == 0){
    printk(0x99cbd, 0xf0920, 0xf08c7, 0x72);
    printk(0xf0935, 0x2000b474);
    assert_post_action(0xf08c7, 0x72);
    return;
  }
  z_spin_lock_set_owner(0x2000b474);
  int r0b = z_unpend_first_thread(param_1);
  if(r0b == 0){
    int a = *(volatile int*)(param_1+8);
    int b = *(volatile int*)(param_1+0xc);
    if(b != a) a = a + 1;
    *(volatile int*)(param_1+8) = a;
    z_handle_obj_poll_events(param_1+0x10, 2);
  } else {
    *(volatile int*)(r0b + 0x90) = 0;
    z_ready_thread_locked();
  }
  z_reschedule(0x2000b474, r5);
}

