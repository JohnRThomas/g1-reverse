/* readable reconstruction; identity: FUN_00074060 @ 0x00074060
 * public-name: FUN_00074060
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   dlist_unlink_node                        <= FUN_00073cdc @ 0x00073cdc
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f82f4                             @ 0x000f82f4
 *   rodata_f84d6                             @ 0x000f84d6
 *   g_sched_ready_runq                       @ 0x2000b464
 *   sched_spinlock_b490                      @ 0x2000b490
 */
/* Reconstructed FUN_00074060 @ 0x74060  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int z_spin_lock_valid(unsigned);
extern int z_spin_unlock_valid(unsigned);
extern void z_spin_lock_set_owner(unsigned);
extern void FUN_000737d8(int);
extern void dlist_unlink_node(void*,int*,int,int,unsigned);
extern void assert_post_action(unsigned,unsigned);
extern void printk(unsigned,unsigned,unsigned,unsigned);
int FUN_00074060(int *param_1, char param_2, unsigned param_3, unsigned param_4)
{
  unsigned basepri, uVar10, uVar5; int iVar3, iVar4;
  unsigned *puVar6, *puVar8, *puVar9; unsigned char bVar7;
  uVar10 = 0; uVar5 = 0;
  basepri = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20u);
  __ISB();
  uVar10 = basepri;
  iVar3 = z_spin_lock_valid(0x2000b490);
  if (iVar3 == 0) {
    printk(0x00099cbd, 0x000f0920, 0x000f08c7, 0x72);
    printk(0x000f0935, 0x2000b490, 0, 0);
    uVar5 = 0x72; uVar10 = 0x000f08c7;
  } else {
    z_spin_lock_set_owner(0x2000b490);
    puVar8 = (unsigned*)0x2000b464;
    if (((*(unsigned char*)((int)param_1 + 0xd) & 0x1f) == 0) && (param_1[6] == 0)) {
      bVar7 = *(unsigned char*)((int)param_1 + 0xd) & 0x7f;
      *(volatile unsigned char*)((int)param_1 + 0xd) = bVar7;
      dlist_unlink_node(puVar8, param_1, 0, bVar7, param_4);
      *(volatile char*)((int)param_1 + 0xe) = param_2;
      *(volatile unsigned char*)((int)param_1 + 0xd) = *(unsigned char*)((int)param_1 + 0xd) | 0x80;
      if (param_1 == (int*)0x20006720) {
        printk(0x00099cbd, 0x000f84d6, 0x000f82f4, 0xc1);
        uVar5 = 0xc1; uVar10 = 0x000f82f4;
        goto LABe0;
      }
      puVar9 = (unsigned*)0;
      if ((unsigned*)*puVar8 != puVar8) puVar9 = (unsigned*)*puVar8;
      puVar6 = (unsigned*)puVar8[1];
      for (; puVar9 != 0; puVar9 = (unsigned*)*puVar9) {
        if ((param_2 != *(char*)((int)puVar9 + 0xe)) && (param_2 < *(char*)((int)puVar9 + 0xe))) {
          puVar8 = (unsigned*)puVar9[1];
          *(volatile unsigned*)param_1 = (unsigned)puVar9;
          *(volatile unsigned*)(param_1+1) = (unsigned)puVar8;
          *(volatile unsigned*)puVar8 = (unsigned)param_1;
          *(volatile unsigned*)(puVar9+1) = (unsigned)param_1;
          goto LAB138;
        }
        if (puVar6 == puVar9) break;
      }
      *(volatile unsigned*)param_1 = (unsigned)puVar8;
      *(volatile unsigned*)(param_1+1) = (unsigned)puVar6;
      *(volatile unsigned*)puVar6 = (unsigned)param_1;
      *(volatile unsigned*)(puVar8+1) = (unsigned)param_1;
LAB138:
      FUN_000737d8(1);
    } else {
      iVar3 = 0;
      *(volatile char*)((int)param_1 + 0xe) = param_2;
    }
    iVar4 = z_spin_unlock_valid(0x2000b490);
    if (iVar4 != 0) {
      __set_BASEPRI(uVar10);
      __ISB();
      return iVar3;
    }
    printk(0x00099cbd, 0x000f08f4, 0x000f08c7, 0xf0);
    printk(0x000f090b, 0x2000b490, 0, 0);
    uVar5 = 0xf0; uVar10 = 0x000f08c7;
  }
LABe0:
  assert_post_action(uVar10, uVar5);
  return 0;
}
