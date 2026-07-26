/* net-core FUN_010237b0 @ 0x10237b0  (parity 300 trials PROVEN) */
#include <stdint.h>
extern int FUN_0102286c(int a0, unsigned int a1);
extern void FUN_01024440(void);
extern unsigned long long FUN_01025084(int a0, int a1);
extern void FUN_010256dc(unsigned int a0, unsigned int a1, unsigned int a2, unsigned int a3);
#include <cmsis_gcc.h>

static inline void enableIRQinterrupts(void) { __enable_irq(); }
static inline void disableIRQinterrupts(void) { __disable_irq(); }
static inline int isIRQinterruptsEnabled(void) { return (int)__get_PRIMASK(); }
static inline int isCurrentModePrivileged(void) { return (__get_CONTROL() & 1u) == 0; }

typedef void (*cbfn)(unsigned int);

int FUN_010237b0(unsigned int param_1)
{
    unsigned char uVar1;
    unsigned char bVar2;
    char cVar3;
    int iVar4;
    unsigned int uVar5;
    int iVar9;
    unsigned int uVar10;
    unsigned char *puVar11;
    int iVar12;
    unsigned int uVar13;
    int iVar14;
    int iVar15;
    int iVar16;
    unsigned int uVar17;
    unsigned char *puVar18;
    int bVar19;
    unsigned long long uVar20;

    iVar12 = 0;
    iVar4 = 0x210016f0;
    iVar14 = 1;
    iVar15 = 0x210016f0 + 0x50;
    (void)uVar1; (void)uVar5; (void)iVar9; (void)iVar16; (void)uVar20;

    for (;;) {
        for (;;) {
            if (iVar14 == 0) enableIRQinterrupts();
            *(volatile unsigned char *)(iVar4 + 0x39) = 0;
            bVar2 = *(volatile unsigned char *)(iVar4 + 0x49);
            {
                volatile unsigned int *src = (volatile unsigned int *)(iVar15 + (unsigned int)bVar2 * 0x40);
                uVar13 = (bVar2 + 1) & 1;
                volatile unsigned int *dst = (volatile unsigned int *)(iVar15 + uVar13 * 0x40);
                unsigned int t[16];
                int k;
                for (k = 0; k < 16; k++) t[k] = src[k];
                for (k = 0; k < 16; k++) dst[k] = t[k];
            }
            iVar16 = (unsigned int)bVar2 * 3 + 0x30;
            iVar9 = uVar13 * 3 + 0x30;
            uVar1 = *(volatile unsigned char *)(iVar4 + iVar16 + 2);
            *(volatile unsigned short *)(iVar4 + iVar9) = *(volatile unsigned short *)(iVar4 + iVar16);
            *(volatile unsigned char *)(iVar9 + iVar4 + 2) = uVar1;
            if (*(volatile char *)(iVar4 + 0x39) == 0) break;
        }
        iVar9 = uVar13 * 0x20;
        if (*(volatile char *)(iVar4 + (param_1 + uVar13 * 0x20) * 2 + 0x50) != 3) goto LAB_010238cc;
        uVar17 = (unsigned int)*(volatile unsigned char *)(uVar13 * 3 + iVar4 + 0x30);
        uVar10 = uVar17;
        if (param_1 == uVar17) {
            if (uVar17 == 0x20) goto LAB_010238cc;
            iVar16 = 0;
LAB_01023a32:
            *(volatile unsigned char *)(uVar13 * 3 + iVar4 + 0x30) =
                *(volatile unsigned char *)(iVar4 + (uVar10 + iVar9) * 2 + 0x51);
        } else {
            for (;;) {
                uVar5 = uVar10;
                if (uVar5 == 0x20) goto LAB_010238cc;
                iVar16 = iVar9 + (int)uVar5;
                uVar10 = (unsigned int)*(volatile unsigned char *)(iVar4 + iVar16 * 2 + 0x51);
                if (param_1 == uVar10) break;
            }
            if (uVar10 == 0x20) goto LAB_010238cc;
            if (uVar17 == uVar10) goto LAB_01023a32;
            uVar5 = iVar4 + (uVar5 + iVar9) * 2;
            *(volatile unsigned char *)(uVar5 + 0x51) = *(volatile unsigned char *)(iVar4 + (uVar10 + iVar9) * 2 + 0x51);
        }
LAB_010239f4:
        *(volatile unsigned char *)(iVar4 + (iVar9 + (int)param_1) * 2 + 0x50) = 1;

        iVar14 = 0;
        bVar19 = isCurrentModePrivileged();
        if (bVar19) {
            iVar14 = isIRQinterruptsEnabled();
        }
        disableIRQinterrupts();
        if (*(volatile char *)(iVar4 + 0x39) == 0) break;
    }
    iVar15 = 0;
    if ((param_1 == uVar17) && (*(volatile char *)(iVar4 + 0x4a) == ' ')) {
        uVar20 = FUN_0102286c(2, uVar13);
        iVar15 = (int)uVar20;
        if (iVar15 == 0) {
            goto LAB_010238e0;
        }
    }
    *(volatile unsigned char *)(iVar4 + 0x49) = (unsigned char)(~*(volatile unsigned char *)(iVar4 + 0x49) & 1);
    *(volatile unsigned char *)(iVar4 + 0x39) = 0xff;
    if (iVar15 == 2) {
        uVar20 = FUN_01025084((int)uVar20, (int)((unsigned long long)uVar20 >> 0x20));
        uVar13 = (unsigned int)((unsigned long long)uVar20 >> 0x20);
        uVar5 = (unsigned int)uVar20;
        uVar17 = *(volatile unsigned int *)(iVar4 + 0x10);
        uVar10 = *(volatile unsigned int *)(iVar4 + 0x14);
        if (uVar10 <= uVar13 && (unsigned int)(uVar5 <= uVar17) <= uVar10 - uVar13) {
            FUN_010256dc(0x70, 0x816, 0, 0);
        }
        uVar13 = (uVar10 - uVar13) - (unsigned int)(uVar17 < uVar5);
        {
            int bVar19b = (0x7fffff < (int)(uVar17 - uVar5));
            if (uVar13 != 0 || uVar13 < (unsigned int)bVar19b) {
                FUN_010256dc(0x70, 0x817, uVar13, uVar13 - (unsigned int)(!bVar19b));
            }
        }
        FUN_01024440();
        iVar12 = 1;
        if (*(volatile cbfn *)(iVar4 + 0x4d0) != 0) {
            (*(volatile cbfn *)(iVar4 + 0x4d0))(0);
        }
    } else if (iVar15 == 1) {
        iVar12 = 1;
        if (*(volatile cbfn *)(iVar4 + 0x4d0) != 0) {
            (*(volatile cbfn *)(iVar4 + 0x4d0))(0xffffffff);
        }
    } else {
        iVar12 = 1;
    }
LAB_010238e0:
    if (iVar14 == 0) enableIRQinterrupts();
    return iVar12;

LAB_010238cc:
    goto LAB_010238e0;
}
