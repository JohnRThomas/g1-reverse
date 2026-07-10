/* named: k_uptime_ticks_impl */
/* Reconstructed k_uptime_ticks_impl @ 0x74f68  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(unsigned int);
extern void z_spin_lock_set_owner(unsigned int);
extern unsigned int rtc_get_elapsed_cycles_since_baseline(void);
extern int z_spin_unlock_valid(unsigned int);
extern void printk(unsigned int,...);
extern void assert_post_action(unsigned int,...);
unsigned long long k_uptime_ticks_impl(void){
  unsigned int uVar6=0;
  int iVar2=z_spin_lock_valid(0x2000b498);
  if(iVar2==0){
    printk(0x00099cbd,0x000f0920,0x000f08c7,0x72);
    printk(0x000f0935,0x2000b498);
    assert_post_action(0x000f08c7,0x72);
  }
  z_spin_lock_set_owner(0x2000b498);
  unsigned int uVar3=rtc_get_elapsed_cycles_since_baseline();
  unsigned int uVar4=*(volatile unsigned int*)0x200069e0UL;
  unsigned int uVar5=*(volatile unsigned int*)0x200069e4UL;
  int iVar2b=z_spin_unlock_valid(0x2000b498);
  if(iVar2b==0){
    printk(0x00099cbd,0x000f08f4,0x000f08c7,0xf0);
    printk(0x000f090b,0x2000b498);
    assert_post_action(0x000f08c7,0xf0);
  }
  (void)uVar6;
  unsigned int r0res=uVar3+uVar4;
  unsigned int r1res=uVar5 + (unsigned int)((int)uVar3>>31) + (unsigned int)(((unsigned long long)uVar3+uVar4)>>32);
  return ((unsigned long long)r1res<<32)|r0res;
}

