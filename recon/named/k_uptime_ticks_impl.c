/* readable reconstruction; identity: FUN_00074f68 @ 0x00074f68
 * public-name: k_uptime_ticks_impl
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   rtc_get_elapsed_cycles_since_baseline    <= FUN_00074b68 @ 0x00074b68
 *   k_uptime_ticks_impl                      <= FUN_00074f68 @ 0x00074f68
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   g_curr_tick_lo                           @ 0x200069e0
 *   g_curr_tick_hi                           @ 0x200069e4
 *   g_timeout_list_spinlock                  @ 0x2000b498
 */
/* Reconstructed FUN_00074f68 @ 0x74f68  (parity: 80/80 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern int z_spin_lock_valid(unsigned int);
extern void z_spin_lock_set_owner(unsigned int);
extern unsigned int rtc_get_elapsed_cycles_since_baseline(void);
extern int z_spin_unlock_valid(unsigned int);
extern void assert_post_action(unsigned int,...);
unsigned long long k_uptime_ticks_impl(void){
  unsigned int uVar6=0;
  int iVar2=z_spin_lock_valid(0x2000b498);
  if(iVar2==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0x000f08c7,0x72);
    printk(((unsigned long)"\tInvalid spinlock %p\n"),0x2000b498);
    assert_post_action(0x000f08c7,0x72);
  }
  z_spin_lock_set_owner(0x2000b498);
  unsigned int uVar3=rtc_get_elapsed_cycles_since_baseline();
  unsigned int uVar4=*(volatile unsigned int*)0x200069e0UL;
  unsigned int uVar5=*(volatile unsigned int*)0x200069e4UL;
  int iVar2b=z_spin_unlock_valid(0x2000b498);
  if(iVar2b==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0x000f08c7,0xf0);
    printk(((unsigned long)"\tNot my spinlock %p\n"),0x2000b498);
    assert_post_action(0x000f08c7,0xf0);
  }
  (void)uVar6;
  unsigned int r0res=uVar3+uVar4;
  unsigned int r1res=uVar5 + (unsigned int)((int)uVar3>>31) + (unsigned int)(((unsigned long long)uVar3+uVar4)>>32);
  return ((unsigned long long)r1res<<32)|r0res;
}
