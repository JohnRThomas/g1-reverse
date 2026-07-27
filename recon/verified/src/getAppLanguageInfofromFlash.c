/* Reconstructed getAppLanguageInfofromFlash @ 0x23d0c. */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern uintptr_t FUN_000167a8(void);
extern int FUN_0008638c(uint32_t device);

typedef int (*flash_read_fn)(void *context, uint32_t address,
                             void *destination, unsigned length);

uint8_t getAppLanguageInfofromFlash(uint32_t request, uint32_t saved_word,
                                    uint32_t reason)
{
    volatile int *log_level = (volatile int *)0x2000230c;
    volatile uint32_t *deferred_logger = (volatile uint32_t *)0x20007554;
    volatile uint32_t *flash_device = (volatile uint32_t *)0x00087bf0;
    volatile uint8_t *published_language = (volatile uint8_t *)0x20018463;
    volatile uint32_t language_record = saved_word;

    if (*log_level > 2) {
        if (*deferred_logger == 0) {
            DEBUG_PRINT(0x0009e9bf, 0x0009ed2e, reason, 0, request);
        } else {
            FUN_00019c70(0x0009e9bf, 0x0009ed2e, reason, 0, request);
        }
    }

    if (FUN_0008638c((uint32_t)flash_device) == 0) {
        if (*log_level > 0) {
            if (*deferred_logger == 0) {
                DEBUG_PRINT(0x0009e9ea, 0x0009ed2e,
                            *flash_device, 0, request);
            } else {
                FUN_00019c70(0x0009e9ea, 0x0009ed2e,
                             *flash_device, 0, request);
            }
        }
        return 0xff;
    }

    language_record &= 0xff000000u;
    uintptr_t state = FUN_000167a8();
    flash_read_fn read_flash = *(flash_read_fn *)(state + 0x1030);
    void *context = (void *)FUN_000167a8();
    int status = read_flash(context, 0x13e000, (void *)&language_record, 3);

    if (status != 0) {
        if (*log_level > 0) {
            if (*deferred_logger == 0) {
                DEBUG_PRINT(0x0009ea0a, 0x0009ed2e, 0x13e000);
            } else {
                FUN_00019c70(0x0009ea0a, 0x0009ed2e, 0x13e000);
            }
        }
        return 0;
    }

    uint8_t language = (int8_t)language_record == (int8_t)0xaa ?
                       (uint8_t)(language_record >> 8) : 2;
    *published_language = language;
    if (*log_level > 3) {
        if (*deferred_logger == 0) {
            DEBUG_PRINT(0x0009ea37, 0x0009ed2e, *published_language);
        } else {
            FUN_00019c70(0x0009ea37, 0x0009ed2e, *published_language);
        }
    }
    return *published_language;
}
