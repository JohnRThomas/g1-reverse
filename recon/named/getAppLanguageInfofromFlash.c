/* readable reconstruction; identity: FUN_00023d0c @ 0x00023d0c
 * public-name: getAppLanguageInfofromFlash
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e9bf                             @ 0x0009e9bf   [INLINED -- G6 literal batch]
 *   rodata_9e9ea                             @ 0x0009e9ea
 *   rodata_9ea0a                             @ 0x0009ea0a
 *   rodata_9ea37                             @ 0x0009ea37   [INLINED -- G6 literal batch]
 *   rodata_9ed2e                             @ 0x0009ed2e   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_20018463                               @ 0x20018463
 */
/* Reconstructed getAppLanguageInfofromFlash @ 0x23d0c. */
#include <stdint.h>
#include "../headers/g1_log.h"

extern uintptr_t get_device_info(void);
extern int z_device_is_ready(uint32_t device);

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
            log_message(((unsigned long)"%s(): read setting flash data to ram...\r\n\n"), ((unsigned long)"getAppLanguageInfofromFlash"), reason, 0, request);
        } else {
            debug_print(((unsigned long)"%s(): read setting flash data to ram...\r\n\n"), ((unsigned long)"getAppLanguageInfofromFlash"), reason, 0, request);
        }
    }

    if (z_device_is_ready((uint32_t)flash_device) == 0) {
        if (*log_level > 0) {
            if (*deferred_logger == 0) {
                log_message(0x0009e9ea, ((unsigned long)"getAppLanguageInfofromFlash"),
                            *flash_device, 0, request);
            } else {
                debug_print(0x0009e9ea, ((unsigned long)"getAppLanguageInfofromFlash"),
                             *flash_device, 0, request);
            }
        }
        return 0xff;
    }

    language_record &= 0xff000000u;
    uintptr_t state = get_device_info();
    flash_read_fn read_flash = *(flash_read_fn *)(state + 0x1030);
    void *context = (void *)get_device_info();
    int status = read_flash(context, 0x13e000, (void *)&language_record, 3);

    if (status != 0) {
        if (*log_level > 0) {
            if (*deferred_logger == 0) {
                log_message(0x0009ea0a, ((unsigned long)"getAppLanguageInfofromFlash"), 0x13e000);
            } else {
                debug_print(0x0009ea0a, ((unsigned long)"getAppLanguageInfofromFlash"), 0x13e000);
            }
        }
        return 0;
    }

    uint8_t language = (int8_t)language_record == (int8_t)0xaa ?
                       (uint8_t)(language_record >> 8) : 2;
    *published_language = language;
    if (*log_level > 3) {
        if (*deferred_logger == 0) {
            log_message(((unsigned long)"%s(): system language type = %d\n"), ((unsigned long)"getAppLanguageInfofromFlash"), *published_language);
        } else {
            debug_print(((unsigned long)"%s(): system language type = %d\n"), ((unsigned long)"getAppLanguageInfofromFlash"), *published_language);
        }
    }
    return *published_language;
}
