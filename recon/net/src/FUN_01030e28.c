/* net-core FUN_01030e28 @ 0x1030e28  (parity 300 trials PROVEN) */
#include <stdint.h>

extern int FUN_01030dd0(unsigned int *a);

#define LIT_ef8 0xfffcf0f0u

unsigned int FUN_01030e28(unsigned int *param_1, int param_2, int param_3)
{
    unsigned int uVar2 = LIT_ef8;
    unsigned int *puVar7 = param_1 + param_2;
    unsigned int uVar1, uVar4, uVar5, uVar6, uVar8;
    int iVar3;
    unsigned int local_2c;

    while (1) {
        if (param_1 == puVar7) {
            return 0;
        }
        uVar6 = *param_1;
        uVar4 = uVar6 & 0x7f;
        if (uVar4 == 0x7f) {
            uVar4 = 0xffffffffu;
        }
        int do_tail = 0;
        switch (uVar6 >> 0x10) {
        case 0:
            *(volatile unsigned int *)(param_3 + 0x50c) = uVar4;
            do_tail = 1;
            break;
        case 1:
            *(volatile unsigned int *)(param_3 + 0x514) = uVar4;
            goto LAB_78;
        case 2:
            *(volatile unsigned int *)(param_3 + 0x508) = uVar4;
            do_tail = 1;
            break;
        case 3:
            *(volatile unsigned int *)(param_3 + 0x510) = uVar4;
        LAB_78:
            if (uVar4 != 0xffffffffu) {
                uVar8 = 0;
                goto LAB_80;
            }
            goto LAB_6e;
        default:
            return 0xffffff7au;
        }

        if (do_tail && uVar4 != 0xffffffffu) {
            local_2c = uVar4;
            iVar3 = FUN_01030dd0(&local_2c);
            uVar8 = 1;
            *(volatile int *)(iVar3 + 8) = 1 << (local_2c & 0xff);
        LAB_80:
            uVar5 = *param_1;
            uVar1 = uVar8;
            if ((uVar5 & 0x2000) != 0) {
                uVar8 = 0;
                uVar1 = 1;
            }
            local_2c = uVar4;
            iVar3 = FUN_01030dd0(&local_2c);
            iVar3 = iVar3 + (int)local_2c * 4;
            *(volatile unsigned int *)(iVar3 + 0x200) =
                (((uVar6 << 0x13) >> 0x1c) << 8) |
                (((uVar5 << 0x17) >> 0x1e) << 2) |
                uVar8 |
                (*(volatile unsigned int *)(iVar3 + 0x200) & uVar2) |
                (uVar1 << 1);
        }
    LAB_6e:
        param_1 = param_1 + 1;
    }
}
