/* Reconstructed FUN_00021a40 @ 0x21a40  (parity: 252/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void FUN_00019c70(void);
extern void FUN_0004a424(void);
extern void FUN_00086c1e(void);
extern void FUN_00086c78(void);

unsigned FUN_00021a40(int param_1, int param_2, unsigned char param_3, void *param_4)
{
    volatile int *piVar1 = (volatile int*)0x2000230c;
    volatile int *flag = (volatile int*)0x20007554;
    volatile int local_3c[16];
    int uVar9 = param_2 / 0x11;
    int iVar8 = uVar9 + 1;
    int iVar10 = param_2 % 0x11;
    int iVar11, iVar13, iVar12;
    int iVar10b;

    FUN_00086c78();

    if (2 < *piVar1) {
        if (*flag == 0) DEBUG_PRINT();
        else FUN_00019c70();
    }
    iVar13 = 0;
    while (1) {
        iVar11 = *piVar1;
        iVar12 = iVar13 + 1;
        if (uVar9 <= iVar13) break;
        {
            volatile int *puVar6 = (volatile int*)(iVar13 * 0x11 + param_1);
            volatile int *puVar2 = &local_3c[1];
            volatile int *puVar7, *puVar3;
            do {
                puVar7 = puVar6 + 1;
                puVar3 = puVar2 + 1;
                *puVar2 = *puVar6;
                puVar2 = puVar3;
                puVar6 = puVar7;
            } while (puVar7 != (volatile int*)(iVar13 * 0x11 + param_1) + 4);
            *(volatile uint8_t*)puVar3 = *(volatile uint8_t*)puVar7;
        }
        if (2 < iVar11) {
            if (*flag == 0) DEBUG_PRINT();
            else FUN_00019c70();
        }
        FUN_0004a424();
        ((void(*)(void*))(intptr_t)param_4)((void*)local_3c);
        iVar13 = iVar12;
    }
    (void)iVar8; (void)iVar12;

    if (iVar10 == 0) {
        FUN_00086c78();
        if (iVar11 < 3) goto LAB_b5a;
        iVar10b = *flag;
    } else {
        FUN_00086c78();
        FUN_00086c1e();
        if (iVar11 < 3) goto LAB_b5a;
        iVar10b = *flag;
    }
    if (iVar10b == 0) DEBUG_PRINT();
    else FUN_00019c70();
LAB_b5a:
    FUN_0004a424();
    if (2 < *piVar1) {
        if (*flag == 0) DEBUG_PRINT();
        else FUN_00019c70();
    }
    ((void(*)(void*))(intptr_t)param_4)((void*)local_3c);
    return 0;
}

