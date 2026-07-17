#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002a65c @ 0x0002a65c
 * public-name: run_main_dispatch_thread
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   spawn_flash_ops_and_brightness_threads   <= FUN_00023a54 @ 0x00023a54
 *   run_main_dispatch_thread                 <= FUN_0002a65c @ 0x0002a65c
 *   init_watchdog                            <= FUN_0002ace0 @ 0x0002ace0
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   spawn_proxy_thread                       <= FUN_00047ad0 @ 0x00047ad0
 *   spawn_display_thread                     <= FUN_00049638 @ 0x00049638
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_state_mutex                         @ 0x20007b3c
 */
/* Reconstructed FUN_0002a65c @ 0x2a65c */
#include <stdint.h>

extern void DEBUG_PRINT(uint32_t, uint32_t);
extern void debug_print(uint32_t, uint32_t);
extern void spawn_flash_ops_and_brightness_threads(void *);
extern void init_watchdog(void);
extern int is_battery_critical(void);
extern void FUN_00032fe8(void);
extern void FUN_0003304c(void);
extern void spawn_proxy_thread(void *);
extern void spawn_display_thread(void *);
extern void FUN_0007cb66(uint32_t, uint32_t, uint32_t, uint32_t,
                         void *, int32_t, uint32_t, uint32_t);
extern void kmutex_dlist_init(uint32_t);

#define CREATE_DISPATCH_THREAD(control, stack, stack_size, entry, context, priority) \
    FUN_0007cb66((control), (stack), (stack_size), (entry), \
                 (context), (priority), 0, 0)

void run_main_dispatch_thread(char *dispatch_mode)
{
    int battery_critical;
    uint32_t final_entry;

    if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            DEBUG_PRINT(0x000a18bfUL, 0x000a1a98UL);
        else
            debug_print(0x000a18bfUL, 0x000a1a98UL);
    }

    kmutex_dlist_init(((unsigned long)&g_ui_state_mutex) /*=0x20007b3c*/);
    spawn_flash_ops_and_brightness_threads(dispatch_mode);
    init_watchdog();

    battery_critical = is_battery_critical();
    if (battery_critical == 0) {
        CREATE_DISPATCH_THREAD(0x200046b8UL, 0x20026a68UL, 0xc00,
                               0x0002a8d9UL, dispatch_mode, -10);
        CREATE_DISPATCH_THREAD(0x200041a8UL, 0x20024868UL, 0x400,
                               0x000286f9UL, dispatch_mode, -10);
    } else {
        CREATE_DISPATCH_THREAD(0x200046b8UL, 0x20026a68UL, 0xc00,
                               0x0002685dUL, dispatch_mode, -10);
        FUN_00032fe8();
        FUN_0003304c();
    }

    CREATE_DISPATCH_THREAD(0x200040d0UL, 0x20023c68UL, 0xc00,
                           0x0002a4f5UL, 0, -9);

    if ((uint8_t)dispatch_mode[0] == 1 || (uint8_t)dispatch_mode[0] == 2) {
        CREATE_DISPATCH_THREAD(0x200045e0UL, 0x20026268UL, 0x800,
                               0x00028bedUL, dispatch_mode, -13);
        CREATE_DISPATCH_THREAD(0x20004508UL, 0x20025a68UL, 0x800,
                               0x0002692dUL, dispatch_mode, -12);
        if ((uint8_t)dispatch_mode[0] == 1) {
            spawn_proxy_thread(dispatch_mode);
        } else {
            CREATE_DISPATCH_THREAD(0x20004430UL, 0x20025468UL, 0x600,
                                   0x00027cfdUL, dispatch_mode, -11);
        }
        spawn_display_thread(dispatch_mode);
    }

    final_entry = is_battery_critical() == 1 ? 0x00028a1dUL : 0x0002a0d9UL;
    CREATE_DISPATCH_THREAD(0x20004358UL, 0x20025068UL, 0x400,
                           final_entry, dispatch_mode, -14);
    CREATE_DISPATCH_THREAD(0x20004280UL, 0x20024c68UL, 0x400,
                           0x0002955dUL, dispatch_mode, -13);
}
