#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036198 @ 0x01036198
 * public-name: z_impl_k_msgq_put
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_msgq_put                        <= FUN_01036198 @ 0x01036198
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   z_handle_obj_poll_events                 <= FUN_0103b4f6 @ 0x0103b4f6
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103ea89                           @ 0x0103ea89
 */
/* net-core FUN_01036198 @ 0x1036198  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
static inline int isCurrentModePrivileged(void){return (__get_CONTROL()&1)==0;}
static inline int getBasePriority(void){return (int)__get_BASEPRI();}
static inline void setBasePriority(int p){__set_BASEPRI((unsigned)p);}
static inline void InstructionSynchronizationBarrier(int x){(void)x;__ISB();}
static inline unsigned int getCurrentExceptionNumber(void){return __get_IPSR();}

extern int FUN_0103610c(int);
extern int FUN_01036128(int);
extern void FUN_01036144(int);
extern void FUN_0103705c(int);
extern void FUN_01037130(int, unsigned int);
extern unsigned int FUN_010375b8(int, unsigned int, int, int, unsigned int, unsigned int);
extern int FUN_010379d4(int);
extern void FUN_01039bb0(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int, ...);
extern void z_handle_obj_poll_events(int, int);
extern void FUN_0103b614(unsigned int, unsigned int, unsigned int);

#define DAT_010362c0 ((unsigned long)&rodata_103ea89) /*=0x103ea89*/
#define DAT_010362c4 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define DAT_010362c8 ((unsigned long)&rodata_103d3b6) /*=0x103d3b6*/
#define DAT_010362cc 0x21004b28u

unsigned int z_impl_k_msgq_put(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
  int iVar1;
  unsigned int uVar2;
  unsigned int uVar3;
  unsigned int uVar4;
  unsigned int uVar5;
  int iVar6;
  int iVar7;
  unsigned int uVar8;
  int bVar9;

  uVar4 = 0;
  bVar9 = isCurrentModePrivileged();
  if (bVar9) {
    uVar4 = getCurrentExceptionNumber();
    uVar4 = uVar4 & 0x1f;
  }
  if ((uVar4 == 0) || ((param_3 | param_4) == 0)) {
    iVar7 = param_1 + 8;
    uVar8 = 0;
    bVar9 = isCurrentModePrivileged();
    if (bVar9) {
      uVar8 = getBasePriority();
    }
    bVar9 = isCurrentModePrivileged();
    if (bVar9) {
      uVar4 = getBasePriority();
      if (uVar4 == 0 || 0x40 < uVar4) {
        setBasePriority(0x40);
      }
    }
    InstructionSynchronizationBarrier(0xf);
    iVar6 = param_1;
    uVar3 = param_2;
    uVar4 = param_3;
    iVar1 = FUN_0103610c(iVar7);
    if (iVar1 == 0) {
      assert_print(DAT_010362c4, DAT_010362c8, 0x72);
      uVar3 = 0x72;
      uVar8 = DAT_010362c8;
    } else {
      FUN_01036144(iVar7);
      if (*(volatile unsigned int *)(param_1 + 0x24) < *(volatile unsigned int *)(param_1 + 0x10)) {
        iVar1 = FUN_010379d4(param_1);
        if (iVar1 != 0) {
          FUN_0103b614(*(volatile unsigned int *)(iVar1 + 0x14), param_2, *(volatile unsigned int *)(param_1 + 0xc));
          *(volatile unsigned int *)(iVar1 + 0x90) = 0;
          FUN_0103705c(iVar1);
          FUN_01037130(iVar7, uVar8);
          return 0;
        }
        uVar2 = *(volatile unsigned int *)(param_1 + 0x20);
        uVar5 = *(volatile unsigned int *)(param_1 + 0x14);
        if ((uVar2 < uVar5) || (uVar5 = *(volatile unsigned int *)(param_1 + 0x18), uVar5 <= uVar2)) {
          assert_print(DAT_010362c4, DAT_010362c0, 0x90, uVar5, iVar6, uVar3, uVar4);
          uVar3 = 0x90;
          uVar8 = DAT_010362c0;
          goto LAB_010361ea;
        }
        FUN_0103b614(uVar2, param_2, *(volatile unsigned int *)(param_1 + 0xc));
        iVar6 = *(volatile int *)(param_1 + 0x20) + *(volatile int *)(param_1 + 0xc);
        *(volatile int *)(param_1 + 0x20) = iVar6;
        bVar9 = iVar6 == *(volatile int *)(param_1 + 0x18);
        if (bVar9) {
          iVar6 = *(volatile int *)(param_1 + 0x14);
        }
        if (bVar9) {
          *(volatile int *)(param_1 + 0x20) = iVar6;
        }
        *(volatile int *)(param_1 + 0x24) = *(volatile int *)(param_1 + 0x24) + 1;
        z_handle_obj_poll_events(param_1 + 0x28, 0x10);
        uVar3 = 0;
      } else {
        if (param_3 != 0 || param_4 != 0) {
          iVar6 = *(volatile int *)(DAT_010362cc + 8);
          *(volatile unsigned int *)(iVar6 + 0x14) = param_2;
          uVar8 = FUN_010375b8(iVar7, uVar8, param_1, iVar6, param_3, param_4);
          return uVar8;
        }
        uVar3 = 0xffffffdd;
      }
      iVar7 = FUN_01036128(iVar7);
      if (iVar7 != 0) {
        bVar9 = isCurrentModePrivileged();
        if (bVar9) {
          setBasePriority((int)uVar8);
        }
        InstructionSynchronizationBarrier(0xf);
        return uVar3;
      }
      assert_print(DAT_010362c4, DAT_010362c8, 0xf0);
      uVar3 = 0xf0;
      uVar8 = DAT_010362c8;
    }
  } else {
    assert_print(DAT_010362c4, DAT_010362c0, 0x76, param_3 | param_4, param_1, param_2, param_3);
    uVar3 = 0x76;
    uVar8 = DAT_010362c0;
  }
LAB_010361ea:
  FUN_01039bb0(uVar8, uVar3);
  __builtin_unreachable();
}
