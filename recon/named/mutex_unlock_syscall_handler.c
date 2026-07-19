/* readable reconstruction; identity: FUN_000745c8 @ 0x000745c8
 * public-name: mutex_unlock_syscall_handler
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   arch_swap                                <= FUN_000501d4 @ 0x000501d4
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   sched_update_cache                       <= FUN_000737d8 @ 0x000737d8
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   mutex_unlock_syscall_handler             <= FUN_000745c8 @ 0x000745c8
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f53ff                             @ 0x000f53ff
 *   rodata_f801f                             @ 0x000f801f
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f84d6                             @ 0x000f84d6
 *   _kernel                                  @ 0x2000b448
 *   sched_spinlock                           @ 0x2000b490
 */
/* Reconstructed FUN_000745c8 @ 0x745c8  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int arch_swap(int,...);
extern int z_spin_lock_valid(int,...);
extern int z_spin_unlock_valid(int,...);
extern int z_spin_lock_set_owner(int,...);
extern int sched_update_cache(int,...);
extern int dlist_unlink_node(int,...);
extern int assert_post_action(int,...);
extern int printk(int,...);
void mutex_unlock_syscall_handler(void)
{
  if (__get_IPSR() != 0) {
    printk(0x99cbd,0xf801f,0xf82f4,0x57a);
    printk(0xf53ff);
    assert_post_action(0xf82f4,0x57a);
    return;
  }
  unsigned key = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();
  int iVar2 = z_spin_lock_valid(0x2000b490);
  int iVar3 = 0x2000b448;
  if (iVar2 == 0) {
    printk(0x99cbd,0xf0920,0xf08c7,0x72);
    printk(0xf0935,0x2000b490);
    assert_post_action(0xf08c7,0x72);
    return;
  }
  z_spin_lock_set_owner(0x2000b490);
  int *puVar9 = (int*)(iVar3+0x1c);
  *(unsigned char*)(*(int*)(iVar3+8)+0xd) &= 0x7f;
  dlist_unlink_node((int)puVar9);
  int *piVar8 = *(int**)(iVar3+8);
  *(unsigned char*)((int)piVar8+0xd) |= 0x80;
  if (piVar8 == (int*)0x20006720) {
    printk(0x99cbd,0xf84d6,0xf82f4,0xc1);
    assert_post_action(0xf82f4,0xc1);
    return;
  }
  int *puVar6 = *(int**)(iVar3+0x1c);
  int *puVar5 = *(int**)(iVar3+0x20);
  if (puVar6 == puVar9) puVar6 = 0;
  for (; puVar6 != 0; puVar6 = (int*)*puVar6) {
    if ((*(signed char*)((int)piVar8+0xe) != *(signed char*)((int)puVar6+0xe)) &&
        (*(signed char*)((int)piVar8+0xe) < *(signed char*)((int)puVar6+0xe))) {
      int *pv = (int*)puVar6[1];
      *piVar8 = (int)puVar6; piVar8[1]=(int)pv; *pv=(int)piVar8; puVar6[1]=(int)piVar8;
      goto L;
    }
    if (puVar6 == puVar5) break;
  }
  *piVar8 = (int)puVar9; piVar8[1]=(int)puVar5; *puVar5=(int)piVar8; *(int**)(iVar3+0x20)=piVar8;
L:
  sched_update_cache(1);
  int r = z_spin_unlock_valid(0x2000b490);
  if (r != 0) { arch_swap(key); return; }
  printk(0x99cbd,0xf08f4,0xf08c7,0x111);
  printk(0xf090b,0x2000b490);
  assert_post_action(0xf08c7,0x111);
}
