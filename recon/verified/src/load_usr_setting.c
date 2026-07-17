/* Reconstructed load_usr_setting @ 0x22e78 */

#include <stdint.h>

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

extern void DEBUG_PRINT(uint32_t format, uint32_t function_name);
extern void FUN_00019c70(uint32_t format, uint32_t function_name, ...);
extern int FUN_000225b4(uint32_t address, void *destination, uint32_t length);
extern void FUN_00022ddc(void *settings);
extern int FUN_00032ee4(void);
extern void FUN_00032ef0(uint32_t mode);
extern void FUN_0007c28e(void *settings, uint32_t value);
extern void FUN_00086c78(void *destination, int value, uint32_t length);

int load_usr_setting(uint8_t *settings)
{
    struct user_settings_record record;

    FUN_00086c78(&record, 0, sizeof(record));
    if (FUN_000225b4(0x00134000UL, &record, sizeof(record)) != 0) {
        if (*(volatile int32_t *)0x2000230cUL > 1) {
            if (*(volatile uint32_t *)0x20007554UL == 0) {
                DEBUG_PRINT(0x0009e60cUL, 0x0009e7a6UL);
            } else {
                FUN_00019c70(0x0009e60cUL, 0x0009e7a6UL);
            }
        }
        return -1;
    }

    if (*(volatile int32_t *)0x2000230cUL > 1) {
        if (*(volatile uint32_t *)0x20007554UL == 0) {
            DEBUG_PRINT(0x0009e632UL, 0x0009e7a6UL);
        } else {
            FUN_00019c70(0x0009e632UL, 0x0009e7a6UL);
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
        FUN_00022ddc(settings);
    }
    if (settings[0xec0] > 8) {
        settings[0xec0] = 3;
    }
    if ((uint32_t)(settings[0xec1] - 1) > 8) {
        settings[0xec1] = 3;
    }
    if ((int8_t)settings[0xfea] == 11) {
        settings[0xfea] = 10;
        FUN_0007c28e(settings, 0);
    }

    FUN_00032ef0(record.critical_mode < 2 ? record.critical_mode : 0);
    if (FUN_00032ee4() == 1) {
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
