#include "g1_app_symbols.h"
/* named: ui_onboarding_task */
/* globals referenced:
//   0x2000230c  g_log_level                  
//   0x200034f5  onboarding_last_step_cache   
//   0x20007554  g_log_use_alt_sink           
//   0x2001cdce  onboarding_secondary_reset_flag 
*/
/* Reconstructed ui_onboarding_task @ 0x42d44  (parity: 300/300 trials, PROVEN) */
#include <stdint.h>
typedef unsigned int uint;
typedef unsigned undefined4;
typedef unsigned char byte;
typedef unsigned char undefined1;
extern void DEBUG_PRINT(unsigned, ...);
extern int get_device_info(void);
extern void debug_print(unsigned, ...);
extern void onboarding_retry_watchdog_update(void);
extern void FUN_00040794(int a);
extern void FUN_000417f8(int a);
extern void FUN_000429f8(void);
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
    volatile int *verbose = (volatile int *)((uintptr_t)&g_log_level) /*=0x2000230c*/;
    volatile int *dbg = (volatile int *)((uintptr_t)&g_log_use_alt_sink) /*=0x20007554*/;

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
            (iVar4 = get_device_info(), pbVar3 = (byte *)((uintptr_t)&g_onboarding_step_retry_cnt) /*=0x20004bf0*/,
             *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 2) != '\0')) {
            uVar7 = k_uptime_get_8();
            uVar7 = u64_sub((int)uVar7, (int)(uVar7 >> 0x20), *(volatile unsigned *)(pbVar3 + 8), *(volatile unsigned *)(pbVar3 + 0xc));
            if ((int)(unsigned)((unsigned)uVar7 < 0x3e9) <= (int)(uVar7 >> 0x20)) {
                *pbVar3 = *pbVar3 + 1;
                uVar7 = k_uptime_get_8();
                *(volatile unsigned long long *)(pbVar3 + 8) = uVar7;
                if (0x13 < *pbVar3) {
                    if (1 < *verbose) {
                        if (*dbg == 0) DEBUG_PRINT(0, 0);
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
        if (((uint)*(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2) == (int)*(volatile char *)((uintptr_t)&onboarding_last_step_cache) /*=0x200034f5*/) &&
            (iVar4 = get_device_info(), *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 3) == *(volatile char *)((uintptr_t)&onboarding_secondary_reset_flag) /*=0x2001cdce*/)) {
            FUN_00040794(param_3);
            FUN_000417f8(param_3);
            return 0;
        }
        pcVar5 = (char *)get_device_info();
        if (*pcVar5 == '\x01') {
            FUN_000429f8();
            iVar4 = get_device_info();
            *(volatile char *)((uintptr_t)&onboarding_secondary_reset_flag) /*=0x2001cdce*/ = *(volatile char *)(*(volatile int *)(iVar4 + 0x1014) + 3);
            iVar4 = get_device_info();
            local_14[0] = *(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 2);
            local_14[1] = *(volatile char *)((uintptr_t)&onboarding_secondary_reset_flag) /*=0x2001cdce*/;
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
                        DEBUG_PRINT(0, 0, (uint)bVar2, (uint)*(volatile byte *)(*(volatile int *)(iVar4 + 0x1014) + 3));
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

