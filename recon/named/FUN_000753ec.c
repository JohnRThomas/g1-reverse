/* readable reconstruction; identity: FUN_000753ec @ 0x000753ec
 * public-name: FUN_000753ec
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   rodata_99cbd                             @ 0x00099cbd
 *   rodata_f08c7                             @ 0x000f08c7
 *   rodata_f08f4                             @ 0x000f08f4
 *   rodata_f090b                             @ 0x000f090b
 *   rodata_f0920                             @ 0x000f0920
 *   rodata_f0935                             @ 0x000f0935
 *   rodata_f7a30                             @ 0x000f7a30
 *   rodata_f871d                             @ 0x000f871d
 *   rodata_f875b                             @ 0x000f875b
 *   rodata_f8775                             @ 0x000f8775
 *   rodata_f878a                             @ 0x000f878a
 *   rodata_f87a6                             @ 0x000f87a6
 *   rodata_f87b7                             @ 0x000f87b7
 *   rodata_f87d4                             @ 0x000f87d4
 *   rodata_f87eb                             @ 0x000f87eb
 *   rodata_f8806                             @ 0x000f8806
 *   rodata_f881f                             @ 0x000f881f
 *   poll_spinlock                            @ 0x2000b4a0
 */
/* Reconstructed FUN_000753ec @ 0x753ec  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline unsigned read_basepri(void){return __get_BASEPRI();}
static inline void write_basepri(unsigned v){__set_BASEPRI(v);}
static inline void write_basepri_max(unsigned v){__set_BASEPRI_MAX(v);}
static inline void isb_sy(void){__ISB();}

extern int z_spin_lock_valid(unsigned,...);
extern int z_spin_unlock_valid(unsigned,...);
extern int z_spin_lock_set_owner(unsigned,...);
extern int assert_post_action(int,...);
extern int printk(int,...);

void FUN_000753ec(int param_1, int param_2, unsigned param_3)
{
  unsigned uVar4 = 0x2000b4a0UL;
  int iVar3 = param_2 * 0x14 + param_1;
  int iVar7;
  int *piVar6;
  int uVar5 = 0;

  for (;;) {
    if (param_2 == 0) return;

    *(volatile int*)(iVar3 - 0xc) = 0;
    unsigned char sw = (*(volatile unsigned char*)(iVar3 - 7)) & 0x3f;

    switch (sw) {
      case 0:
        goto switchD;
      case 1:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          printk(0x99cbd, 0xf87b7, 0xf871d, 0xbe);
          printk(0xf87d4);
          uVar5 = 0xbe;
          goto LAB;
        }
        break;
      case 2:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          printk(0x99cbd, 0xf875b, 0xf871d, 0xb6);
          printk(0xf8775);
          uVar5 = 0xb6;
          goto LAB;
        }
        break;
      case 4:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          printk(0x99cbd, 0xf878a, 0xf871d, 0xba);
          printk(0xf87a6);
          uVar5 = 0xba;
          goto LAB;
        }
        break;
      case 8:
        if (*(volatile int*)(iVar3 - 4) == 0) {
          printk(0x99cbd, 0xf87eb, 0xf871d, 0xc2);
          printk(0xf8806);
          uVar5 = 0xc2;
          goto LAB;
        }
        break;
      default:
        printk(0x99cbd, 0xf7a30, 0xf871d, 0xcf);
        printk(0xf881f);
        uVar5 = 0xcf;
        goto LAB;
    }

    iVar7 = *(volatile int*)(iVar3 - 0x14);
    if (iVar7 != 0) {
      piVar6 = *(volatile int**)(iVar3 - 0x10);
      *piVar6 = iVar7;
      *(volatile int*)(iVar7 + 4) = (int)(long)piVar6;
      *(volatile int*)(iVar3 - 0x14) = 0;
      *(volatile int*)(iVar3 - 0x10) = 0;
    }

  switchD:
    iVar7 = z_spin_unlock_valid(uVar4);
    if (iVar7 == 0) {
      printk(0x99cbd, 0xf08f4, 0xf08c7, 0xf0);
      printk(0xf090b, 0x2000b4a0UL);
      uVar5 = 0xf0;
      goto LAB;
    }

    write_basepri(param_3);
    isb_sy();

    param_3 = read_basepri();
    write_basepri_max(0x20);
    isb_sy();

    iVar7 = z_spin_lock_valid(uVar4);
    param_2 = param_2 - 1;
    if (iVar7 == 0) {
      printk(0x99cbd, 0xf0920, 0xf08c7, 0x72);
      printk(0xf0935, 0x2000b4a0UL);
      uVar5 = 0x72;
      goto LAB;
    }
    z_spin_lock_set_owner(uVar4);
    iVar3 = iVar3 - 0x14;
  }

LAB:
  assert_post_action(uVar4, uVar5);
}
