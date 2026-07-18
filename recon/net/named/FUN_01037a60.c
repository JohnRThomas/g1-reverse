/* readable reconstruction; identity: FUN_01037a60 @ 0x01037a60
 * public-name: FUN_01037a60
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   assert_post_action                       <= FUN_01039bb0 @ 0x01039bb0
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103d3b6                           @ 0x0103d3b6
 *   rodata_103eb0e                           @ 0x0103eb0e
 */
/* net-core FUN_01037a60 @ 0x1037a60  (parity 300 trials PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"

extern void FUN_0102ec10(unsigned int a);
extern int FUN_0103610c(unsigned int a);
extern int FUN_01036128(unsigned int a);
extern void FUN_01036144(unsigned int a);
extern void FUN_01036f74(int a);
extern void FUN_0103735c(void *list_head, void *node);
extern void assert_post_action(unsigned int a, unsigned int b);
extern void assert_print(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

#define DAT_37b44 0x0103eb0eu
#define DAT_37b48 0x0103d2a7u
#define DAT_37b4c 0x21004b68u
#define DAT_37b50 0x0103d3b6u
#define DAT_37b54 0x21004b28u
#define DAT_37b58 0x210043a8u

void FUN_01037a60(void)
{
    unsigned int uVar10;
    int iVar2, iVar3;
    int *piVar8;
    int *puVar9, *puVar6, *puVar5;

    unsigned int exception = __get_IPSR() & 0x1fU;
    if (exception != 0) {
        assert_print(DAT_37b48, DAT_37b44, 0x57a, exception, 0);
        assert_post_action(DAT_37b44, 0x57a);
    }

    uVar10 = __get_BASEPRI();
    __set_BASEPRI_MAX(0x40);
    __ISB();

    iVar2 = FUN_0103610c(DAT_37b4c);
    if (iVar2 == 0) {
        assert_print(DAT_37b48, DAT_37b50, 0x72, 0, 0);
        assert_post_action(DAT_37b50, 0x72);
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
        assert_print(DAT_37b48, DAT_37b44, 0xc1, (unsigned int)(intptr_t)piVar8, 0);
        assert_post_action(DAT_37b44, 0xc1);
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
    assert_print(DAT_37b48, DAT_37b50, 0x111, 0, 0);
    assert_post_action(DAT_37b50, 0x111);
    goto SHARED;
}
