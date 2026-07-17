/* readable reconstruction; identity: FUN_00025b78 @ 0x00025b78
 * public-name: global_ipc_service_send
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 * address symbols (name @ address):
 *   rodata_9f576                             @ 0x0009f576
 *   rodata_9f5a9                             @ 0x0009f5a9
 *   rodata_9f5ce                             @ 0x0009f5ce
 *   rodata_9f704                             @ 0x0009f704
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ipc_send_fail_cnt                      @ 0x20007a74
 *   g_serialization_ipc_ept                  @ 0x20007a78
 *   g_serialization_ipc_ready                @ 0x20007a80
 */
/* Reconstructed global_ipc_service_send @ 0x25b78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void *get_device_info(void);
extern void debug_print(uint32_t, ...);
extern int sys_reboot(int);
extern int FUN_0004cc50(uint32_t, uint32_t, uint32_t);
extern void FUN_00074844(int, int);

int global_ipc_service_send(unsigned int param_1, unsigned int param_2)
{
    volatile int *piVar1;
    volatile int *piVar2;
    int iVar3;
    int iVar4;

    if ((*(volatile int*)0x20007a80UL == 1)) {
        char *r0 = (char*)get_device_info();
        if (r0[1] != 8) {
            r0 = (char*)get_device_info();
            if (r0[1] != 9) {
                iVar3 = FUN_0004cc50(0x20007a78UL, param_1, param_2);
                piVar2 = (volatile int*)0x2000230cUL;
                piVar1 = (volatile int*)0x20007a74UL;
                if (iVar3 < 0) {
                    if (0 < *piVar2) {
                        if (*(volatile int*)0x20007554UL == 0) {
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
