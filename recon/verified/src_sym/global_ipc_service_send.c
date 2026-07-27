/* Reconstructed global_ipc_service_send @ 0x25b78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(unsigned long, ...);
extern void *get_device_info(void);
extern void debug_print(unsigned long, ...);
extern int sys_reboot(int);
extern int ipc_service_send(uint32_t, uint32_t, uint32_t);
extern void FUN_00074844(int, int);

int global_ipc_service_send(unsigned int param_1, unsigned int param_2)
{
    volatile int *piVar1;
    volatile int *piVar2;
    int iVar3;
    int iVar4;

    if ((*(volatile int*)0x20007a80UL /* device_info+0x1084 (IPC service enabled flag) */ == 1)) {
        char *r0 = (char*)get_device_info();
        if (r0[1] != 8) {
            r0 = (char*)get_device_info();
            if (r0[1] != 9) {
                iVar3 = ipc_service_send(0x20007a78UL /* device_info+0x107C (IPC service endpoint object) */, param_1, param_2);
                piVar2 = (volatile int*)0x2000230cUL /* g_log_verbosity_level (debug print threshold) */;
                piVar1 = (volatile int*)0x20007a74UL /* device_info+0x1078 (IPC send retry counter) */;
                if (iVar3 < 0) {
                    if (0 < *piVar2) {
                        if (*(volatile int*)0x20007554UL /* device_info.is_debug @+0xB58  (log sink select: 0=RTT DEBUG_PRINT) */ == 0) {
                            goto lab_debug_1;
                        }
                        debug_print(0x0009f576UL, 0x0009f704UL, iVar3, *piVar1);
                    }
                    while (iVar4 = *piVar1 + 1, *piVar1 = iVar4, 2 < iVar4) {
                        if (0 < *piVar2) {
                            if (*(volatile int*)0x20007554UL == 0) {
                                DEBUG_PRINT(0x0009f5a9UL, 0x0009f704UL);
                            } else {
                                debug_print(0x0009f5a9UL, 0x0009f704UL);
                            }
                        }
                        FUN_00074844(0x4000, 0);
                        sys_reboot(1);
lab_debug_1:
                        DEBUG_PRINT(0x0009f576UL, 0x0009f704UL, iVar3);
                    }
                    return iVar3;
                }
                *piVar1 = 0;
                return iVar3;
            }
        }
    }
    if (0 < *(volatile int*)0x2000230cUL) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009f5ceUL, 0x0009f704UL);
        } else {
            debug_print(0x0009f5ceUL, 0x0009f704UL);
        }
    }
    return -1;
}

