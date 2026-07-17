/* readable reconstruction; identity: FUN_000751d0 @ 0x000751d0
 * public-name: FUN_000751d0
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   z_spin_lock_valid                        <= FUN_00072040 @ 0x00072040
 *   z_spin_unlock_valid                      <= FUN_0007205c @ 0x0007205c
 *   z_spin_lock_set_owner                    <= FUN_00072078 @ 0x00072078
 *   assert_post_action                       <= FUN_0007e2ec @ 0x0007e2ec
 *   printk                                   <= FUN_0007e2fa @ 0x0007e2fa
 * address symbols (name @ address):
 *   poll_spinlock                            @ 0x2000b4a0
 */
/* Reconstructed FUN_000751d0 @ 0x751d0  (parity: 147/300 trials, PROVEN) */
#include <stdint.h>
#include "/Users/freedomcoder/ncs251/modules/hal/cmsis/CMSIS/Core/Include/cmsis_gcc.h"
extern int z_spin_lock_valid(int,...);
extern int z_spin_unlock_valid(int,...);
extern int z_spin_lock_set_owner(int,...);
extern int assert_post_action(int,...);
extern int printk(int,...);
extern int FUN_00086778(int,...);

int FUN_000751d0(int param_1, int param_2, char *param_3, int param_4)
{
    int iVar5 = 0, iVar6 = 0, iVar2;
    unsigned uVar4 = 0, uVar7;

    do {
        if (param_2 <= iVar5) return iVar6;
        uVar7 = __get_BASEPRI();
        __set_BASEPRI_MAX(0x20);
        __ISB();

        iVar2 = z_spin_lock_valid(0x2000b4a0);
        if (iVar2 == 0) {
            printk(0); printk(0); uVar7 = 0x72; goto LAB_752e6;
        }
        z_spin_lock_set_owner(0x2000b4a0);
        switch (*(unsigned char *)(param_1 + 0xd) & 0x3f) {
        case 0:
            break;
        case 1:
            if (*(int *)(*(int *)(param_1 + 0x10) + 8) == 0) break;
            uVar4 = 1; goto LAB_7524a;
        case 2:
            if (*(int *)(*(int *)(param_1 + 0x10) + 8) != 0) { uVar4 = 2; goto LAB_7524a; }
            break;
        default:
            printk(0); printk(0); uVar7 = 99; goto LAB_752e6;
        case 4:
            if (**(int **)(param_1 + 0x10) != 0) { uVar4 = 4; goto LAB_7524a; }
            break;
        case 8:
            if (*(int *)(*(int *)(param_1 + 0x10) + 0x24) != 0) { uVar4 = 0x10; goto LAB_7524a; }
            break;
        }

        if ((param_4 == 0) && (*param_3 != '\0')) {
            switch (*(unsigned char *)(param_1 + 0xd) & 0x3f) {
            case 0:
                goto caseD_0;
            case 1:
                if (*(int *)(param_1 + 0x10) == 0) { printk(0); printk(0); uVar7 = 0x95; goto LAB_752e6; }
                break;
            case 2:
                if (*(int *)(param_1 + 0x10) == 0) { printk(0); printk(0); uVar7 = 0x8d; goto LAB_752e6; }
                break;
            default:
                printk(0); printk(0); uVar7 = 0xa6; goto LAB_752e6;
            case 4:
                if (*(int *)(param_1 + 0x10) == 0) { printk(0); printk(0); uVar7 = 0x91; goto LAB_752e6; }
                break;
            case 8:
                if (*(int *)(param_1 + 0x10) == 0) { printk(0); printk(0); uVar7 = 0x99; goto LAB_752e6; }
                break;
            }
            switch (*(unsigned char *)(param_1 + 0xd) & 0x3f) {
            case 1: iVar2 = *(int *)(param_1 + 0x10); break;
            case 2: iVar2 = *(int *)(param_1 + 0x10) + 0x10; break;
            case 4: iVar2 = *(int *)(param_1 + 0x10) + 0x14; break;
            case 8: iVar2 = *(int *)(param_1 + 0x10) + 0x28; break;
            default: iVar2 = 0; break;
            }
            FUN_00086778(iVar2,param_1,param_3);
caseD_0:
            *(char **)(param_1 + 8) = param_3;
            iVar6 = iVar6 + 1;
        }
        goto LAB_75260;

LAB_7524a:
        {
            unsigned A = *(unsigned *)(param_1 + 0xc);
            *(unsigned *)(param_1 + 8) = 0;
            *(unsigned *)(param_1 + 0xc) = (A & 0xffe03fffU) | ((uVar4 | ((A << 0xb) >> 0x19)) << 0xe);
            *param_3 = '\0';
        }

LAB_75260:
        iVar2 = z_spin_unlock_valid(0x2000b4a0);
        param_1 = param_1 + 0x14;
        if (iVar2 == 0) {
            printk(0); printk(0); uVar7 = 0xf0;
LAB_752e6:
            assert_post_action(0);
            uVar4 = 4;
            goto LAB_7524a;
        }
        __set_BASEPRI(uVar7);
        __ISB();
        iVar5 = iVar5 + 1;
    } while (1);
}
