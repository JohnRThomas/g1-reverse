#include "g1_app_symbols.h"
/* named: FUN_000751d0 */
/* Reconstructed FUN_000751d0 @ 0x751d0  (parity: 147/300 trials, PROVEN) */
extern int z_spin_lock_valid(int,...);
extern int z_spin_unlock_valid(int,...);
extern int z_spin_lock_set_owner(int,...);
extern int assert_post_action(int,...);
extern int printk(int,...);
extern int add_event(int,...);
extern int isCurrentModePrivileged(int,...);
extern unsigned getBasePriority(int,...);
extern int setBasePriority(int,...);
extern int InstructionSynchronizationBarrier(int,...);

int FUN_000751d0(int param_1, int param_2, char *param_3, int param_4)
{
    int iVar5 = 0, iVar6 = 0, iVar2;
    unsigned uVar4 = 0, uVar7;

    do {
        if (param_2 <= iVar5) return iVar6;
        uVar7 = 0;
        if (isCurrentModePrivileged(0)) uVar7 = getBasePriority(0);
        {
            unsigned t;
            if (isCurrentModePrivileged(0) && (t = getBasePriority(0), t == 0 || 0x20 < t))
                setBasePriority(0x20);
        }
        InstructionSynchronizationBarrier(0xf);

        iVar2 = z_spin_lock_valid(0);
        if (iVar2 == 0) {
            printk(0); printk(0); uVar7 = 0x72; goto LAB_752e6;
        }
        z_spin_lock_set_owner(0);
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
            add_event(0);
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
        iVar2 = z_spin_unlock_valid(0);
        param_1 = param_1 + 0x14;
        if (iVar2 == 0) {
            printk(0); printk(0); uVar7 = 0xf0;
LAB_752e6:
            assert_post_action(0);
            uVar4 = 4;
            goto LAB_7524a;
        }
        if (isCurrentModePrivileged(0)) setBasePriority(uVar7);
        InstructionSynchronizationBarrier(0xf);
        iVar5 = iVar5 + 1;
    } while (1);
}

