/* readable reconstruction; identity: FUN_01037b5c @ 0x01037b5c
 * public-name: FUN_01037b5c
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103bac9                           @ 0x0103bac9
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb0e                           @ 0x0103eb0e
 *   g_zephyr_sched_swap_tmp                  @ 0x21004b5c
 */
/* net-core FUN_01037b5c @ 0x1037b5c  (parity 300 trials PROVEN) */
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
typedef unsigned char u8;
typedef unsigned int u32;
typedef int i32;
typedef long long i64;

extern void FUN_0102ec10(u32);
extern i32  FUN_0103610c(u32);
extern i32  FUN_01036128(u32);
extern void FUN_01036144(u32);
extern void FUN_010374dc(u32);
extern void FUN_01037a60(void);
extern void FUN_01037f8c(i32,u32,u32,u32);
extern u32  assert_post_action(u32,u32);
extern void assert_print(u32,u32,u32);
extern u32  FUN_0103b2f8(u32,u32,u32);

#define DAT_01037c48 0x0103eb0eu
#define DAT_01037c4c 0x0103d2a7u
#define DAT_01037c50 0x21004b68u
#define DAT_01037c54 0x0103d3b6u
#define DAT_01037c58 G1_NET_K(0x00)
#define DAT_01037c5c 0x21004b5cu
#define DAT_01037c60 0x0103bac9u

i32 FUN_01037b5c(u32 param_1, i32 param_2)
{
  u32 r0v, r1v;
  i32 r4;
  u32 r8v;

  {
    u32 ipsr = __get_IPSR();
    if (ipsr != 0) {
      assert_print(DAT_01037c4c, DAT_01037c48, 0x596);
      r1v = 0x596;
      r0v = DAT_01037c48;
      goto FINAL_CALL;
    }
  }
  if ((param_1 | (u32)param_2) == 0) {
    FUN_01037a60();
    return 0;
  }
  {
    i64 combined = (((i64)param_2) << 32 | (u32)param_1) + 2;
    if (combined < 0) {
      r4 = (i32)(0xFFFFFFFEu - param_1);
    } else {
      i32 iVar2 = (i32)FUN_0103b2f8(param_1, (u32)param_2, param_1 + 2);
      r4 = (i32)(param_1 + (u32)iVar2);
    }
  }

COMMON: ;
  {
    u32 oldpri = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40u);
    __ISB();
    r8v = oldpri;
  }
  {
    i32 res = FUN_0103610c(DAT_01037c50);
    if (res == 0) {
      u32 rv;
      assert_print(DAT_01037c4c, DAT_01037c54, 0x72);
      r1v = 0x72;
      r0v = DAT_01037c54;
FINAL_CALL:
      rv = assert_post_action(r0v, r1v);
      r4 = (i32)(0xFFFFFFFEu - rv);
      goto COMMON;
    }
  }
  {
    i32 iVar2addr = DAT_01037c58;
    i32 iVar3;
    FUN_01036144(DAT_01037c50);
    {
      u32 current = *(volatile u32*)((u32)iVar2addr + 8);
      *(volatile u32*)DAT_01037c5c = current;
      /* The callee has no semantic argument, but the firmware enters it with
       * the just-published current pointer still live in r0.  Preserve that
       * call-boundary value for instruction-faithful oracle comparison. */
      FUN_010374dc(current);
    }
    FUN_01037f8c(*(volatile i32*)((u32)iVar2addr + 8) + 0x18, DAT_01037c60, param_1, (u32)param_2);
    {
      u32 uVar5 = DAT_01037c50;
      *(volatile u8*)((u32)(*(volatile i32*)((u32)iVar2addr + 8)) + 0xd) =
        *(volatile u8*)((u32)(*(volatile i32*)((u32)iVar2addr + 8)) + 0xd) | 0x10;
      iVar3 = FUN_01036128(uVar5);
      if (iVar3 == 0) {
        u32 rv;
        assert_print(DAT_01037c4c, DAT_01037c54, 0x111);
        r1v = 0x111;
        r0v = DAT_01037c54;
        rv = assert_post_action(r0v, r1v);
        r4 = (i32)(0xFFFFFFFEu - rv);
        goto COMMON;
      } else {
        FUN_0102ec10(r8v);
        if ((i32)(((u32)(*(volatile u8*)((u32)(*(volatile i32*)((u32)iVar2addr + 8)) + 0xd))) << 0x1b) >= 0) {
          u32 uVar4 = FUN_0103b2f8(0, 0, 0);
          if ((u32)r4 < uVar4) {
            return 0;
          }
          return r4 - (i32)uVar4;
        }
        {
          u32 rv;
          assert_print(DAT_01037c4c, DAT_01037c48, 0x5b2);
          r1v = 0x5b2;
          r0v = DAT_01037c48;
          rv = assert_post_action(r0v, r1v);
          r4 = (i32)(0xFFFFFFFEu - rv);
          goto COMMON;
        }
      }
    }
  }
}
