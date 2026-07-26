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
 *   start_aging_mode_thread                  <= FUN_00032fe8 @ 0x00032fe8
 *   spawn_aging_mode_aux_thread              <= FUN_0003304c @ 0x0003304c
 *   spawn_proxy_thread                       <= FUN_00047ad0 @ 0x00047ad0
 *   spawn_display_thread                     <= FUN_00049638 @ 0x00049638
 *   main_dispatch_thread_tick                <= FUN_0007cb66 @ 0x0007cb66
 *   kmutex_dlist_init                        <= FUN_000864c2 @ 0x000864c2
 * address symbols (name @ address):
 *   ADDR_low_speed_peripheral_dispatch_thread_for_test_THUMB @ 0x0002685d
 *   rodata_2692d                             @ 0x0002692d
 *   rodata_27cfd                             @ 0x00027cfd
 *   ADDR_process_task_sync_event_THUMB       @ 0x000286f9
 *   ADDR_click_event_dispatch_loop_THUMB     @ 0x00028a1d
 *   ADDR_display_dispatch_thread_THUMB       @ 0x00028bed
 *   ADDR_key_event_thread_THUMB              @ 0x0002955d
 *   ADDR_touch_key_thread_THUMB              @ 0x0002a0d9
 *   ADDR_transport_dispatch_thread_THUMB     @ 0x0002a4f5
 *   ADDR_FUN_0002a8d8_THUMB                  @ 0x0002a8d9
 *   rodata_a18bf                             @ 0x000a18bf   [INLINED -- G6 literal batch]
 *   rodata_a1a98                             @ 0x000a1a98   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_200040d0                               @ 0x200040d0
 *   g_200041a8                               @ 0x200041a8
 *   g_20004280                               @ 0x20004280
 *   g_20004358                               @ 0x20004358
 *   g_20004430                               @ 0x20004430
 *   g_20004508                               @ 0x20004508
 *   g_200045e0                               @ 0x200045e0
 *   g_200046b8                               @ 0x200046b8
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_ui_state_mutex                         @ 0x20007b3c
 *   g_20023c68                               @ 0x20023c68
 *   g_20024868                               @ 0x20024868
 *   g_20024c68                               @ 0x20024c68
 *   g_20025068                               @ 0x20025068
 *   g_20025468                               @ 0x20025468
 *   g_20025a68                               @ 0x20025a68
 *   g_20026268                               @ 0x20026268
 *   g_20026a68                               @ 0x20026a68
 */
/* Reconstructed FUN_0002a65c @ 0x2a65c */
#include <stdint.h>

extern void log_message(uint32_t, uint32_t);
extern void debug_print(uint32_t, uint32_t);
extern void spawn_flash_ops_and_brightness_threads(void *);
extern void init_watchdog(void);
extern int is_battery_critical(void);
extern void start_aging_mode_thread(void);
extern void spawn_aging_mode_aux_thread(void);
extern void spawn_proxy_thread(void *);
extern void spawn_display_thread(void *);
extern void main_dispatch_thread_tick(uint32_t, uint32_t, uint32_t, uint32_t,
                         void *, int32_t, uint32_t, uint32_t);
extern void kmutex_dlist_init(uint32_t);

#define CREATE_DISPATCH_THREAD(control, stack, stack_size, entry, context, priority) \
    main_dispatch_thread_tick((control), (stack), (stack_size), (entry), \
                 (context), (priority), 0, 0)

void run_main_dispatch_thread(char *dispatch_mode)
{
    int battery_critical;
    uint32_t final_entry;

    if (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 2) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
            log_message(((unsigned long)"%s(): enter.\n") /*=0xa18bf*/, ((unsigned long)"run_main_dispatch_thread") /*=0xa1a98*/);
        else
            debug_print(((unsigned long)"%s(): enter.\n") /*=0xa18bf*/, ((unsigned long)"run_main_dispatch_thread") /*=0xa1a98*/);
    }

    kmutex_dlist_init(((unsigned long)&g_ui_state_mutex) /*=0x20007b3c*/);
    spawn_flash_ops_and_brightness_threads(dispatch_mode);
    init_watchdog();

    battery_critical = is_battery_critical();
    if (battery_critical == 0) {
        CREATE_DISPATCH_THREAD(((unsigned long)&g_200046b8) /*=0x200046b8*/, ((unsigned long)&g_20026a68) /*=0x20026a68*/, 0xc00,
                               ADDR_FUN_0002a8d8_THUMB /*=0x2a8d9*/, dispatch_mode, -10);
        CREATE_DISPATCH_THREAD(((unsigned long)&g_200041a8) /*=0x200041a8*/, ((unsigned long)&g_20024868) /*=0x20024868*/, 0x400,
                               ADDR_process_task_sync_event_THUMB /*=0x286f9*/, dispatch_mode, -10);
    } else {
        CREATE_DISPATCH_THREAD(((unsigned long)&g_200046b8) /*=0x200046b8*/, ((unsigned long)&g_20026a68) /*=0x20026a68*/, 0xc00,
                               ADDR_low_speed_peripheral_dispatch_thread_for_test_THUMB /*=0x2685d*/, dispatch_mode, -10);
        start_aging_mode_thread();
        spawn_aging_mode_aux_thread();
    }

    CREATE_DISPATCH_THREAD(((unsigned long)&g_200040d0) /*=0x200040d0*/, ((unsigned long)&g_20023c68) /*=0x20023c68*/, 0xc00,
                           ADDR_transport_dispatch_thread_THUMB /*=0x2a4f5*/, 0, -9);

    if ((uint8_t)dispatch_mode[0] == 1 || (uint8_t)dispatch_mode[0] == 2) {
        CREATE_DISPATCH_THREAD(((unsigned long)&g_200045e0) /*=0x200045e0*/, ((unsigned long)&g_20026268) /*=0x20026268*/, 0x800,
                               ADDR_display_dispatch_thread_THUMB /*=0x28bed*/, dispatch_mode, -13);
        CREATE_DISPATCH_THREAD(((unsigned long)&g_20004508) /*=0x20004508*/, ((unsigned long)&g_20025a68) /*=0x20025a68*/, 0x800,
                               ((unsigned long)&rodata_2692d) /*=0x2692d*/, dispatch_mode, -12);
        if ((uint8_t)dispatch_mode[0] == 1) {
            spawn_proxy_thread(dispatch_mode);
        } else {
            CREATE_DISPATCH_THREAD(((unsigned long)&g_20004430) /*=0x20004430*/, ((unsigned long)&g_20025468) /*=0x20025468*/, 0x600,
                                   ((unsigned long)&rodata_27cfd) /*=0x27cfd*/, dispatch_mode, -11);
        }
        spawn_display_thread(dispatch_mode);
    }

    final_entry = is_battery_critical() == 1 ? ADDR_click_event_dispatch_loop_THUMB /*=0x28a1d*/ : ADDR_touch_key_thread_THUMB /*=0x2a0d9*/;
    CREATE_DISPATCH_THREAD(((unsigned long)&g_20004358) /*=0x20004358*/, ((unsigned long)&g_20025068) /*=0x20025068*/, 0x400,
                           final_entry, dispatch_mode, -14);
    CREATE_DISPATCH_THREAD(((unsigned long)&g_20004280) /*=0x20004280*/, ((unsigned long)&g_20024c68) /*=0x20024c68*/, 0x400,
                           ADDR_key_event_thread_THUMB /*=0x2955d*/, dispatch_mode, -13);
}
