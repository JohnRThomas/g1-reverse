/* Reconstructed parse_receiver_pack_pkcs7 @ 0x19cd0  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00086c04(int, ...);

unsigned int parse_receiver_pack_pkcs7(int param_1, unsigned char *param_2, unsigned int param_3)
{
    unsigned char bVar1, bVar2;
    unsigned short uVar3;
    unsigned char *pbVar4 = (unsigned char*)0x20010320UL;
    unsigned short *puVar5 = (unsigned short*)0x2000d6f4UL;
    unsigned int uVar6;
    unsigned int uVar7;
    int iVar8;
    unsigned int uVar9;

    if (param_2 == (unsigned char*)0) {
        uVar7 = 0xb0;
        iVar8 = *(volatile int*)0x20007554UL;
        uVar6 = 0x0009b371UL;
    } else {
        if (param_1 != 0) {
            if (param_3 < 3) {
                if (*(volatile int*)0x20007554UL != 0) {
                    FUN_00019c70(0x0009b3b5UL, 0x0009e0d0UL, 0xbbUL, param_3);
                    return 0xca;
                }
                DEBUG_PRINT(0x0009b3b5UL, 0x0009e0d0UL, 0xbbUL, param_3);
                return 0xca;
            }
            bVar1 = param_2[2];
            uVar9 = (unsigned int)*param_2;
            bVar2 = param_2[1];
            if (bVar1 == 0) {
                *pbVar4 = *param_2;
                *puVar5 = (unsigned short)bVar1;
            }
            if (*pbVar4 != uVar9) {
                if (*(volatile int*)0x20007554UL != 0) {
                    FUN_00019c70(0x0009b3e0UL, 0x0009e0d0UL);
                    return 0xca;
                }
                DEBUG_PRINT(0x0009b3e0UL, 0x0009e0d0UL, 0xd0UL, uVar9, (unsigned int)*pbVar4);
                return 0xca;
            }
            uVar3 = *puVar5;
            FUN_00086c04(param_1 + (unsigned int)uVar3, param_2 + 3, param_3 - 3, uVar9, param_1, param_2);
            if ((unsigned int)bVar1 == (unsigned int)(bVar2 - 1)) {
                uVar6 = 0xc9;
            } else {
                uVar6 = 0xcb;
            }
            *puVar5 = (unsigned short)((int)param_3 + (uVar3 - 3));
            return uVar6;
        }
        uVar7 = 0xb5;
        iVar8 = *(volatile int*)0x20007554UL;
        uVar6 = 0x0009b38fUL;
    }
    if (iVar8 == 0) {
        DEBUG_PRINT(uVar6, 0x0009e0d0UL, uVar7);
    } else {
        FUN_00019c70(uVar6, 0x0009e0d0UL, uVar7);
    }
    return 0xca;
}

