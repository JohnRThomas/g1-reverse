/* named: FUN_00073960 */
/* Reconstructed FUN_00073960 @ 0x73960  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void z_abort_thread_timeout(int);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
void FUN_00073960(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar3=z_spin_lock_valid(0x2000b490);
  if(iVar3==0){
    printk(0x99cbd,0xf0920,0xf08c7,0x72,p4);
    printk(0xf0935,0x2000b490,0,0,0);
    assert_post_action(0xf08c7,0x72);
    return;
  }
  z_spin_lock_set_owner(0x2000b490);
  if(*(volatile int*)(param_1+8)!=0) z_abort_thread_timeout(param_1);
  iVar3=z_spin_unlock_valid(0x2000b490);
  if(iVar3!=0) return;
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0,p4);
  printk(0xf090b,0x2000b490,0,0,0);
  assert_post_action(0xf08c7,0xf0);
}

