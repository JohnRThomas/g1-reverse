/* Reconstructed FUN_00050558 @ 0x50558  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_00080780(int,int,void*);

int FUN_00050558(int param_1, unsigned char *param_2)
{
    int uVar2;
    int local_40, local_3c, uStack_38;
    int local_20, local_1c;

    local_1c = 0x000f1df9;
    local_20 = 2;
    FUN_00080780(0x00088258, 0x1040, &local_20);
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x13 < 0) {
        local_20 = 2;
        local_1c = 0x000f1e0f;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x17;
    } else {
        uVar2 = 0x16;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x14 < 0) {
        local_1c = 0x000f1c82;
        local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x18;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x16 < 0) {
        local_1c = 0x000f1e20;
        local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        if (*(volatile int *)(0xe000ed00 + 0x28) << 0x10 < 0) {
            local_3c = 0x000f1e39;
            local_40 = 3;
            uStack_38 = *(volatile int *)(0xe000ed00 + 0x38);
            FUN_00080780(0x00088258, 0x1840, &local_40);
            if (param_1 != 0) {
                *(volatile unsigned int *)(0xe000ed00 + 0x28) = *(volatile unsigned int *)(0xe000ed00 + 0x28) & 0xffff7fff;
            }
        }
        uVar2 = 0x19;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x15 < 0) {
        local_1c = 0x000f1e4e;
        local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x1a;
    }
    if (*(volatile int *)(0xe000ed00 + 0x28) << 0x17 < 0) {
        local_1c = 0x000f1e69;
        local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x1b;
    } else if (*(volatile int *)(0xe000ed00 + 0x28) << 0x12 < 0) {
        local_1c = 0x000f1ce2;
        local_20 = 2;
        FUN_00080780(0x00088258, 0x1040, &local_20);
        uVar2 = 0x1c;
    }
    *(volatile unsigned int *)(0xe000ed00 + 0x28) = *(volatile unsigned int *)(0xe000ed00 + 0x28) | 0xff00;
    *param_2 = 0;
    return uVar2;
}

