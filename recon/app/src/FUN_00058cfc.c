/* Reconstructed FUN_00058cfc @ 0x58cfc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern uint64_t FUN_000582b8(int);
extern void FUN_0005f24c(int);
extern int FUN_0005f2d4(int);
extern int FUN_0005f594(int, int);
extern void FUN_0007e2ec(int, int);
extern void FUN_0007e2fa(int, int, int, int);
extern void FUN_00081ddc(int, int, int);
extern void FUN_000821f4(int, int, int, int);
extern int FUN_00082236(int, int);
extern int FUN_00082396(int);

int FUN_00058cfc(int param_1, int param_2)
{
    volatile uint8_t *pbVar3;
    int cVar1 = 0;
    int iVar7, iVar8, iVar6;
    int local_44;
    unsigned uVar5 = 0;
    uint64_t uVar9;
    volatile int logbuf[8];

    if (*(volatile int16_t*)(param_2 + 0x10) == 0) {
        FUN_00081ddc(0x00088100, 0x1040, (int)(intptr_t)logbuf);
        return 0;
    }
    pbVar3 = (volatile uint8_t*)(intptr_t)FUN_0005f594(param_2 + 0xc, 1);
    iVar8 = 0x0008b2b4;
    if (*(volatile int*)(param_1 - 8) == 0) return 0;
    iVar6 = 0;
    do {
        iVar7 = 0x0008b2b4 + iVar6 * 8;
        if (*(volatile uint8_t*)(0x0008b2b4 + iVar6 * 8) == *pbVar3) {
            local_44 = *(volatile int*)(param_1 + 0x13c);
            if (local_44 != 0) goto LAB_dbc;
            {
                int t = FUN_0005f2d4(param_2);
                cVar1 = *(volatile int8_t*)(iVar7 + 2);
                *(volatile int*)(param_1 + 0x13c) = t;
            }
            if (cVar1 == 1) {
                iVar7 = FUN_00082236(param_1 + 0x118, local_44);
                goto joined;
            } else if (cVar1 == 5) {
                iVar7 = FUN_00082236(param_1 + 0x118, 1);
            joined:
                if (iVar7 != 0) {
                    FUN_00081ddc(0x00088100, 0x1080, (int)(intptr_t)logbuf);
                    goto LAB_d9c;
                }
            }
            iVar8 = iVar8 + iVar6 * 8;
            if ((unsigned)*(volatile uint16_t*)(param_2 + 0x10) < (unsigned)*(volatile uint8_t*)(iVar8 + 1)) {
                FUN_00081ddc(0x00088100, 0x2040, (int)(intptr_t)logbuf);
                if (*(volatile int8_t*)(iVar8 + 2) != 1) goto LAB_d9c;
                iVar8 = 4;
            } else {
                iVar8 = ((int(*)(int,int))(*(volatile uintptr_t*)(iVar8 + 4)))(param_1 - 8, param_2);
                if (cVar1 != 1 || iVar8 == 0) goto LAB_d9c;
            }
            uVar5 = *pbVar3;
            goto LAB_e12;
        }
        iVar6 = iVar6 + 1;
    } while (iVar6 != 0x1e);
    if (*(volatile int*)(param_1 + 0x13c) != 0) {
    LAB_dbc:
        FUN_0007e2fa(0x00099cbd, 0x000f45af, 0x000f4388, 0xb54);
        FUN_0007e2ec(0x000f4388, 0xb54);
    }
    {
        int t = FUN_0005f2d4(param_2);
        *(volatile int*)(param_1 + 0x13c) = t;
    }
    FUN_00081ddc(0x00088100, 0x1880, (int)(intptr_t)logbuf);
    uVar9 = FUN_000582b8(*pbVar3);
    uVar5 = (unsigned)(uVar9 >> 0x20);
    if ((int)uVar9 != 0 && (int)uVar9 != 5) {
        iVar8 = 6;
    LAB_e12:
        FUN_000821f4(param_1 - 8, uVar5, 0, iVar8);
    }
LAB_d9c:
    FUN_0005f24c(*(volatile int*)(param_1 + 0x13c));
    *(volatile int*)(param_1 + 0x13c) = 0;
    return 0;
}

