#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01035d18 @ 0x01035d18
 * public-name: FUN_01035d18
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   sys_timepoint_calc                       <= FUN_0103b304 @ 0x0103b304
 *   sys_timepoint_timeout                    <= FUN_0103b34c @ 0x0103b34c
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103e9fe                           @ 0x0103e9fe
 */
/* net-core FUN_01035d18 @ 0x1035d18  (parity 300 trials PROVEN) */
#include <stdint.h>
#include <cmsis_gcc.h>
#include "../../headers/g1_cmsis_shim.h"

extern unsigned long long FUN_0102c4e4(int, unsigned int, unsigned int);
extern int FUN_0103610c(int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void FUN_010375b8(int, unsigned int, int, int, int, int);
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int);
extern void sys_timepoint_calc(int*);
extern void sys_timepoint_timeout(int*, int, int, int);

#define DAT_01035e10 ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define DAT_01035e14 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define DAT_01035e18 ((unsigned long)&rodata_103e9fe) /*=0x103e9fe*/

int FUN_01035d18(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4,
                  int param_5, int param_6)
{
  int bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  unsigned int uVar5;
  unsigned int uVar6;
  unsigned int uVar7;
  int iVar8;
  unsigned long long uVar9;
  int local_30;
  int iStack_2c;

  iVar8 = param_1 + 0x14;
  sys_timepoint_calc(&local_30);
  iVar2 = iStack_2c;
  iVar4 = local_30;
  uVar7 = 0;
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar7 = getBasePriority();
  }
  bVar1 = isCurrentModePrivileged();
  if (bVar1) {
    uVar6 = getBasePriority();
    if (uVar6 == 0 || 0x40 < uVar6) {
      setBasePriority(0x40);
    }
  }
  InstructionSynchronizationBarrier(0xf);
  iVar3 = FUN_0103610c(iVar8);
  uVar9 = 0;
  if (iVar3 == 0) {
LAB_01035d56:
    assert_print(DAT_01035e14, DAT_01035e10, 0x72);
    uVar5 = 0x72;
    uVar7 = DAT_01035e10;
  } else {
    FUN_01036144(iVar8);
    uVar6 = 0;
    bVar1 = isCurrentModePrivileged();
    if (bVar1) {
      uVar6 = getCurrentExceptionNumber();
      uVar6 = uVar6 & 0x1f;
    }
    if ((uVar6 == 0) || (param_5 == 0 && param_6 == 0)) {
      while (1) {
        uVar9 = FUN_0102c4e4(param_1, param_2, param_3);
        if (((int)uVar9 != 0) || (param_5 == 0 && param_6 == 0)) break;
        sys_timepoint_timeout(&local_30, (int)(uVar9 >> 0x20), iVar4, iVar2);
        param_6 = iStack_2c;
        param_5 = local_30;
        FUN_010375b8(iVar8, uVar7, param_1 + 0xc, iStack_2c, local_30, iStack_2c);
        uVar7 = 0;
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          uVar7 = getBasePriority();
        }
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          uVar6 = getBasePriority();
          if (uVar6 == 0 || 0x40 < uVar6) {
            setBasePriority(0x40);
          }
        }
        InstructionSynchronizationBarrier(0xf);
        iVar3 = FUN_0103610c(iVar8);
        if (iVar3 == 0) goto LAB_01035d56;
        FUN_01036144(iVar8);
      }
      iVar4 = FUN_01036128(iVar8);
      if (iVar4 != 0) {
        bVar1 = isCurrentModePrivileged();
        if (bVar1) {
          setBasePriority((int)uVar7);
        }
        InstructionSynchronizationBarrier(0xf);
        return (int)uVar9;
      }
      assert_print(DAT_01035e14, DAT_01035e10, 0xf0);
      uVar5 = 0xf0;
      uVar7 = DAT_01035e10;
    } else {
      assert_print(DAT_01035e14, DAT_01035e18, 0x4a);
      uVar5 = 0x4a;
      uVar7 = DAT_01035e18;
    }
  }
  assert_post_action(uVar7, uVar5);
  __builtin_unreachable();
}
