/* Reconstructed FUN_00057a04 @ 0x57a04  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005774c(int,int);
extern int FUN_0005f24c(int);
extern short FUN_0005f450(int,int,int);
extern int FUN_0007e2ec(int,int);
extern void FUN_0007e2fa(unsigned long, ...);
extern long long FUN_00081616(int);
extern int FUN_000816a2(int);
extern int FUN_00081746(int,int,void*);
extern int FUN_00081b30(int);

void FUN_00057a04(int param_1, int param_2)
{
    unsigned char bVar1;
    unsigned short uVar2;
    short sVar3;
    unsigned int uVar4;
    int iVar5;
    int extraout_r1;
    unsigned short uVar6;
    unsigned int uVar7;
    unsigned int local_48;
    int local_44, local_40, local_3c;
    int local_28;
    long long _r;

    _r = FUN_00081616(*(int *)(param_1 + 0x80));
    uVar2 = (unsigned short)_r;
    extraout_r1 = (int)((unsigned long long)_r >> 32);
    uVar6 = uVar2;
    if (uVar2 != 0) {
        uVar6 = *(unsigned short *)(extraout_r1 + 0x18);
    }
    if ((unsigned int)*(unsigned short *)(param_2 + 0x10) + (unsigned int)uVar2 <= (unsigned int)*(unsigned short *)(param_1 + 0x84)) {
        *(unsigned short *)(extraout_r1 + 0x18) = uVar6 + 1;
        local_40 = 0x00081699;
        local_48 = 0;
        local_44 = 0;
        local_3c = param_1;
        (void)local_40; (void)local_44; (void)local_3c;
        sVar3 = FUN_0005f450(*(int *)(param_1 + 0x80), *(unsigned short *)(param_2 + 0x10), *(int *)(param_2 + 0xc));
        if (*(short *)(param_2 + 0x10) == sVar3) {
            uVar7 = *(unsigned int *)(param_1 + 0x80);
            uVar4 = (unsigned int)FUN_00081616(uVar7);
            if (*(unsigned short *)(param_1 + 0x84) <= uVar4) {
                bVar1 = *(unsigned char *)(param_1 + 0xb4);
                *(unsigned int *)(param_1 + 0x80) = 0;
                *(unsigned short *)(param_1 + 0x84) = 0;
                if (bVar1 == 3) {
                    iVar5 = FUN_000816a2(param_1 + 0x1c);
                    if (iVar5 == 0) {
                        iVar5 = (**(int (**)(int,int))(*(int *)(param_1 + 4) + 0x14))(param_1, uVar7);
                        if (iVar5 < 0) {
                            if (iVar5 == -0x77) {
                                return;
                            }
                            local_44 = 0x000f4079;
                            local_48 = (unsigned int)bVar1;
                            local_40 = iVar5;
                            FUN_00081746(0x00088160, 0x1840, &local_48);
                            FUN_00081b30(param_1);
                        } else if (*(char *)(param_1 + 0xb4) == '\x03') {
                            FUN_0005774c(param_1, 1);
                        }
                        FUN_0005f24c(uVar7);
                        return;
                    }
                    FUN_0007e2fa(0, 0, 0, 0x99c);
                    uVar7 = 0x99c;
                } else {
                    FUN_0007e2fa(0, 0, 0, 0x99b);
                    uVar7 = 0x99b;
                }
                FUN_0007e2ec(0, uVar7);
            }
            iVar5 = FUN_000816a2(param_1 + 0x1c);
            if (iVar5 != 0) {
                return;
            }
            FUN_0005774c(param_1, 1);
            return;
        }
    }
    local_28 = 2;
    FUN_00081746(0x00088160, 0x1040, &local_28);
    FUN_00081b30(param_1);
    return;
}

