/* Reconstructed FUN_000751d0 @ 0x751d0  (parity: 147/300 trials, PROVEN) */
extern int FUN_00072040(int,...);
extern int FUN_0007205c(int,...);
extern int FUN_00072078(int,...);
extern int FUN_0007e2ec(int,...);
extern int FUN_0007e2fa(int,...);
extern int FUN_00086778(int,...);
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

        iVar2 = FUN_00072040(0);
        if (iVar2 == 0) {
            FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 0x72; goto LAB_752e6;
        }
        FUN_00072078(0);
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
            FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 99; goto LAB_752e6;
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
                if (*(int *)(param_1 + 0x10) == 0) { FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 0x95; goto LAB_752e6; }
                break;
            case 2:
                if (*(int *)(param_1 + 0x10) == 0) { FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 0x8d; goto LAB_752e6; }
                break;
            default:
                FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 0xa6; goto LAB_752e6;
            case 4:
                if (*(int *)(param_1 + 0x10) == 0) { FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 0x91; goto LAB_752e6; }
                break;
            case 8:
                if (*(int *)(param_1 + 0x10) == 0) { FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 0x99; goto LAB_752e6; }
                break;
            }
            FUN_00086778(0);
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
        iVar2 = FUN_0007205c(0);
        param_1 = param_1 + 0x14;
        if (iVar2 == 0) {
            FUN_0007e2fa(0); FUN_0007e2fa(0); uVar7 = 0xf0;
LAB_752e6:
            FUN_0007e2ec(0);
            uVar4 = 4;
            goto LAB_7524a;
        }
        if (isCurrentModePrivileged(0)) setBasePriority(uVar7);
        InstructionSynchronizationBarrier(0xf);
        iVar5 = iVar5 + 1;
    } while (1);
}

