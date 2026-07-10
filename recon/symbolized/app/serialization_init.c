#include "g1_app_symbols.h"
/* named: serialization_init */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed serialization_init @ 0x25c54  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(uint32_t, ...);
extern void debug_print(uint32_t, ...);
extern int ipc_service_open_instance(uint32_t);
extern unsigned long long FUN_0004cbec(uint32_t, uint32_t, uint32_t);
extern void mutex_lock_syscall_handler(uint32_t, int, int, int);

unsigned int serialization_init(void)
{
    volatile int *piVar1 = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    int iVar2;
    unsigned int format_string;
    unsigned long long uVar3;

    if (2 < *piVar1) {
        if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            DEBUG_PRINT("%s(): IPC-service HOST init started\n" /*=0x9f5ec*/, "serialization_init" /*=0x9f6f1*/);
        } else {
            debug_print("%s(): IPC-service HOST init started\n" /*=0x9f5ec*/, "serialization_init" /*=0x9f6f1*/);
        }
    }
    iVar2 = ipc_service_open_instance(((uintptr_t)&tbl_87b30) /*=0x87c08*/);
    if ((iVar2 < 0) && (iVar2 != -0x78)) {
        if (*piVar1 < 1) {
            return 0xffffffffUL;
        }
        iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        format_string = "%s(): ipc_service_open_instance() failure\n" /*=0x9f611*/;
    } else {
        if (2 < *piVar1) {
            if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): ipc open %d\n" /*=0x9f63c*/, "serialization_init" /*=0x9f6f1*/);
            } else {
                debug_print("%s(): ipc open %d\n" /*=0x9f63c*/, "serialization_init" /*=0x9f6f1*/);
            }
        }
        uVar3 = FUN_0004cbec(((uintptr_t)&tbl_87b30) /*=0x87c08*/, ((uintptr_t)&g_serialization_ipc_ept) /*=0x20007a78*/, ((uintptr_t)&g_serialization_ipc_ept_ctx) /*=0x200023dc*/);
        if (-1 < (int)uVar3) {
            mutex_lock_syscall_handler(((uintptr_t)&g_serialization_ipc_mutex) /*=0x200039c8*/, (int)(uVar3 >> 32), -1, -1);
            *(volatile int*)((uintptr_t)&g_serialization_ipc_ready) /*=0x20007a80*/ = 1;
            if (1 < *piVar1) {
                if (*(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                    DEBUG_PRINT("%s(): ipc_service[HOST] has ready!\n\n" /*=0x9f67e*/, "serialization_init" /*=0x9f6f1*/);
                } else {
                    debug_print("%s(): ipc_service[HOST] has ready!\n\n" /*=0x9f67e*/, "serialization_init" /*=0x9f6f1*/);
                }
            }
            return 0;
        }
        if (*piVar1 < 1) {
            return 0xffffffffUL;
        }
        iVar2 = *(volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
        format_string = "%s(): ipc_service_register_endpoint() failure\n" /*=0x9f64f*/;
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, "serialization_init" /*=0x9f6f1*/);
    } else {
        debug_print(format_string, "serialization_init" /*=0x9f6f1*/);
    }
    return 0xffffffffUL;
}

