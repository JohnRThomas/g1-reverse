/* Reconstructed FUN_0005d964 @ 0x5d964  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_0005cac0(int);
extern int FUN_0005caec(int);
extern int FUN_0005cc30(int);
extern unsigned int FUN_0005d568(int, unsigned int);
extern int FUN_0005e6a8(int, int);
extern int FUN_0005e7c8(int, int, int);
extern void FUN_0005f24c(int);
extern int FUN_0005f5d0(int, int);
extern int FUN_00081820(int, int, int, int, int);
extern int FUN_00082ff6(int, int);
extern int FUN_0008307a(void);
extern void FUN_00083090(int, int);
extern int FUN_000830b0(int, int);

int FUN_0005d964(int param_1)
{
    int iVar2, iVar3, iVar6, iVar8, cac;
    unsigned uVar7;
    int puVar5;
    uint8_t uVar1;

    if (*(volatile uint8_t*)(param_1 + 3) != 1) return -0x16;
    iVar2 = FUN_0008307a();
    if (iVar2 == 0) return -0x80;
    iVar8 = iVar2 + 4;
    iVar3 = FUN_00082ff6(iVar8, 4);
    if (iVar3 != 0) return -5;
    iVar3 = FUN_00082ff6(iVar8, 3);
    if (iVar3 != 0) return -0x10;
    iVar3 = FUN_00082ff6(iVar8, 1);
    if (iVar3 != 0) return -0x10;
    cac = FUN_0005cac0(iVar2);
    uVar7 = *(volatile uint8_t*)(*(volatile int*)(iVar2 + 0xf0) + 10);
    if (uVar7 == 3) {
        iVar6 = FUN_0005caec(iVar2);
        if (iVar6 != 3) goto LAB_5da60;
        if (cac != 0) {
            uVar7 = *(volatile uint32_t*)(cac + 0xc);
            if (uVar7 == 0) goto MAIN;
            goto LAB_5da60;
        }
    } else if (uVar7 > 3) {
        if (uVar7 != 4) goto MAIN;
        iVar6 = FUN_0005caec(iVar2);
        if (iVar6 == 3) {
            if (cac == 0) goto MAIN;
            if (*(volatile int*)(cac + 0xc) == 0) goto MAIN;
        }
        uVar7 = *(volatile uint8_t*)0x2001d532;
        if (uVar7 == 0) goto MAIN;
        goto LAB_5da60;
    } else {
        if ((uint32_t)(uVar7 - 1) <= 1) goto LAB_5da60;
    }
MAIN:
    iVar3 = FUN_00082ff6(param_1 + 4, 0xb);
    if (iVar3 != 0) return -0x16;
    if (*(volatile int*)(param_1 + 0xc0) == 0) {
        iVar3 = FUN_0005e7c8(0x20, *(volatile uint8_t*)(param_1 + 8), param_1 + 0x90);
        *(volatile int*)(param_1 + 0xc0) = iVar3;
        if (iVar3 == 0) {
            iVar3 = FUN_0005e7c8(4, *(volatile uint8_t*)(param_1 + 8), param_1 + 0x90);
            *(volatile int*)(param_1 + 0xc0) = iVar3;
        }
    }
    iVar3 = *(volatile int*)(param_1 + 0xc0);
    if (iVar3 == 0) return -0x16;
    if ((*(volatile uint16_t*)(iVar3 + 0xe) & 0x24) == 0) return -0x16;
    if (*(volatile uint8_t*)(param_1 + 10) <= 2) goto LAB_5da60;
    if ((*(volatile uint8_t*)(iVar3 + 0xd) & 1) == 0) return -0x16;
    if (*(volatile uint8_t*)(param_1 + 10) == 3) goto LAB_5da60;
    if ((*(volatile uint16_t*)(iVar3 + 0xe) & 0x20) == 0) return -0x16;
    if (*(volatile int8_t*)(iVar3 + 0xc) != 0x10) return -0x16;
LAB_5da60:
    iVar3 = *(volatile int*)(param_1 + 0xc0);
    if (iVar3 == 0) {
        iVar3 = FUN_0005e6a8(*(volatile uint8_t*)(param_1 + 8), param_1 + 0x90);
        *(volatile int*)(param_1 + 0xc0) = iVar3;
        if (iVar3 == 0) return -0xc;
    }
    iVar3 = FUN_0005cc30(iVar2);
    if (iVar3 != 0) return -0x69;
    iVar6 = FUN_000830b0(iVar2, 0xb);
    if (iVar6 == 0) return -0x69;
    puVar5 = FUN_0005f5d0(iVar6 + 0xc, 1);
    uVar1 = (uint8_t)FUN_0005d568(iVar2, 9);
    *(volatile uint8_t*)puVar5 = uVar1;
    {
        int rv = FUN_00081820(param_1, 6, iVar6, 0, 0);
        if (rv == 0) {
            FUN_00083090(iVar8, 0xf);
            FUN_00083090(iVar2, 1);
            return 0;
        }
        FUN_0005f24c(iVar6);
        return rv;
    }
}

