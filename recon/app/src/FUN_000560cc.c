/* Reconstructed FUN_000560cc @ 0x560cc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern int FUN_000543c8(void);
extern void FUN_00056080(void);
extern int FUN_0005f518(void);
extern void FUN_0005f558(void);
extern void FUN_00072880(void);
extern int FUN_00072908(void);
extern void FUN_0007e2ec(unsigned long, unsigned long);
extern void FUN_0007e2fa(unsigned long, ...);
extern void FUN_0008137e(void);
extern void FUN_000813ca(void);
extern int FUN_00083730(void);
extern void FUN_00083740(void);
extern int FUN_000836e8(void);

#define S16(a) (*(volatile int16_t*)(a))
#define U16(a) (*(volatile uint16_t*)(a))
#define U32(a) (*(volatile uint32_t*)(a))
#define I32(a) (*(volatile int32_t*)(a))

unsigned FUN_000560cc(int param_1, int param_2, int param_3, unsigned param_4)
{
    int iVar2 = 0x20002000;
    int iVar4;
    unsigned uVar8;
    int puVar9;
    int unaff_r10 = 0;

    iVar4 = (U16(iVar2 + 0x104) == 0) ? 0 : (iVar2 + 0x108);
    (void)iVar4;
    if (FUN_00072908() != 0) {
        return 0xffffff97;
    }
    if (param_3 == 0) {
        param_3 = FUN_000836e8();
    } else {
        unsigned local_2c = U16(iVar2 + 0x104);
        int iVar4b = param_3 + 0xc;
        unsigned uVar5 = (unsigned)FUN_00083730();
        uint16_t uVar3;
        if (uVar5 <= local_2c) {
            uVar3 = (uint16_t)FUN_00083730();
        } else {
            uVar3 = U16(iVar2 + 0x104);
        }
        (void)uVar3;
        FUN_00083740();
        FUN_0005f558();
    }
    puVar9 = (int)U32(param_3 + 0x18);
    if (*(volatile int8_t*)(param_1 + 0xd) == 7) {
        if (puVar9 == 0) {
            int v = (int)U32(param_1 + 0x18);
            int iVar4c;
            if (v == 0) {
                unaff_r10 = param_1 + 0x1c;
                iVar4c = I32(param_1 + 0x1c);
            } else {
                unaff_r10 = v + 0xc;
                iVar4c = I32(v + 0xc);
            }
            I32(unaff_r10) = iVar4c + 1;
        } else {
            U32(puVar9) = 0;
            if (U32(param_1 + 0x18) == 0) {
                U32(param_1 + 0x14) = (uint32_t)puVar9;
                U32(param_1 + 0x18) = (uint32_t)puVar9;
            } else {
                U32(U32(param_1 + 0x18)) = (uint32_t)puVar9;
                U32(param_1 + 0x18) = (uint32_t)puVar9;
            }
        }
        int puVar6 = FUN_0005f518();
        U16(puVar6) = (uint16_t)(U16(param_1) | ((param_4 & 0xfd) << 0xc));
        U16(puVar6 + 2) = (uint16_t)(S16(param_3 + 0x10) - 4);
        *(volatile uint8_t*)(param_3 + 0x18) = 2;
        if (FUN_000543c8() == 0) {
            return 0;
        }
        FUN_000813ca();
        if (puVar9 == 0) {
            if (I32(unaff_r10) == 0) {
                FUN_0007e2fa(((unsigned long)"ASSERTION FAIL [%s] @ %s:%d\n"), ((unsigned long)"*pending_no_cb > 0"), ((unsigned long)"WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c"), 627);
                FUN_0007e2ec(((unsigned long)"WEST_TOPDIR/zephyr/subsys/bluetooth/host/conn.c"), 627);
            }
            I32(unaff_r10) = I32(unaff_r10) - 1;
        } else {
            FUN_0008137e();
        }
        uVar8 = 0xfffffffb;
    } else {
        uVar8 = 0xffffff80;
    }
    FUN_00072880();
    if (puVar9 != 0) {
        U32(param_3 + 0x18) = 0;
        FUN_00056080();
    }
    return uVar8;
}

