/* net-core FUN_01037398 @ 0x1037398  (parity 300 trials PROVEN) */
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

#define P_01037424 G1_NET_K(0x18)
#define P_01037428 0x210043a8
#define P_0103742c 0x0103eb0e
#define P_01037430 0x0103d2a7
#define P_01037434 G1_NET_K(0x00)

extern void FUN_01036f74(int);
extern void FUN_0103735c(int, int *);
extern void FUN_01039bbe(int, int, unsigned int);
extern void FUN_01039bb0(int, unsigned int);

void FUN_01037398(int *param_1)
{
  int iVar1;
  unsigned int *puVar2;
  unsigned int *puVar3;
  unsigned int *puVar4;

  if (*(signed char *)((int)param_1 + 0xd) < 0) {
    *(unsigned char *)((int)param_1 + 0xd) = *(unsigned char *)((int)param_1 + 0xd) & 0x7f;
    FUN_0103735c(P_01037424, param_1);
  }
  *(unsigned char *)((int)param_1 + 0xd) = *(unsigned char *)((int)param_1 + 0xd) | 0x80;
  iVar1 = P_01037434;
  if (param_1 == (int *)P_01037428) {
    FUN_01039bbe(P_01037430, P_0103742c, 0xc1);
    FUN_01039bb0(P_0103742c, 0xc1);
    return;
  }
  puVar3 = (unsigned int *)(P_01037434 + 0x18);
  puVar4 = (unsigned int *)*puVar3;
  puVar2 = *(unsigned int **)(P_01037434 + 0x1c);
  if (puVar4 == puVar3) {
    puVar4 = (unsigned int *)0;
  }
  for (; puVar4 != (unsigned int *)0; puVar4 = (unsigned int *)*puVar4) {
    if ((*(signed char *)((int)param_1 + 0xe) != *(signed char *)((int)puVar4 + 0xe)) &&
        (*(signed char *)((int)param_1 + 0xe) < *(signed char *)((int)puVar4 + 0xe))) {
      puVar3 = (unsigned int *)puVar4[1];
      *param_1 = (int)puVar4;
      param_1[1] = (int)puVar3;
      *puVar3 = (unsigned int)param_1;
      puVar4[1] = (unsigned int)param_1;
      goto LAB_end;
    }
    if (puVar2 == puVar4) break;
  }
  *param_1 = (int)puVar3;
  param_1[1] = (int)puVar2;
  *puVar2 = (unsigned int)param_1;
  *(int **)(iVar1 + 0x1c) = param_1;
LAB_end:
  FUN_01036f74((*(int **)(iVar1 + 8) == param_1) ? 1 : 0);
  return;
}

