#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00025b78 @ 0x00025b78
 * public-name: global_ipc_service_send
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   ipc_service_send                         <= FUN_0004cc50 @ 0x0004cc50
 *   k_sleep                                  <= FUN_00074844 @ 0x00074844
 * address symbols (name @ address):
 *   rodata_9f576                             @ 0x0009f576   [INLINED -- G6 literal batch]
 *   rodata_9f5a9                             @ 0x0009f5a9   [INLINED -- G6 literal batch]
 *   rodata_9f5ce                             @ 0x0009f5ce   [INLINED -- G6 literal batch]
 *   rodata_9f704                             @ 0x0009f704   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ipc_send_fail_cnt                      @ 0x20007a74
 *   g_serialization_ipc_ept                  @ 0x20007a78
 *   g_serialization_ipc_ready                @ 0x20007a80
 */
/* Reconstructed global_ipc_service_send @ 0x25b78  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../headers/g1_log.h"
extern int get_device_info(void);
extern unsigned long sys_reboot(long);
extern int ipc_service_send(uint32_t, uint32_t, uint32_t);
extern void k_sleep(int, int);

int global_ipc_service_send(unsigned int param_1, unsigned int param_2)
{
    volatile int *piVar1;
    volatile int *piVar2;
    int iVar3;
    int iVar4;

    if ((*(volatile int*)((unsigned long)&g_serialization_ipc_ready) /*=0x20007a80*/ == 1)) {
        char *r0 = (char*)get_device_info();
        if (r0[1] != 8) {
            r0 = (char*)get_device_info();
            if (r0[1] != 9) {
                iVar3 = ipc_service_send(((unsigned long)&g_serialization_ipc_ept) /*=0x20007a78*/, param_1, param_2);
                piVar2 = (volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/;
                piVar1 = (volatile int*)((unsigned long)&g_ipc_send_fail_cnt) /*=0x20007a74*/;
                if (iVar3 < 0) {
                    if (0 < *piVar2) {
                        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                            goto lab_debug_1;
                        }
                        debug_print(((unsigned long)"%s(): ipc_service_send data failed with ret %d %d\n") /*=0x9f576*/, ((unsigned long)"global_ipc_service_send") /*=0x9f704*/, iVar3, *piVar1);
                    }
                    while (iVar4 = *piVar1 + 1, *piVar1 = iVar4, 2 < iVar4) {
                        if (0 < *piVar2) {
                            if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                                log_message(((unsigned long)"%s(): sys reboot because ipc failed\n") /*=0x9f5a9*/, ((unsigned long)"global_ipc_service_send") /*=0x9f704*/);
                            } else {
                                debug_print(((unsigned long)"%s(): sys reboot because ipc failed\n") /*=0x9f5a9*/, ((unsigned long)"global_ipc_service_send") /*=0x9f704*/);
                            }
                        }
                        k_sleep(0x4000, 0);
                        sys_reboot(1);
lab_debug_1:
                        log_message(((unsigned long)"%s(): ipc_service_send data failed with ret %d %d\n") /*=0x9f576*/, ((unsigned long)"global_ipc_service_send") /*=0x9f704*/, iVar3);
                    }
                    return iVar3;
                }
                *piVar1 = 0;
                return iVar3;
            }
        }
    }
    if (0 < *(volatile int*)((unsigned long)&g_log_level) /*=0x2000230c*/) {
        if (*(volatile int*)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): ipc_service not ready!\n") /*=0x9f5ce*/, ((unsigned long)"global_ipc_service_send") /*=0x9f704*/);
        } else {
            debug_print(((unsigned long)"%s(): ipc_service not ready!\n") /*=0x9f5ce*/, ((unsigned long)"global_ipc_service_send") /*=0x9f704*/);
        }
    }
    return -1;
}
