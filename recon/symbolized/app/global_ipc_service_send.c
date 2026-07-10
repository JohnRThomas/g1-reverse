#include "g1_app_symbols.h"
/* named: global_ipc_service_send */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed global_ipc_service_send @ 0x25b78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern int sys_reboot(int);
extern int ipc_service_send(uint32_t, uint32_t, uint32_t);
extern void FUN_00074844(int, int);

int global_ipc_service_send(unsigned int param_1, unsigned int param_2)
{
    volatile int *piVar1;
    volatile int *piVar2;
    int iVar3;
    int iVar4;

    if ((*(volatile int*)((uintptr_t)&g_serialization_ipc_ready) /*=0x20007a80*/ == 1)) {
        char *r0 = (char*)get_device_info();
        if (r0[1] != 8) {
            r0 = (char*)get_device_info();
            if (r0[1] != 9) {
                iVar3 = ipc_service_send(((uintptr_t)&g_serialization_ipc_ept) /*=0x20007a78*/, param_1, param_2);
                piVar2 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
                piVar1 = (volatile int*)((uintptr_t)&g_ipc_send_fail_cnt) /*=0x20007a74*/;
                if (iVar3 < 0) {
                    if (0 < *piVar2) {
                        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            goto lab_debug_1;
                        }
                        debug_print("%s(): ipc_service_send data failed with ret %d %d\n" /*=0x9f576*/, "global_ipc_service_send" /*=0x9f704*/, iVar3, *piVar1);
                    }
                    while (iVar4 = *piVar1 + 1, *piVar1 = iVar4, 2 < iVar4) {
                        if (0 < *piVar2) {
                            if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                DEBUG_PRINT("%s(): sys reboot because ipc failed\n" /*=0x9f5a9*/, "global_ipc_service_send" /*=0x9f704*/);
                            } else {
                                debug_print("%s(): sys reboot because ipc failed\n" /*=0x9f5a9*/, "global_ipc_service_send" /*=0x9f704*/);
                            }
                        }
                        FUN_00074844(0x4000, 0);
                        sys_reboot(1);
lab_debug_1:
                        DEBUG_PRINT("%s(): ipc_service_send data failed with ret %d %d\n" /*=0x9f576*/, "global_ipc_service_send" /*=0x9f704*/, iVar3);
                    }
                    return iVar3;
                }
                *piVar1 = 0;
                return iVar3;
            }
        }
    }
    if (0 < *(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): ipc_service not ready!\n" /*=0x9f5ce*/, "global_ipc_service_send" /*=0x9f704*/);
        } else {
            debug_print("%s(): ipc_service not ready!\n" /*=0x9f5ce*/, "global_ipc_service_send" /*=0x9f704*/);
        }
    }
    return -1;
}

