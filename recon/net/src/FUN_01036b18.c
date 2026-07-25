/* net-core FUN_01036b18 @ 0x1036b18  (parity 300 trials PROVEN) */
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

extern void FUN_01039bb0(unsigned int a, unsigned int b);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_0103b14a(void);
extern void FUN_0103b25a(int a);

#define DAT_be0 0x0103eaedu
#define DAT_be4 0x0103d2a7u
#define DAT_be8 G1_NET_K(0x00)

unsigned int FUN_01036b18(unsigned int *param_1, int *param_2, unsigned int param_3, unsigned int param_4)
{
    int iVar1;
    int iVar2 = (int)param_1[3];
    int iVar3;
    unsigned int uVar4;

    if ((iVar2 << 0x1e) < 0) {
        uVar4 = 0xfffffff0;
        goto LAB_b76;
    }
    if ((iVar2 << 0x1d) < 0) {
        goto LAB_b76;
    }
    if (*param_2 == 0) {
        *param_2 = (int)param_1[2];
    }
    if ((int)(param_1[3] << 0x1f) < 0) {
        if (param_1[2] == 0) {
            FUN_01039bbe(DAT_be4, DAT_be0, 0x14e, 0, param_4);
            FUN_01039bb0(DAT_be0, 0x14e);
            /* real hardware: falls through with r3 still == param_1[2] (==0 here) */
        }
        uVar4 = 2;
        *param_2 = (int)param_1[2];
    } else {
        uVar4 = 1;
    }

    iVar2 = *param_2;
    if (iVar2 == 0) {
        uVar4 = 0xffffffea;
        goto LAB_b76;
    }

    if (*(volatile int *)(DAT_be8 + 8) == iVar2) {
        iVar1 = FUN_0103b14a();
        iVar3 = *(volatile int *)(iVar2 + 0xb0);
        if (iVar1 != 0) {
            goto LAB_b6a;
        }
        if ((iVar3 << 0x1f) < 0) {
            if ((iVar3 << 0x1c) >= 0 || (iVar3 << 0x1d) < 0) {
                goto LAB_bac;
            }
            uVar4 = 0xfffffff0;
            goto LAB_b76;
        }
    } else {
        iVar3 = *(volatile int *)(iVar2 + 0xb0);
    LAB_b6a:
        if ((iVar3 << 0x1f) < 0) {
            if ((iVar3 << 0x1d) >= 0 && (iVar3 << 0x1c) >= 0) {
            LAB_bac:
                *param_1 = 0;
                if (*(volatile unsigned int **)(iVar2 + 0x9c) == 0) {
                    *(volatile unsigned int **)(iVar2 + 0x98) = param_1;
                    *(volatile unsigned int **)(iVar2 + 0x9c) = param_1;
                } else {
                    **(volatile unsigned int **)(iVar2 + 0x9c) = (unsigned int)(uintptr_t)param_1;
                    *(volatile unsigned int **)(iVar2 + 0x9c) = param_1;
                }
                FUN_0103b25a(iVar2);
                param_1[3] = param_1[3] | 4;
                param_1[2] = (unsigned int)*param_2;
                return uVar4;
            }
            uVar4 = 0xfffffff0;
            goto LAB_b76;
        }
    }
    uVar4 = 0xffffffed;

LAB_b76:
    *param_2 = 0;
    return uVar4;
}

