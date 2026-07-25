/* readable reconstruction; identity: FUN_01036198 @ 0x01036198
 * public-name: z_impl_k_msgq_put
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   z_impl_k_msgq_put                        <= FUN_01036198 @ 0x01036198
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   z_handle_obj_poll_events                 <= FUN_0103b4f6 @ 0x0103b4f6
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103ea89                           @ 0x0103ea89
 */
/* net-core FUN_01036198 @ 0x1036198  (parity 300 trials PROVEN) */
#ifdef G1_COHESIVE_BUILD
/* P4 iteration 20 - the shipped CPUNET `_kernel` is at 0x21004b28.
 * In the relocated cohesive link that address is inside `sdc_mempool`
 * (0x21002bb8..0x21007e79), so every recovered kernel body that reaches the
 * scheduler through this base read/wrote a SHADOW copy of `_kernel` carved out
 * of the SoftDevice Controller's heap while the linked Zephyr scheduler
 * (z_arm_pendsv, arch_swap, z_ready_thread) used the real one at
 * &_kernel.  Iteration 7 converted only the four spinlock validators and
 * recorded the rest as open; this pass closes the whole window structurally.
 * Field offsets are identical in both images: +0x08 = cpus[0].current and
 * +0x10 = cpus[0].id were verified against the shipped disassembly in
 * iteration 7, which fixes struct _cpu at 0x14 bytes and therefore
 * ready_q.cache at +0x14 and ready_q.runq at +0x18; `nm -S` reports
 * sizeof(_kernel) = 0x20 in this link.
 * Parity builds keep the original literal, so no proven body changes. */
/* Reached through an asm label so no reconstruction TU has to pull in the
 * Zephyr kernel headers (several of them declare assert_print /
 * assert_post_action with the recovered prototypes). */
extern char g1_net_kernel_object[] __asm__("_kernel");
#define G1_NET_KERNEL_BASE ((unsigned long)g1_net_kernel_object)
#else
#define G1_NET_KERNEL_BASE 0x21004b28ul
#endif
#define G1_NET_K(off) (G1_NET_KERNEL_BASE + (off))

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
extern void assert_post_action(unsigned int, unsigned int);
extern void assert_print(unsigned int, unsigned int, unsigned int, ...);
extern void z_handle_obj_poll_events(int, int);
extern void FUN_0103b614(unsigned int, unsigned int, unsigned int);

#define DAT_010362c0 0x0103ea89u
#define DAT_010362c4 0x0103d2a7u
#define DAT_010362c8 0x0103d3b6u
#define DAT_010362cc G1_NET_K(0x00)

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
  assert_post_action(uVar8, uVar3);
  __builtin_unreachable();
}
