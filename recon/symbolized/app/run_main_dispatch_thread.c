#include "g1_app_symbols.h"
/* named: run_main_dispatch_thread */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x20007554  g_log_use_alt_sink           
*/
/* Reconstructed run_main_dispatch_thread @ 0x2a65c  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
extern void DEBUG_PRINT(void);
extern void debug_print(void);
extern void spawn_flash_ops_and_brightness_threads(void);
extern void init_watchdog(void);
extern int is_battery_critical(void);
extern void FUN_00032fe8(void);
extern void FUN_0003304c(void);
extern void spawn_proxy_thread(void);
extern void spawn_display_thread(void);
extern void FUN_0007cb66(void);
extern void kmutex_dlist_init(void);

void run_main_dispatch_thread(char *param_1)
{
    volatile int *dbg = (volatile int*)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    volatile int *flag = (volatile int*)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;
    int iVar1;

    if (2 < *dbg) {
        if (*flag == 0) DEBUG_PRINT();
        else debug_print();
    }
    kmutex_dlist_init();
    spawn_flash_ops_and_brightness_threads();
    init_watchdog();
    iVar1 = is_battery_critical();
    if (iVar1 == 0) {
        FUN_0007cb66();
        FUN_0007cb66();
    } else {
        FUN_0007cb66();
        FUN_00032fe8();
        FUN_0003304c();
    }
    FUN_0007cb66();
    if (*(volatile uint8_t*)param_1 == 1) {
        FUN_0007cb66();
        FUN_0007cb66();
        spawn_proxy_thread();
        spawn_display_thread();
    } else if (*(volatile uint8_t*)param_1 == 2) {
        FUN_0007cb66();
        FUN_0007cb66();
        FUN_0007cb66();
        spawn_display_thread();
    }
    is_battery_critical();
    FUN_0007cb66();
    FUN_0007cb66();
}

