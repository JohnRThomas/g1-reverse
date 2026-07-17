/* Reconstructed button_init @ 0x17a40  (parity: 200/200 trials, PROVEN) */
#include <stdint.h>
extern int DEBUG_PRINT(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
extern int FUN_00017688(unsigned int, unsigned int);
extern void FUN_00017768(unsigned int, unsigned int, unsigned int);
extern unsigned int FUN_000177c4(unsigned int, unsigned int);
extern void FUN_00017858(unsigned int, unsigned int);
extern unsigned int FUN_00017980(unsigned int);
extern void FUN_00019c70(void);
extern int FUN_00025284(void);
extern int FUN_0008638c(unsigned int);

unsigned char button_init(void)
{
    volatile int *piVar2 = (volatile int *)0x2000230cUL;
    unsigned int uVar15 = 0;
    int iVar5, iVar6, iVar16;
    unsigned char bVar4;
    unsigned int uVar7,uVar8,uVar9,uVar10,uVar11,uVar12,uVar13;
    unsigned int uVar14 = 0, uVar18;
    void *pcVar17;
    unsigned int gpio_specs[9][2];
    volatile const unsigned int *spec_data =
        (volatile const unsigned int *)0x00088340UL;

    for (unsigned int spec = 0; spec < 9; ++spec) {
        gpio_specs[spec][0] = spec_data[spec * 2];
        gpio_specs[spec][1] = spec_data[spec * 2 + 1];
    }

    FUN_00017688((uintptr_t)gpio_specs[0], 0x10000);
    FUN_00017688((uintptr_t)gpio_specs[1], 0x10000);
    FUN_00017688((uintptr_t)gpio_specs[2], 0x10000);
    FUN_00017688((uintptr_t)gpio_specs[3], 0x10000);
    FUN_00017688((uintptr_t)gpio_specs[4], 0x30000);
    FUN_00017768(0x00087b60UL, 0x18, 1);
    FUN_00017688((uintptr_t)gpio_specs[5], 0x30000);
    FUN_00017768(0x00087b60UL, 0x13, 0);
    FUN_00017688((uintptr_t)gpio_specs[6], 0x30000);
    FUN_00017768(0x00087b60UL, 0x15, 0);
    FUN_00017688((uintptr_t)gpio_specs[7], 0x30000);
    FUN_00017768(0x00087b60UL, 0x1e, 1);
    FUN_00017688((uintptr_t)gpio_specs[8], 0x30000);
    FUN_00017768(0x00087b60UL, 0x17, 0);

    iVar16 = 0x00087b48;
    iVar5 = FUN_0008638c(0x00087b48UL);
    if (iVar5 == 0) {
        if (1 < *piVar2) {
            iVar5 = *(volatile int *)0x20007554UL;
            uVar15 = 0x00099f81UL;
LAB_b48_1:
            if (iVar5 == 0) {
                DEBUG_PRINT(uVar15, 0x0009a126UL, 0,0,0,0);
            } else {
                FUN_00019c70();
            }
        }
    } else {
        iVar6 = FUN_00017688(0x000889d0UL, 0x10000);
        iVar5 = 0x20006a10;
        if (-1 < iVar6) {
            *(volatile unsigned int *)0x20006a14UL = 0x0001793dUL;
            *(volatile unsigned int *)(iVar5+8) = 0x200;
            pcVar17 = *(void **)(*(int *)(iVar16 + 8) + 0x1c);
            if (pcVar17 == 0) {
                if (1 < *piVar2) {
                    iVar5 = *(volatile int *)0x20007554UL;
                    uVar15 = 0x00099fa8UL;
                    goto LAB_b48_1;
                }
            } else {
                int r = ((int (*)(int,int,int))pcVar17)(iVar16, iVar5, 1);
                if (r < 0) {
                    if (1 < *piVar2) {
                        iVar5 = *(volatile int *)0x20007554UL;
                        uVar15 = 0x00099fa8UL;
                        goto LAB_b48_1;
                    }
                } else {
                    FUN_00017858(0x000889d0UL, 0x5c00000);
                    if (1 < *piVar2) {
                        if (*(volatile int *)0x20007554UL == 0) {
                            DEBUG_PRINT(0x00099fd2UL, 0x0009a126UL, 9,0,0,0);
                        } else {
                            FUN_00019c70();
                        }
                    }
                }
            }
        }
    }

    iVar5 = FUN_0008638c(0x00087b48UL);
    if (iVar5 == 0) {
        if (*piVar2 < 2) goto LAB_c40;
        iVar16 = *(volatile int *)0x20007554UL;
        uVar15 = 0x00099f81UL;
        uVar14 = 0x0009a119UL;
    } else {
        iVar6 = FUN_00017688(0x000889e0UL, 0x10000);
        iVar5 = 0x20006a04;
        if (iVar6 < 0) goto LAB_c40;
        *(volatile unsigned int *)0x20006a08UL = 0x00017819UL;
        *(volatile unsigned int *)(iVar5+8) = 0x400;
        pcVar17 = *(void **)(*(int *)(iVar16 + 8) + 0x1c);
        if (pcVar17 != 0) {
            int r = ((int (*)(int,int,int))pcVar17)(0x00087b48, iVar5, 1);
            if (-1 < r) {
                iVar16 = FUN_00025284();
                if (iVar16 == 0) {
                    uVar15 = 0x5c00000;
                } else {
                    uVar15 = 0x3c00000;
                }
                FUN_00017858(0x000889e0UL, uVar15);
                if (1 < *piVar2) {
                    if (*(volatile int *)0x20007554UL == 0) {
                        DEBUG_PRINT(0x0009a0c6UL, 0x0009a119UL, 10,0,0,0);
                    } else {
                        FUN_00019c70();
                    }
                }
                goto LAB_c40;
            }
        }
        if (*piVar2 < 2) goto LAB_c40;
        iVar16 = *(volatile int *)0x20007554UL;
        uVar15 = 0x00099fa8UL;
        uVar14 = 0x0009a119UL;
    }
    if (iVar16 == 0) {
        DEBUG_PRINT(uVar15, uVar14, 0,0,0,0);
    } else {
        FUN_00019c70();
    }
LAB_c40:
    bVar4 = (unsigned char)FUN_00017980(0x1a);
    uVar7 = FUN_00017980(0x19);
    uVar8 = FUN_00017980(0x1c);
    uVar9 = FUN_00017980(0x1b);
    uVar10 = FUN_000177c4(0x00087b60UL, 0x18);
    uVar11 = FUN_000177c4(0x00087b60UL, 0x13);
    uVar12 = FUN_000177c4(0x00087b60UL, 0x15);
    uVar13 = FUN_000177c4(0x00087b60UL, 0x1e);
    if (1 < *piVar2) {
        uVar18 = bVar4;
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x00099fe8UL, 0x0009a132UL, 0x1a, uVar18,0,0);
        } else {
            FUN_00019c70();
        }
        if (1 < *piVar2) {
            uVar7 = uVar7 & 0xff;
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009a016UL, 0x0009a132UL, 0x19, uVar7,0,0);
            } else {
                FUN_00019c70();
            }
            if (1 < *piVar2) {
                uVar8 = uVar8 & 0xff;
                if (*(volatile int *)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009a044UL, 0x0009a132UL, 0x1c, uVar8,0,0);
                } else {
                    FUN_00019c70();
                }
                if (1 < *piVar2) {
                    uVar9 = uVar9 & 0xff;
                    if (*(volatile int *)0x20007554UL == 0) {
                        DEBUG_PRINT(0x0009a072UL, 0x0009a132UL, 0x1b, uVar9,0,0);
                    } else {
                        FUN_00019c70();
                    }
                    if (1 < *piVar2) {
                        if (*(volatile int *)0x20007554UL == 0) {
                            DEBUG_PRINT(0x0009a0a0UL, 0x0009a132UL, uVar18, uVar7, uVar8, uVar9);
                        } else {
                            FUN_00019c70();
                        }
                        if (1 < *piVar2) {
                            if (*(volatile int *)0x20007554UL == 0) {
                                DEBUG_PRINT(0x0009a0c6UL, 0x0009a132UL, uVar10 & 0xff, uVar11 & 0xff, uVar12 & 0xff, uVar13 & 0xff);
                            } else {
                                FUN_00019c70();
                            }
                        }
                    }
                }
            }
        }
    }
    return bVar4;
}
