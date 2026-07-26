#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00072e9c @ 0x00072e9c
 * public-name: k_work_busy_get
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   k_work_busy_get                          <= FUN_00072e9c @ 0x00072e9c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   timer_spinlock                           @ 0x2000b480
 */
/* Reconstructed FUN_00072e9c @ 0x72e9c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int z_spin_lock_valid(uint32_t);
extern int z_spin_unlock_valid(uint32_t);
extern void z_spin_lock_set_owner(uint32_t);
extern void assert_post_action(uint32_t,uint32_t);
extern void printk(uint32_t,uint32_t,uint32_t,uint32_t,uint32_t);
unsigned k_work_busy_get(int param_1,uint32_t p2,uint32_t p3,uint32_t p4){
  int iVar2=z_spin_lock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
  if(iVar2==0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_lock_valid(l)") /*=0xf0920*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72,p4);
    printk(((unsigned long)"\tInvalid spinlock %p\n") /*=0xf0935*/,((unsigned long)&timer_spinlock) /*=0x2000b480*/,0,0,0);
    assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0x72);
    return 0;
  }
  z_spin_lock_set_owner(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
  unsigned uVar3=*(volatile unsigned*)(param_1+0xc) & 0xf;
  iVar2=z_spin_unlock_valid(((unsigned long)&timer_spinlock) /*=0x2000b480*/);
  if(iVar2!=0) return uVar3;
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n") /*=0x99cbd*/,((unsigned long)"z_spin_unlock_valid(l)") /*=0xf08f4*/,((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0,p4);
  printk(((unsigned long)"\tNot my spinlock %p\n") /*=0xf090b*/,((unsigned long)&timer_spinlock) /*=0x2000b480*/,0,0,0);
  assert_post_action(((unsigned long)&rodata_f08c7) /*=0xf08c7*/,0xf0);
  return 0;
}
