/* net-core FUN_01037a60 @ 0x1037a60  (parity 300 trials PROVEN) */
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
#include <cmsis_gcc.h>

extern void FUN_0102ec10(unsigned int a);
extern int FUN_0103610c(unsigned int a);
extern int FUN_01036128(unsigned int a);
extern void FUN_01036144(unsigned int a);
extern void FUN_01036f74(int a);
extern void FUN_0103735c(void *list_head, void *node);
extern void FUN_01039bb0(unsigned int a, unsigned int b);
extern void FUN_01039bbe(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

#define DAT_37b44 0x0103eb0eu
#define DAT_37b48 0x0103d2a7u
#define DAT_37b4c 0x21004b68u
#define DAT_37b50 0x0103d3b6u
#define DAT_37b54 G1_NET_K(0x00)
#define DAT_37b58 0x210043a8u

void FUN_01037a60(void)
{
    unsigned int uVar10;
    int iVar2, iVar3;
    int *piVar8;
    int *puVar9, *puVar6, *puVar5;

    unsigned int exception = __get_IPSR() & 0x1fU;
    if (exception != 0) {
        FUN_01039bbe(DAT_37b48, DAT_37b44, 0x57a, exception, 0);
        FUN_01039bb0(DAT_37b44, 0x57a);
    }

    uVar10 = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40);
    __ISB();

    iVar2 = FUN_0103610c(DAT_37b4c);
    if (iVar2 == 0) {
        FUN_01039bbe(DAT_37b48, DAT_37b50, 0x72, 0, 0);
        FUN_01039bb0(DAT_37b50, 0x72);
    }

SHARED:
    iVar3 = DAT_37b54;
    FUN_01036144(DAT_37b4c);
    puVar9 = (int *)(iVar3 + 0x18);
    *(volatile unsigned char *)(*(volatile int *)(iVar3 + 8) + 0xd) =
        *(volatile unsigned char *)(*(volatile int *)(iVar3 + 8) + 0xd) & 0x7f;
    FUN_0103735c(puVar9, *(volatile void **)(iVar3 + 8));
    piVar8 = *(volatile int **)(iVar3 + 8);
    *(volatile unsigned char *)((int)piVar8 + 0xd) =
        *(volatile unsigned char *)((int)piVar8 + 0xd) | 0x80;
    if (piVar8 == (int *)DAT_37b58) {
        FUN_01039bbe(DAT_37b48, DAT_37b44, 0xc1, (unsigned int)(intptr_t)piVar8, 0);
        FUN_01039bb0(DAT_37b44, 0xc1);
        goto SHARED;
    }

    puVar6 = *(volatile int **)(iVar3 + 0x18);
    puVar5 = *(volatile int **)(iVar3 + 0x1c);
    if (puVar6 == puVar9) {
        puVar6 = 0;
    }
    for (; puVar6 != 0; puVar6 = (int *)*puVar6) {
        if (*(volatile signed char *)((int)piVar8 + 0xe) != *(volatile signed char *)((int)puVar6 + 0xe) &&
            *(volatile signed char *)((int)piVar8 + 0xe) < *(volatile signed char *)((int)puVar6 + 0xe)) {
            int *puVar9b = (int *)puVar6[1];
            *piVar8 = (int)(intptr_t)puVar6;
            piVar8[1] = (int)(intptr_t)puVar9b;
            *puVar9b = (int)(intptr_t)piVar8;
            puVar6[1] = (int)(intptr_t)piVar8;
            goto LAB_b10;
        }
        if (puVar6 == puVar5) {
            break;
        }
    }
    *piVar8 = (int)(intptr_t)puVar9;
    piVar8[1] = (int)(intptr_t)puVar5;
    *puVar5 = (int)(intptr_t)piVar8;
    *(volatile int **)(iVar3 + 0x1c) = piVar8;
LAB_b10:
    FUN_01036f74(1);
    iVar3 = FUN_01036128(DAT_37b4c);
    if (iVar3 != 0) {
        FUN_0102ec10(uVar10);
        return;
    }
    FUN_01039bbe(DAT_37b48, DAT_37b50, 0x111, 0, 0);
    FUN_01039bb0(DAT_37b50, 0x111);
    goto SHARED;
}

