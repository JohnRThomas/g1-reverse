/* named: FUN_0004b908 */
/* Reconstructed FUN_0004b908 @ 0x4b908  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0004b4fc(int,...);
extern int z_spin_lock_valid(int,...);
extern int z_spin_unlock_valid(int,...);
extern int z_spin_lock_set_owner(int,...);
extern int validate_args(int,...);
extern int notify_one(int,...);
extern int assert_post_action(int,...);
extern int printk(int,...);
unsigned int FUN_0004b908(int *param_1, int *param_2)
{
  unsigned int uVar3 = (unsigned int)validate_args(0);
  if ((int)uVar3 < 0) return uVar3;
  int *puVar8 = param_1 + 5;
  int iVar4 = z_spin_lock_valid((int)puVar8);
  if (iVar4 == 0) {
    printk(0x99cbd,0xf0920,0xf08c7,0x72);
    printk(0xf0935,(int)puVar8);
    assert_post_action(0xf08c7,0x72);
    return 0;
  }
  z_spin_lock_set_owner((int)puVar8);
  unsigned short uVar1 = *(unsigned short*)((int)param_1+0x1c);
  uVar3 = uVar1 & 7;
  unsigned int uVar7;
  if (*(short*)((int)param_1+0x1e) == -1) {
    uVar7 = 0xfffffff5;
    iVar4 = 0;
  } else {
    uVar7 = uVar3;
    if (uVar3 != 2) {
      switch (uVar3) {
        case 0: case 4: case 6:
          *param_2 = 0;
          if (param_1[1] == 0) { *param_1 = (int)param_2; param_1[1] = (int)param_2; }
          else { *(int*)param_1[1] = (int)param_2; param_1[1] = (int)param_2; }
          if ((uVar1 & 7) == 0) { FUN_0004b4fc((int)param_1, 2, 0); return uVar3; }
          break;
        case 1: uVar7 = 0xfffffffb; break;
        case 5: uVar7 = 0xffffff7a; break;
        default:
          printk(0x99cbd,0xf08b1,0xf0824,0x1c8);
          assert_post_action(0xf0824,0x1c8);
          return 0;
      }
      iVar4 = 0;
      goto LAB_b9a6;
    }
    *(short*)((int)param_1+0x1e) = *(short*)((int)param_1+0x1e) + 1;
  }
LAB_b9a6:;
  int iVar5 = z_spin_unlock_valid((int)puVar8);
  if (iVar5 != 0) {
    if (iVar4 != 0) notify_one((int)param_1, (int)param_2, uVar3, 0);
    return uVar7;
  }
  printk(0x99cbd,0xf08f4,0xf08c7,0xf0);
  printk(0xf090b,(int)puVar8);
  assert_post_action(0xf08c7,0xf0);
  return 0;
}

