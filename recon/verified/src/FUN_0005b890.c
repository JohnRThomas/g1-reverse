/* Reconstructed FUN_0005b890 @ 0x5b890  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000566a4(int);
extern int FUN_00056e74(int,int);
extern int FUN_00056f08(int,int,int);
extern int FUN_0005a128(int,int,int,int);
extern int FUN_0005b270(int,int,int);
extern int FUN_0005b680(int,int,int);
extern int FUN_000826b2(int,int);
extern int FUN_00082a42(int,int,void*);
extern int FUN_00082cba(int,int,int);

int FUN_0005b890(int param_1, int param_2, int param_3)
{
    int uVar1;
    int iVar2;
    int iVar3;
    int iVar4;
    short *puVar5;
    unsigned char *puVar6;
    unsigned int uVar7;
    int local_28;
    int local_24;

    uVar1 = 0x000f2b3a;
    if (*(int *)(param_1 + 8) != 0x0005a465) {
        return 1;
    }
    puVar6 = *(unsigned char **)(param_1 + 0xc);
    if (puVar6 == (unsigned char *)0x20002a20) {
        iVar4 = 0;
        iVar2 = 0x2000ff19;
        do {
            iVar3 = FUN_000826b2(iVar2, uVar1);
            if (iVar3 == 0) {
                iVar3 = FUN_00056f08(*(unsigned char *)(iVar2 + -1), iVar2, 7);
                if (iVar3 == 0) {
                    puVar5 = *(short **)(*(int *)(param_3 + 0x10) + 0x10);
                    FUN_0005a128(*(unsigned char *)(iVar2 + -1), iVar2, *puVar5, puVar5[1]);
                }
                else {
                    FUN_000566a4(0);
                }
            }
            iVar4 = iVar4 + 1;
            iVar2 = iVar2 + 0xc;
        } while (iVar4 != 3);
    }
    if (*(short *)(puVar6 + 8) != *(short *)(param_3 + 0xc)) {
        return 1;
    }
    iVar2 = FUN_00056e74(*puVar6, (int)(puVar6 + 1));
    if (iVar2 == 0) {
        return 1;
    }
    if ((*(char *)(iVar2 + 0xd) == '\a') &&
        ((*(int (**)(int,int))(puVar6 + 0x14) == 0 ||
         (iVar4 = (**(int (**)(int,int))(puVar6 + 0x14))(iVar2, param_1), iVar4 != 0)))) {
        iVar4 = FUN_00082cba(iVar2, param_1, 0x94);
        if (iVar4 == 0) {
            if (*(short *)(param_3 + 0xc) == 2) {
                uVar7 = *(unsigned short *)(puVar6 + 8) & 2;
                if ((*(unsigned short *)(puVar6 + 8) & 2) != 0) {
                    iVar4 = FUN_0005b270(iVar2, *(unsigned short *)(param_3 + 4), *(int *)(param_3 + 0x10));
                    if (iVar4 != 0) goto LAB_0005b9a4;
                    *(char *)(*(int *)(param_3 + 0x10) + 0x16) =
                         *(char *)(*(int *)(param_3 + 0x10) + 0x16) + '\x01';
                    uVar7 = 0;
                }
            }
            else {
                if (*(short *)(param_3 + 0xc) != 1) {
                    FUN_000566a4(iVar2);
                    *(int *)(param_3 + 8) = 0;
                    return 1;
                }
                uVar7 = *(unsigned short *)(puVar6 + 8) & 1;
                if ((*(unsigned short *)(puVar6 + 8) & 1) != 0) {
                    iVar4 = FUN_0005b680(iVar2, *(unsigned short *)(param_3 + 4), *(int *)(param_3 + 0x10));
LAB_0005b9a4:
                    FUN_000566a4(iVar2);
                    *(int *)(param_3 + 8) = iVar4;
                    if (-1 < iVar4) {
                        return 1;
                    }
                    return 0;
                }
            }
            FUN_000566a4(iVar2);
            *(unsigned int *)(param_3 + 8) = uVar7;
            return 1;
        }
        local_24 = 0x000f4ad5;
        local_28 = 2;
        FUN_00082a42(0x00088128, 0x1080, &local_28);
    }
    FUN_000566a4(iVar2);
    return 1;
}

