/* Reconstructed register_ipc_service_recv_callback @ 0x25ae8  (CFG-directed candidate) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void FUN_00019c70(uint32_t, ...);

int register_ipc_service_recv_callback(unsigned int param_1)
{
    int *piVar1;
    int iVar2;
    int iVar3;

    piVar1 = *(int * volatile *)0x20007a84UL;
    iVar2 = *(volatile int *)0x2000230cUL;
    iVar3 = piVar1[1];
    if (iVar3 < 0x16) {
        piVar1[iVar3 + 2] = (int)param_1;
        piVar1[1] = iVar3 + 1;
        if (2 < iVar2) {
            if (*(volatile int *)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009f512UL, 0x0009f6a3UL,
                            *(volatile unsigned char *)param_1,
                            *(volatile int *)(param_1 + 4), iVar3 + 1);
            } else {
                FUN_00019c70(0x0009f512UL, 0x0009f6a3UL,
                             *(volatile unsigned char *)param_1,
                             *(volatile int *)(param_1 + 4), iVar3 + 1);
            }
        }
        return 0;
    }
    if (0 < iVar2) {
        if (*(volatile int *)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009f540UL, 0x0009f6a3UL,
                        *(volatile unsigned char *)param_1,
                        *(volatile int *)(param_1 + 4), iVar3, 0x16);
        } else {
            FUN_00019c70(0x0009f540UL, 0x0009f6a3UL,
                         *(volatile unsigned char *)param_1,
                         *(volatile int *)(param_1 + 4), iVar3, 0x16);
        }
    }
    return -1;
}
