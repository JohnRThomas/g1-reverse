/* Reconstructed FUN_0005e47c @ 0x5e47c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00052cdc(int);
extern int FUN_0005dc2c(int,int);
extern int FUN_0005e6a8(int,int);
extern int FUN_0005e9a0(int,int);
extern void FUN_0005ea18(int record);
extern int FUN_00082ff6(int,int);
extern int FUN_00083074(int,int,void*);
extern int FUN_0008307a(void);

void FUN_0005e47c(int param_1)
{
    int iVar1;
    int iVar2;
    unsigned int uVar3;
    uint32_t *puVar4;
    unsigned char bVar6;
    int iVar7;
    uint32_t *puVar8;
    int iVar9;
    int local_28, local_24, uStack_20;
    short local_1c;
    uint32_t *puVar5;

    iVar1 = FUN_0008307a();
    if (iVar1 == 0) return;
    iVar9 = iVar1 + 4;
    iVar2 = FUN_00082ff6(iVar9, 3);
    if (iVar2 == 0) return;
    if (*(int *)(param_1 + 0xc0) != 0) {
        FUN_0005ea18(*(int *)(param_1 + 0xc0));
    }
    iVar2 = FUN_0005e6a8(*(unsigned char *)(param_1 + 8), param_1 + 0x90);
    *(int *)(param_1 + 0xc0) = iVar2;
    if (iVar2 == 0) {
        uStack_20 = FUN_00052cdc(param_1 + 0x90);
        local_24 = 0x000f4e60;
        local_1c = 0x200;
        local_28 = 0x01000003;
        FUN_00083074(0x00088180, 0x1c40, &local_28);
        FUN_0005dc2c(iVar1, 8);
        return;
    }
    iVar2 = FUN_00082ff6(iVar9, 0xe);
    if (iVar2 != 0) {
        *(unsigned char *)(*(int *)(param_1 + 0xc0) + 0xd) = *(unsigned char *)(*(int *)(param_1 + 0xc0) + 0xd) | 2;
    }
    uVar3 = (unsigned int)*(unsigned char *)(iVar1 + 8);
    iVar2 = *(int *)(param_1 + 0xc0);
    if (uVar3 < 4) {
        if (uVar3 != 0) {
LAB_0005e512:
            iVar2 = *(int *)(param_1 + 0xc0);
            bVar6 = *(unsigned char *)(iVar2 + 0xd) | 1;
            goto LAB_0005e51c;
        }
    } else if (uVar3 - 5 < 2) {
        *(unsigned char *)(iVar2 + 0xd) = *(unsigned char *)(iVar2 + 0xd) | 0x20;
        goto LAB_0005e512;
    }
    *(unsigned char *)(iVar2 + 0xd) = *(unsigned char *)(iVar2 + 0xd) & 0xdf;
    iVar2 = *(int *)(param_1 + 0xc0);
    bVar6 = *(unsigned char *)(iVar2 + 0xd) & 0xfe;
LAB_0005e51c:
    *(unsigned char *)(iVar2 + 0xd) = bVar6;
    bVar6 = *(unsigned char *)(iVar1 + 0x14);
    if (*(unsigned char *)(iVar1 + 0xd) <= *(unsigned char *)(iVar1 + 0x14)) {
        bVar6 = *(unsigned char *)(iVar1 + 0xd);
    }
    *(unsigned char *)(*(int *)(param_1 + 0xc0) + 0xc) = bVar6;
    iVar2 = FUN_00082ff6(iVar9, 5);
    iVar7 = *(int *)(param_1 + 0xc0);
    if (iVar2 == 0) {
        *(unsigned char *)(iVar7 + 0xd) = *(unsigned char *)(iVar7 + 0xd) & 0xef;
    } else {
        *(unsigned char *)(iVar7 + 0xd) = *(unsigned char *)(iVar7 + 0xd) | 0x10;
        iVar2 = FUN_00082ff6(iVar9, 0xd);
        if (iVar2 != 0) {
            FUN_0005e9a0(*(uint32_t *)(param_1 + 0xc0), 0x20);
            puVar4 = (uint32_t *)(iVar1 + 0x47);
            puVar8 = (uint32_t *)(*(int *)(param_1 + 0xc0) + 0x1a);
            do {
                puVar5 = puVar4 + 1;
                *puVar8 = *puVar4;
                puVar4 = puVar5;
                puVar8 = puVar8 + 1;
            } while (puVar5 != (uint32_t *)(iVar1 + 0x57));
            iVar1 = *(int *)(param_1 + 0xc0);
            *(uint32_t *)(iVar1 + 0x10) = 0;
            *(uint32_t *)(iVar1 + 0x14) = 0;
            *(unsigned short *)(*(int *)(param_1 + 0xc0) + 0x18) = 0;
        }
    }
    return;
}
