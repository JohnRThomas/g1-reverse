/* Reconstructed load_sys_setting @ 0x22bd0. */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern int FUN_000225b4(uint32_t, void *, uint32_t);
extern void FUN_00022b00(uintptr_t);
extern void FUN_00086c78(void *, int, uint32_t);

struct __attribute__((packed)) persisted_system_settings {
    uint32_t version;
    uint32_t reserved_word;
    uint8_t mode;
    uint8_t reserved_09[3];
    uint32_t interval;
    uint32_t timeout;
    uint8_t feature_enabled;
    uint8_t first_table[32];
    uint8_t second_table[32];
    uint8_t option_a;
    uint8_t option_b;
    uint8_t reserved_57[9];
    uint16_t width_a;
    uint16_t width_b;
    uint32_t value_fa4;
    uint32_t value_fa0;
    uint32_t value_fa8;
    uint32_t value_fac;
    uint16_t value_eda;
    uint16_t value_edc;
    uint16_t value_ede;
    uint16_t reserved_7a;
    uint32_t counter_fb0;
    uint32_t value_fb4;
};

static __attribute__((always_inline)) inline void
copy_unaligned_table(volatile uint32_t *destination,
                     const uint8_t source[32])
{
    for (unsigned int offset = 0; offset != 16; offset += 4)
        *destination++ = *(const uint32_t *)(source + offset);
}

static __attribute__((always_inline)) inline void
log_settings_event(uint32_t message)
{
    if (*(volatile int32_t *)0x2000230c > 1) {
        if (*(volatile uint32_t *)0x20007554 == 0)
            DEBUG_PRINT(message, 0x0009e7c9);
        else
            FUN_00019c70(message, 0x0009e7c9);
    }
}

int load_sys_setting(uintptr_t application)
{
    struct persisted_system_settings settings;
    FUN_00086c78(&settings, 0, sizeof(settings));

    int result = FUN_000225b4(0x130000, &settings, sizeof(settings));
    if (result != 0) {
        log_settings_event(0x0009e580);
        return -1;
    }

    log_settings_event(0x0009e5a6);

    *(uint32_t *)(application + 0x1050) = settings.version;
    *(uint8_t *)(application + 2) = settings.mode;
    *(uint32_t *)(application + 0xf64) = settings.interval;
    *(uint32_t *)(application + 0xf94) = settings.timeout;
    *(uint8_t *)(application + 0xed4) = settings.feature_enabled;

    if (settings.first_table[0] != 0xff)
        copy_unaligned_table((volatile uint32_t *)0x20003003,
                             settings.first_table);
    if (settings.second_table[0] != 0xff)
        copy_unaligned_table((volatile uint32_t *)0x20002fe3,
                             settings.second_table);

    *(uint8_t *)(application + 3) = settings.option_a;
    *(uint8_t *)(application + 4) = settings.option_b;
    *(uint16_t *)(application + 0x1072) = settings.width_a;
    *(uint16_t *)(application + 0x1074) = settings.width_b;
    *(uint32_t *)(application + 0xfa0) = settings.value_fa0;
    *(uint32_t *)(application + 0xfa4) = settings.value_fa4;
    *(uint32_t *)(application + 0xfa8) = settings.value_fa8;
    *(uint32_t *)(application + 0xfac) = settings.value_fac;
    *(uint32_t *)(application + 0xfb0) = settings.counter_fb0;
    *(uint32_t *)(application + 0xfb4) = settings.value_fb4;
    *(uint16_t *)(application + 0xeda) = settings.value_eda;
    *(uint16_t *)(application + 0xedc) = settings.value_edc;
    *(uint16_t *)(application + 0xede) = settings.value_ede;

    if (settings.version != 1) {
        log_settings_event(0x0009e5c8);
        *(volatile uint8_t *)(application + 2) = 0xff;
        *(volatile uint32_t *)(application + 0xf94) = 0x13880;
        *(volatile uint32_t *)(application + 0xf64) = 0;
        *(volatile uint8_t *)(application + 0xed4) = 0;
        *(volatile uint16_t *)(application + 0x1072) = 0x20;
        *(volatile uint16_t *)(application + 0x1074) = 0x20;
        *(volatile uint32_t *)(application + 0xfb0) = 0x1f400;
        *(volatile uint16_t *)(application + 0xeda) = 0x3f;
        *(volatile uint32_t *)(application + 0xfa0) = 0;
        *(volatile uint32_t *)(application + 0xfa4) = 0;
        *(volatile uint32_t *)(application + 0xfa8) = 0;
        *(volatile uint32_t *)(application + 0xfac) = 0;
        *(volatile uint32_t *)(application + 0xfb4) = 0;
        *(volatile uint32_t *)(application + 0xedc) = 0x3f003f;
        FUN_00022b00(application);
    }

    *(uint32_t *)(application + 0x1050) = 1;
    if (*(uint8_t *)(application + 0xed4) != 1)
        *(uint8_t *)(application + 0xed4) = 0;

    uint32_t next_counter = *(uint32_t *)(application + 0xfb0) + 1;
    if (next_counter < 2)
        *(uint32_t *)(application + 0xfb0) = 0x1f400;

    uint16_t width_delta = *(uint16_t *)(application + 0x1072) - 0x16;
    if (width_delta > 0x14)
        *(uint16_t *)(application + 0x1072) = 0x20;

    uint16_t width_b = *(uint16_t *)(application + 0x1074);
    if (width_b > 0x40)
        *(uint16_t *)(application + 0x1074) = 0x20;
    else if (width_b <= 3)
        *(uint16_t *)(application + 0x1074) = 4;

    if ((uint16_t)(*(uint16_t *)(application + 0xede) - 1) > 0x3e)
        *(uint16_t *)(application + 0xede) = 0x3f;
    return 0;
}
