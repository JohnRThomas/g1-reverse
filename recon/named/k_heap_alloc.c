/* readable reconstruction; identity: FUN_000719f4 @ 0x000719f4
 * public-name: k_heap_alloc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sys_heap_aligned_alloc                   <= FUN_0004b2b0 @ 0x0004b2b0
 *   k_heap_alloc                             <= FUN_000719f4 @ 0x000719f4
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   z_pend_curr                              <= FUN_00073f6c @ 0x00073f6c
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 *   sys_timepoint_calc                       <= FUN_0008669c @ 0x0008669c
 *   sys_timepoint_timeout                    <= FUN_000866e4 @ 0x000866e4
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f7dbe                             @ 0x000f7dbe
 *   rodata_f7df6                             @ 0x000f7df6
 */
/* Reconstructed FUN_000719f4 @ 0x719f4  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../headers/g1_log.h"
extern void sys_timepoint_calc(void*);
extern int z_spin_lock_valid(unsigned int*);
extern int z_spin_lock_set_owner(unsigned int*);
extern int z_spin_unlock_valid(int);
extern long long sys_heap_aligned_alloc(int,unsigned,unsigned);
extern void sys_timepoint_timeout(void*,int,int,int);
extern void z_pend_curr(int, int, int, int, int, int);
extern int assert_post_action(int, int);

static inline unsigned gp(void){unsigned r;__asm volatile("mrs %0, basepri":"=r"(r));return r;}
static inline void spm(unsigned v){__asm volatile("msr basepri_max, %0"::"r"(v):"memory");}
static inline void sp(unsigned v){__asm volatile("msr basepri, %0"::"r"(v):"memory");}
static inline void ib(void){__asm volatile("isb sy":::"memory");}
static inline unsigned gi(void){unsigned r;__asm volatile("mrs %0, ipsr":"=r"(r));return r;}

int k_heap_alloc(int param_1, unsigned param_2, unsigned param_3, unsigned param_4, int param_5, int param_6){
  int local_30, iStack_2c;
  sys_timepoint_calc(&local_30);
  int iVar4 = local_30;
  int iVar2 = iStack_2c;
  int iVar7 = param_1 + 0x14;
  unsigned uVar8, uVar5;
  long long uVar9 = 0;
  uVar8 = gp(); spm(0x20); ib();
  int iVar3 = z_spin_lock_valid(iVar7);
  if(iVar3 == 0){
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0x000f08c7,0x72);
    printk(((unsigned long)"\tInvalid spinlock %p\n"),iVar7);
    uVar5 = 0x72; uVar8 = 0x000f08c7;
    goto EC;
  }
  z_spin_lock_set_owner(iVar7);
  unsigned uVar6 = gi();
  if(uVar6 == 0 || (param_5 == 0 && param_6 == 0)){
    while(1){
      uVar9 = sys_heap_aligned_alloc(param_1, param_2, param_3);
      if((int)uVar9 != 0 || (param_5 == 0 && param_6 == 0)) break;
      sys_timepoint_timeout(&local_30, (int)((unsigned long long)uVar9 >> 0x20), iVar4, iVar2);
      param_6 = iStack_2c;
      param_5 = local_30;
      z_pend_curr(iVar7, uVar8, param_1 + 0xc, iStack_2c, local_30, iStack_2c);
      uVar8 = gp(); spm(0x20); ib();
      iVar3 = z_spin_lock_valid(iVar7);
      if(iVar3 == 0){
        printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0x000f08c7,0x72);
        printk(((unsigned long)"\tInvalid spinlock %p\n"),iVar7);
        uVar5 = 0x72; uVar8 = 0x000f08c7;
        goto EC;
      }
      z_spin_lock_set_owner(iVar7);
    }
    int iVar4b = z_spin_unlock_valid(iVar7);
    if(iVar4b != 0){
      sp(uVar8); ib();
      return (int)uVar9;
    }
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0x000f08c7,0xf0);
    printk(((unsigned long)"\tNot my spinlock %p\n"),iVar7);
    uVar5 = 0xf0; uVar8 = 0x000f08c7;
  } else {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),0x000f7df6,0x000f7dbe,0x4a);
    printk(0x000f53ff);
    uVar5 = 0x4a; uVar8 = 0x000f7dbe;
  }
EC:
  assert_post_action(uVar8, uVar5);
  return 0;
}
