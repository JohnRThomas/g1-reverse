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
    volatile int *piVar1 = (volatile int*)0x2000230cUL;
    int iVar2;
    unsigned int format_string;
    unsigned long long uVar3;

    if (2 < *piVar1) {
        if (*(volatile int*)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009f5ecUL, 0x0009f6f1UL);
        } else {
            debug_print(0x0009f5ecUL, 0x0009f6f1UL);
        }
    }
    iVar2 = ipc_service_open_instance(0x00087c08UL);
    if ((iVar2 < 0) && (iVar2 != -0x78)) {
        if (*piVar1 < 1) {
            return 0xffffffffUL;
        }
        iVar2 = *(volatile int*)0x20007554UL;
        format_string = 0x0009f611UL;
    } else {
        if (2 < *piVar1) {
            if (*(volatile int*)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009f63cUL, 0x0009f6f1UL);
            } else {
                debug_print(0x0009f63cUL, 0x0009f6f1UL);
            }
        }
        uVar3 = FUN_0004cbec(0x00087c08UL, 0x20007a78UL, 0x200023dcUL);
        if (-1 < (int)uVar3) {
            mutex_lock_syscall_handler(0x200039c8UL, (int)(uVar3 >> 32), -1, -1);
            *(volatile int*)0x20007a80UL = 1;
            if (1 < *piVar1) {
                if (*(volatile int*)0x20007554UL == 0) {
                    DEBUG_PRINT(0x0009f67eUL, 0x0009f6f1UL);
                } else {
                    debug_print(0x0009f67eUL, 0x0009f6f1UL);
                }
            }
            return 0;
        }
        if (*piVar1 < 1) {
            return 0xffffffffUL;
        }
        iVar2 = *(volatile int*)0x20007554UL;
        format_string = 0x0009f64fUL;
    }
    if (iVar2 == 0) {
        DEBUG_PRINT(format_string, 0x0009f6f1UL);
    } else {
        debug_print(format_string, 0x0009f6f1UL);
    }
    return 0xffffffffUL;
}

