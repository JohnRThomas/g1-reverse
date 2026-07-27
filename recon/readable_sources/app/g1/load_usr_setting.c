#include "g1_app_symbols.h"
/* Recovered layout bindings (presentation-only; Ghidra-grounded):
 *   param_1          => struct g1_layout_g1_device_runtime_state__param_0027    [param_0027; G1-original]
 * Raw function identity: 0x00022e78.  See ../include/g1_recovered_layouts.h. */
/* readable reconstruction; identity: FUN_00022e78 @ 0x00022e78
 * public-name: load_usr_setting
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_settings_read                      <= FUN_000225b4 @ 0x000225b4
 *   reset_usr_setting                        <= FUN_00022ddc @ 0x00022ddc
 *   is_battery_critical                      <= FUN_00032ee4 @ 0x00032ee4
 *   set_test_mode                            <= FUN_00032ef0 @ 0x00032ef0
 *   save_usr_setting                         <= FUN_0007c28e @ 0x0007c28e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9e60c                             @ 0x0009e60c   [INLINED -- G6 literal batch]
 *   rodata_9e632                             @ 0x0009e632   [INLINED -- G6 literal batch]
 *   rodata_9e7a6                             @ 0x0009e7a6   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed load_usr_setting @ 0x22e78 */

#include <stdint.h>
#include "../../../headers/g1_log.h"

struct __attribute__((packed)) user_settings_record {
    uint8_t display_mode;
    uint8_t language;
    uint8_t secondary_language;
    uint8_t interaction_mode;
    uint32_t timeout;
    uint8_t brightness;
    uint8_t gesture_mode;
    uint8_t auxiliary_mode;
    uint8_t primary_index;
    uint32_t identifier;
    uint16_t interval;
    uint8_t identifier_tail;
    uint8_t language_extension;
    uint8_t boolean_mode;
    uint8_t option_a;
    uint8_t option_b;
    uint8_t critical_mode;
    uint8_t secondary_index;
    uint8_t reserved[3];
    uint32_t counter;
};

extern int flash_settings_read(uint32_t address, void *destination, uint32_t length);
extern void reset_usr_setting(void *settings);
extern int is_battery_critical(void);
extern void set_test_mode(unsigned int);
extern void save_usr_setting(void *settings, uint32_t value);
extern void memset_bytes(void *destination, int value, uint32_t length);

int load_usr_setting(uint8_t *settings)
{
    struct user_settings_record record;

    memset_bytes(&record, 0, sizeof(record));
    if (flash_settings_read(0x00134000UL, &record, sizeof(record)) != 0) {
        if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
            if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
                log_message(((unsigned long)"%s(): usr_flash_settings_read error!\n") /*=0x9e60c*/, ((unsigned long)"load_usr_setting") /*=0x9e7a6*/);
            } else {
                debug_print(((unsigned long)"%s(): usr_flash_settings_read error!\n") /*=0x9e60c*/, ((unsigned long)"load_usr_setting") /*=0x9e7a6*/);
            }
        }
        return -1;
    }

    if (*(volatile int32_t *)((unsigned long)&g_log_level) /*=0x2000230c*/ > 1) {
        if (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0) {
            log_message(((unsigned long)"%s(): read user settings success!\n") /*=0x9e632*/, ((unsigned long)"load_usr_setting") /*=0x9e7a6*/);
        } else {
            debug_print(((unsigned long)"%s(): read user settings success!\n") /*=0x9e632*/, ((unsigned long)"load_usr_setting") /*=0x9e7a6*/);
        }
    }

    settings[0xed5] = record.language;
    settings[0xef4] = record.secondary_language;
    *(uint32_t *)(settings + 0xf6c) =
        record.timeout == 0 ? 400 : record.timeout;
    settings[0xfea] = record.display_mode;
    settings[0xf98] = record.brightness;
    settings[0xf60] = record.interaction_mode;
    settings[0x1070] = record.gesture_mode;
    settings[0x108d] = record.auxiliary_mode;
    settings[0xec0] = record.primary_index;
    *(uint32_t *)(settings + 0x1069) = record.identifier;
    settings[0x106f] = record.identifier_tail;
    *(uint16_t *)(settings + 0x106d) = record.interval;
    settings[0xef5] = record.language_extension;
    settings[0x108f] = record.boolean_mode < 2 ? record.boolean_mode : 0;
    settings[0x1090] = record.option_a;
    settings[0x1091] = record.option_b;
    settings[0xec1] = record.secondary_index;
    *(uint32_t *)(settings + 0xf68) = record.counter;

    if ((uint8_t)(record.display_mode & record.interaction_mode) == 0xff) {
        reset_usr_setting(settings);
    }
    if (settings[0xec0] > 8) {
        settings[0xec0] = 3;
    }
    if ((uint32_t)(settings[0xec1] - 1) > 8) {
        settings[0xec1] = 3;
    }
    if ((int8_t)settings[0xfea] == 11) {
        settings[0xfea] = 10;
        save_usr_setting(settings, 0);
    }

    set_test_mode(record.critical_mode < 2 ? record.critical_mode : 0);
    if (is_battery_critical() == 1) {
        settings[0xf98] = 0;
        settings[0xfea] = 11;
        settings[0xed5] = 0x15;
        *(uint16_t *)(settings + 0xec0) = 0x303;
    } else {
        settings[0xfea] = 10;
    }
    if (*(int32_t *)(settings + 0xf68) == -1) {
        *(uint32_t *)(settings + 0xf68) = 0;
    }
    return 0;
}
