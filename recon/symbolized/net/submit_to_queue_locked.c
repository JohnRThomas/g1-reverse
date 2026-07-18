#include "g1_net_symbols.h"
/* readable reconstruction; identity: FUN_01036b18 @ 0x01036b18
 * public-name: submit_to_queue_locked
 * durable-map: recon/catalogs/function_names_net.json
 * callees (readable <= raw @ address):
 *   submit_to_queue_locked                   <= FUN_01036b18 @ 0x01036b18
 *   assert_print                             <= FUN_01039bbe @ 0x01039bbe
 *   notify_queue_locked_isra_0               <= FUN_0103b25a @ 0x0103b25a
 * address symbols (name @ address):
 *   rodata_103d2a7                           @ 0x0103d2a7
 *   rodata_103eaed                           @ 0x0103eaed
 */
/* net-core FUN_01036b18 @ 0x1036b18  (parity 300 trials PROVEN) */
#include <stdint.h>

extern void FUN_01039bb0(unsigned int a, unsigned int b);
extern void assert_print(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);
extern int FUN_0103b14a(void);
extern void notify_queue_locked_isra_0(int a);

#define DAT_be0 ((unsigned long)&rodata_103eaed) /*=0x103eaed*/
#define DAT_be4 ((unsigned long)&rodata_103d2a7) /*=0x103d2a7*/
#define DAT_be8 0x21004b28u

unsigned int submit_to_queue_locked(unsigned int *param_1, int *param_2, unsigned int param_3, unsigned int param_4)
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
            assert_print(DAT_be4, DAT_be0, 0x14e, 0, param_4);
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
                notify_queue_locked_isra_0(iVar2);
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
