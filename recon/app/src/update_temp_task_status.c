/* Reconstructed update_temp_task_status @ 0x2bffc  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_00049858(unsigned char);
extern void FUN_0007cdf8(void);

unsigned int update_temp_task_status(int param_1, unsigned int param_2, unsigned int param_3)
{
    volatile char *pcVar1 = (volatile char*)0x20018d9cUL;
    uint32_t format_string;
    unsigned int uVar2;
    unsigned char *puVar3;
    int iVar4;

    while (*pcVar1 != 0) {
        FUN_0007cdf8();
    }
    *pcVar1 = 1;

    if (((**(unsigned int**)(intptr_t)(param_1 + 0x1054) == param_2) &&
         ((uVar2 = (unsigned int)(unsigned char)((*(unsigned int**)(intptr_t)(param_1 + 0x1054))[1]),
           uVar2 == 1 || (uVar2 == param_3)))) ||
        (*(unsigned char*)(intptr_t)(param_1 + 0xd5) == param_2)) {
        goto LAB_0002c076;
    }

    if ((*(char*)(intptr_t)(param_1 + 0xd5) == 0) || (*(char*)(intptr_t)(param_1 + 0xd5) == 1)) {
        if (param_3 != 2) goto LAB_0002c08a;
LAB_0002c052:
        if (0 < *(volatile int*)0x2000230cUL) {
            iVar4 = *(volatile int*)0x20007554UL;
            format_string = 0x000a2597UL;
LAB_0002c0ac:
            if (iVar4 == 0) {
                DEBUG_PRINT(format_string, 0x000a2648UL, param_2);
            } else {
                FUN_00019c70(format_string, 0x000a2648UL, param_2);
            }
        }
    } else {
        FUN_00049858(*(unsigned char*)(intptr_t)(param_1 + 0xd5));
        if (param_3 == 2) {
            if ((param_2 & 0xfffffffdUL) != 4) goto LAB_0002c076;
            goto LAB_0002c052;
        }
LAB_0002c08a:
        if (param_3 == 3) {
            if (*(volatile int*)0x2000230cUL < 1) goto LAB_0002c05a;
            iVar4 = *(volatile int*)0x20007554UL;
            format_string = 0x000a25b9UL;
            goto LAB_0002c0ac;
        }
        if (0 < *(volatile int*)0x2000230cUL) {
            iVar4 = *(volatile int*)0x20007554UL;
            format_string = 0x000a25d9UL;
            goto LAB_0002c0ac;
        }
    }
LAB_0002c05a:
    *(unsigned char*)(intptr_t)(param_1 + 0xd5) = (unsigned char)param_2;
    puVar3 = *(unsigned char**)(intptr_t)(param_1 + 0x1054);
    *puVar3 = 0;
    puVar3[1] = 0;
    puVar3[2] = 0;
    puVar3[3] = 0;
    *(unsigned char*)(intptr_t)(*(int*)(intptr_t)(param_1 + 0x1054) + 4) = 1;
LAB_0002c076:
    *pcVar1 = 0;
    return param_3;
}

