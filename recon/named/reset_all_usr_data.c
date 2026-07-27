/* readable reconstruction; identity: FUN_0002316c @ 0x0002316c
 * public-name: reset_all_usr_data
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   reset_all_static_info                    <= FUN_00016738 @ 0x00016738
 *   enable_ship_mode                         <= FUN_000167f4 @ 0x000167f4
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   reset_usr_setting                        <= FUN_00022ddc @ 0x00022ddc
 *   flash_erase_settings_record              <= FUN_000230bc @ 0x000230bc
 *   reset_all_usr_data                       <= FUN_0002316c @ 0x0002316c
 *   cleanAppLanguageInfo                     <= FUN_00023b78 @ 0x00023b78
 *   cleanDashBoardStartUpModeInfo            <= FUN_00023c88 @ 0x00023c88
 *   deleteQuickNoteData                      <= FUN_000244a8 @ 0x000244a8
 *   delAudioStreamRecord                     <= FUN_0002f878 @ 0x0002f878
 *   reset_touch_selection_state              <= FUN_00037098 @ 0x00037098
 *   sys_reboot                               <= FUN_0004c0a8 @ 0x0004c0a8
 *   bt_unpair_all_or_addr                    <= FUN_0005420c @ 0x0005420c
 *   app_msleep_thunk_b                       <= FUN_0007c26e @ 0x0007c26e
 * address symbols (name @ address):
 *   rodata_9e6d7                             @ 0x0009e6d7   [INLINED -- G6 literal batch]
 *   rodata_9e764                             @ 0x0009e764   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed reset_all_usr_data @ 0x2316c. */
#include <stdint.h>
#include "../headers/g1_log.h"

extern void reset_touch_selection_state(void);
extern void delAudioStreamRecord(uint32_t);
extern void app_msleep_thunk_b(int);
extern void deleteQuickNoteData(uint32_t);
extern void cleanAppLanguageInfo(void);
extern void cleanDashBoardStartUpModeInfo(void);
extern void reset_usr_setting(void *);
extern void flash_erase_settings_record(void *);
extern void reset_all_static_info(void);
extern void bt_unpair_all_or_addr(uint32_t, uint32_t);
extern void enable_ship_mode(uint32_t);
extern uint32_t sys_reboot(uint32_t);

#define LOG_LEVEL (*(volatile int32_t *)0x2000230c)
#define LOG_BACKEND (*(volatile uint32_t *)0x20007554)

void reset_all_usr_data(uint8_t *user_data, int reset_radio)
{
    reset_touch_selection_state();
    if (user_data[0] == 1) {
        delAudioStreamRecord(0xff);
        app_msleep_thunk_b(1000);
    }

    for (uint32_t slot = 0; slot != 4; ++slot) {
        deleteQuickNoteData(slot);
        app_msleep_thunk_b(200);
    }
    cleanAppLanguageInfo();
    app_msleep_thunk_b(200);
    cleanDashBoardStartUpModeInfo();
    app_msleep_thunk_b(200);
    reset_usr_setting(user_data);
    flash_erase_settings_record(user_data);
    app_msleep_thunk_b(500);
    reset_all_static_info();
    app_msleep_thunk_b(500);
    bt_unpair_all_or_addr(0, 0);

    if (!reset_radio)
        return;

    app_msleep_thunk_b(1000);
    enable_ship_mode(1);
    app_msleep_thunk_b(1000);
    if (LOG_LEVEL > 0) {
        if (LOG_BACKEND == 0)
            log_message(((unsigned long)"%s(): sys reboot because enter ship mode failed\n"), ((unsigned long)"reset_all_usr_data"));
        else
            debug_print(((unsigned long)"%s(): sys reboot because enter ship mode failed\n"), ((unsigned long)"reset_all_usr_data"));
    }
    for (;;) {
        app_msleep_thunk_b(500);
        log_message(sys_reboot(1));
    }
}
