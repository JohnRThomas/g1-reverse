#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00042d44 @ 0x00042d44
 * public-name: ui_onboarding_task
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   onboarding_retry_watchdog_update         <= FUN_00040708 @ 0x00040708
 *   onboarding_render_step_screen            <= FUN_00040794 @ 0x00040794
 *   render_onboarding_screen                 <= FUN_000417f8 @ 0x000417f8
 *   onboarding_mark_retry_if_reset           <= FUN_000429f8 @ 0x000429f8
 *   onboarding_sync_data                     <= FUN_00042c8c @ 0x00042c8c
 *   ui_onboarding_task                       <= FUN_00042d44 @ 0x00042d44
 *   gui_set_active_canvas                    <= FUN_000431b4 @ 0x000431b4
 *   gui_screen_clear                         <= FUN_000431c0 @ 0x000431c0
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 *   send_response_data_to_ble                <= FUN_00047ba8 @ 0x00047ba8
 *   k_uptime_get_8                           <= FUN_0007d382 @ 0x0007d382
 *   u64_sub                                  <= FUN_0007d3c2 @ 0x0007d3c2
 * address symbols (name @ address):
 *   g_log_level                              @ 0x2000230c
 *   onboarding_last_step_cache               @ 0x200034f5
 *   g_onboarding_step_retry_cnt              @ 0x20004bf0
 *   g_log_use_alt_sink                       @ 0x20007554
 *   onboarding_secondary_reset_flag          @ 0x2001cdce
 */
/* Reconstructed FUN_00042d44 @ 0x42d44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
#include "../../../headers/g1_log.h"
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char byte;
typedef unsigned char undefined1;
extern int get_device_info(void);
extern void onboarding_retry_watchdog_update(void);
extern void onboarding_render_step_screen(int a);
extern void render_onboarding_screen(int a);
extern void onboarding_mark_retry_if_reset(void);
extern int onboarding_sync_data(void *a, int b);
extern void gui_set_active_canvas(int a);
extern void gui_screen_clear(void);
extern void gui_canvas_flags_set_bit1(void);
extern void send_response_data_to_ble(void);
extern unsigned long long k_uptime_get_8(void);
extern unsigned long long u64_sub(int a, int b, unsigned c, unsigned d);
extern void thunk_FUN_00043308(void);

undefined4 ui_onboarding_task(int param_1, undefined4 param_2, int param_3)
{
    byte bVar2;
    byte *pbVar3;
    int iVar4, iVar6;
    char *pcVar5;
    unsigned long long uVar7;
    unsigned char local_14[2], local_12, uStack_11;
    volatile int *verbose = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *dbg = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;

    (void)local_12; (void)uStack_11; (void)param_2;
    local_14[0] = 0;
    iVar4 = get_device_info();
    gui_set_active_canvas(param_1 + 0x24);
    gui_canvas_flags_set_bit1();
    if ((param_3 == 2) || (0x17 < *(volatile byte *)(iVar4 + 0xf1))) {
        iVar4 = get_device_info();
        **(volatile undefined1 **)(iVar4 + 0x1014) = 0;
        iVar4 = get_device_info();
        iVar6 = *(volatile int *)(iVar4 + 0x1014);
        iVar4 = get_device_info();
        *(volatile undefined1 *)(iVar4 + 0xed5) = *(volatile undefined1 *)(iVar6 + 0x20);
        gui_screen_clear();
    } else {
        if ((param_3 == 1) && (pcVar5 = (char *)get_device_info(), *pcVar5 == '\x01')) {
            send_response_data_to_ble();
        }
        pcVar5 = (char *)get_device_info();
        if ((*pcVar5 == '\x01') &&
            (iVar4 = get_device_info(), pbVar3 = (byte *)((unsigned long)&g_onboarding_step_retry_cnt) /*=0x20004bf0*/,
             *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 2) != '\0')) {
            uVar7 = k_uptime_get_8();
            uVar7 = u64_sub((int)uVar7, (int)(uVar7 >> 0x20), *(volatile unsigned *)(pbVar3 + 8), *(volatile unsigned *)(pbVar3 + 0xc));
            if ((int)(unsigned)((unsigned)uVar7 < 0x3e9) <= (int)(uVar7 >> 0x20)) {
                *pbVar3 = *pbVar3 + 1;
                uVar7 = k_uptime_get_8();
                *(volatile unsigned long long *)(pbVar3 + 8) = uVar7;
                if (0x13 < *pbVar3) {
                    if (1 < *verbose) {
                        if (*dbg == 0) log_message(0, 0);
                        else debug_print(0);
                    }
                    *pbVar3 = 0x14;
                    iVar4 = get_device_info();
                    *(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 2) = 0xb;
                    iVar4 = get_device_info();
                    local_14[0] = *(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2);
                    iVar4 = onboarding_sync_data(local_14, 3);
                    if (iVar4 != 0) return 0;
                    iVar4 = get_device_info();
                    **(volatile undefined1 **)(iVar4 + 0x1014) = 0;
                    iVar4 = get_device_info();
                    *(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 1) = 0;
                    return 0;
                }
            }
        }
        iVar4 = get_device_info();
        if (((uint)*(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2) == (int)*(volatile char *)((unsigned long)&onboarding_last_step_cache) /*=0x200034f5*/) &&
            (iVar4 = get_device_info(), *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 3) == *(volatile char *)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/)) {
            onboarding_render_step_screen(param_3);
            render_onboarding_screen(param_3);
            return 0;
        }
        pcVar5 = (char *)get_device_info();
        if (*pcVar5 == '\x01') {
            onboarding_mark_retry_if_reset();
            iVar4 = get_device_info();
            *(volatile char *)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/ = *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 3);
            iVar4 = get_device_info();
            local_14[0] = *(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2);
            local_14[1] = *(volatile char *)((unsigned long)&onboarding_secondary_reset_flag) /*=0x2001cdce*/;
            iVar4 = get_device_info();
            local_12 = *(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 0xc);
            iVar4 = get_device_info();
            if ((*(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 2) != '\n') &&
                (iVar4 = get_device_info(), *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 2) != '\v')) {
                if (2 < *verbose) {
                    if (*dbg == 0) {
                        iVar4 = get_device_info();
                        bVar2 = *(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2);
                        iVar4 = get_device_info();
                        log_message(0, 0, (uint)bVar2, (uint)*(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 3));
                    } else {
                        iVar4 = get_device_info();
                        (void)*(volatile undefined1 *)(*(volatile int *)(iVar4 + 0x1014) + 2);
                        iVar4 = get_device_info();
                        debug_print(0);
                    }
                }
                onboarding_sync_data(local_14, 3);
            }
            thunk_FUN_00043308();
            onboarding_retry_watchdog_update();
            uVar7 = k_uptime_get_8();
            iVar4 = get_device_info();
            *(volatile unsigned long long *)(*(volatile int *)(iVar4 + 0x1014) + 4) = uVar7;
            iVar4 = get_device_info();
            iVar6 = *(volatile int *)(iVar4 + 0x1014);
            iVar4 = get_device_info();
            *(volatile undefined1 *)(iVar4 + 0xcd) = *(volatile undefined1 *)(iVar6 + 3);
        }
    }
    return 0;
}
