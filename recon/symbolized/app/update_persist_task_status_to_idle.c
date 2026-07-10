#include "g1_app_symbols.h"
/* named: update_persist_task_status_to_idle */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed update_persist_task_status_to_idle @ 0x2c0e8  (parity: 300/300 trials, PROVEN) */

typedef unsigned char u8;
extern void DEBUG_PRINT(unsigned int, unsigned int, ...);
extern void debug_print(unsigned int, unsigned int, unsigned int);
extern void display_close_screen(unsigned int);
extern void FUN_0007cdf8(void);

int update_persist_task_status_to_idle(int param_1)
{
    volatile u8 *lock = (volatile u8*)((uintptr_t)&g_persist_task_status_lock) /*=0x20018d9c*/;
    while (*lock != 0) {
        FUN_0007cdf8();
    }
    *lock = 1;
    if ((*(char*)(param_1+0xd5) != 0) || (*(char*)(*(int*)(param_1+0x1054)+4) != 1)) {
        if ((*(char*)(param_1+0xd5) != 0) && (*(char*)(param_1+0xd5) != 1)) {
            display_close_screen(*(u8*)(param_1+0xd5));
        }
        if (*(char*)(param_1+0xd5) == 0x10) {
            *(u8*)(param_1+0xf98) = *(volatile u8*)((uintptr_t)&g_persist_task_status) /*=0x20018d9d*/;
        }
        if (*(volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/ > 0) {
            if (*(volatile unsigned int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                DEBUG_PRINT("%s(): persist task [stop]: %d\n" /*=0xa25d9*/, "update_persist_task_status_to_idle" /*=0xa2625*/);
            } else {
                debug_print("%s(): persist task [stop]: %d\n" /*=0xa25d9*/, "update_persist_task_status_to_idle" /*=0xa2625*/, 0);
            }
        }
        *(u8*)(param_1+0xd5) = 0;
        *(u8*)(*(int*)(param_1+0x1054)+4) = 1;
    }
    *lock = 0;
    return 0;
}

