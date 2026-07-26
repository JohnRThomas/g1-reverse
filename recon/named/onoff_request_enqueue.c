/* readable reconstruction; identity: FUN_0004b908 @ 0x0004b908
 * public-name: onoff_request_enqueue
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   onoff_process_event                      <= FUN_0004b4fc @ 0x0004b4fc
 *   onoff_request_enqueue                    <= FUN_0004b908 @ 0x0004b908
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   validate_args                            <= FUN_0007e1c6 @ 0x0007e1c6
 *   notify_one                               <= FUN_0007e1e6 @ 0x0007e1e6
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd   [INLINED -- G6 literal batch]
 *   rodata_f0824                             @ 0x000f0824
 *   rodata_f08b1                             @ 0x000f08b1   [INLINED -- G6 literal batch]
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4   [INLINED -- G6 literal batch]
 *   rodata_f090b                             @ 0x000f090b   [INLINED -- G6 literal batch]
 *   rodata_f0920                             @ 0x000f0920   [INLINED -- G6 literal batch]
 *   rodata_f0935                             @ 0x000f0935   [INLINED -- G6 literal batch]
 */
/* Reconstructed FUN_0004b908 @ 0x4b908  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
extern int onoff_process_event(int,int,unsigned int);
extern int z_spin_lock_valid(int);
extern int z_spin_unlock_valid(int);
extern int z_spin_lock_set_owner(int);
extern int validate_args(int,int);
extern int notify_one(int,int,unsigned int,int);
extern int assert_post_action(int,...);
extern int printk(int,...);
unsigned int onoff_request_enqueue(int *param_1, int *param_2)
{
  unsigned int uVar3 = (unsigned int)validate_args((int)param_1,(int)param_2);
  if ((int)uVar3 < 0) return uVar3;
  unsigned int saved_basepri = __get_BASEPRI();
  __set_BASEPRI_MAX(0x20);
  __ISB();
  int *puVar8 = param_1 + 5;
  int iVar4 = z_spin_lock_valid((int)puVar8);
  if (iVar4 == 0) {
    printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_lock_valid(l)"),0xf08c7,0x72);
    printk(((unsigned long)"\tInvalid spinlock %p\n"),(int)puVar8);
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
          if ((uVar1 & 7) == 0) { onoff_process_event((int)param_1, 2, saved_basepri); return uVar3; }
          break;
        case 1: uVar7 = 0xfffffffb; break;
        case 5: uVar7 = 0xffffff7a; break;
        default:
          printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"state == (1UL << (0))"),0xf0824,0x1c8);
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
    __set_BASEPRI(saved_basepri);
    __ISB();
    if (iVar4 != 0) notify_one((int)param_1, (int)param_2, uVar3, 0);
    return uVar7;
  }
  printk(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"),((unsigned long)"z_spin_unlock_valid(l)"),0xf08c7,0xf0);
  printk(((unsigned long)"\tNot my spinlock %p\n"),(int)puVar8);
  assert_post_action(0xf08c7,0xf0);
  return 0;
}
