#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00032c28 @ 0x00032c28
 * public-name: is_ext_flash_burned
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   rodata_9e2f1                             @ 0x0009e2f1
 *   rodata_a74dc                             @ 0x000a74dc
 *   rodata_a7500                             @ 0x000a7500
 *   rodata_a766d                             @ 0x000a766d
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Readable reconstruction of FUN_00032c28 @ 0x00032c28. */
#include <stdint.h>

extern int calc_flash_crc(uint16_t *crc, uint32_t flash_address,
                          uint32_t byte_count); /* FUN_00022974 @ 0x00022974 */
extern void debug_print(const char *format, ...); /* FUN_00019c70 @ 0x00019c70 */
extern void k_msleep_ticks32768_b(uint32_t milliseconds); /* FUN_0007d14a @ 0x0007d14a */
extern void log_message(const char *format, ...); /* FUN_0007dda4 @ 0x0007dda4 */

#define LOG_LEVEL        (*(volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/)
#define LOG_USE_ALT_SINK (*(volatile uint32_t *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/)

#define STR_ENTER_CHECK ((const char *)((unsigned long)&rodata_a74dc) /*=0xa74dc*/)
#define STR_REGION_CRC  ((const char *)((unsigned long)&rodata_a7500) /*=0xa7500*/)
#define STR_READ_RETRY  ((const char *)((unsigned long)&rodata_9e2f1) /*=0x9e2f1*/)
#define STR_FUNCTION    ((const char *)((unsigned long)&rodata_a766d) /*=0xa766d*/)

enum flash_burn_check_result {
    FLASH_BURNED = 0,
    FLASH_SIGNATURE_MISMATCH = 1,
    FLASH_READ_RETRIES_EXHAUSTED = 2,
};

struct flash_signature_region {
    uint32_t first_signature_address;
    uint32_t last_signature_address;
    uint16_t expected_crc;
};

static const struct flash_signature_region signature_regions[] = {
    {0x00140000u, 0x0017fcf8u, 0x0d59u},
    {0x00200000u, 0x003f8c98u, 0xdab9u},
    {0x00500000u, 0x00515768u, 0x1265u},
    {0x00520000u, 0x0097c44fu, 0xdab9u},
    {0x00a20000u, 0x00a2b77fu, 0xd412u},
    {0x00a40000u, 0x00dbedcfu, 0xdab9u},
    {0x00180000u, 0x001af0d8u, 0x2632u},
};

static inline __attribute__((always_inline)) void log_entry(void)
{
    if (LOG_LEVEL > 2) {
        if (LOG_USE_ALT_SINK == 0) {
            log_message(STR_ENTER_CHECK, STR_FUNCTION);
        } else {
            debug_print(STR_ENTER_CHECK, STR_FUNCTION);
        }
    }
}

static inline __attribute__((always_inline)) void
log_region_crc(unsigned int region_index, uint16_t crc)
{
    if (LOG_LEVEL > 2) {
        if (LOG_USE_ALT_SINK == 0) {
            log_message(STR_REGION_CRC, STR_FUNCTION, region_index,
                        (unsigned int)crc);
        } else {
            debug_print(STR_REGION_CRC, STR_FUNCTION, region_index,
                        (unsigned int)crc);
        }
    }
}

static inline __attribute__((always_inline)) void
log_read_retry(uint8_t retry_count)
{
    if (LOG_LEVEL > 0) {
        if (LOG_USE_ALT_SINK == 0) {
            log_message(STR_READ_RETRY, STR_FUNCTION,
                        (unsigned int)retry_count);
        } else {
            debug_print(STR_READ_RETRY, STR_FUNCTION,
                        (unsigned int)retry_count);
        }
    }
}

int is_ext_flash_burned(void)
{
    unsigned int region_index;

    log_entry();

    for (region_index = 0;
         region_index < sizeof(signature_regions) / sizeof(signature_regions[0]);
         ++region_index) {
        const struct flash_signature_region *region =
            &signature_regions[region_index];
        uint8_t retry_count = 0;
        uint16_t crc;

        for (;;) {
            crc = 0xffffu;
            if (calc_flash_crc(&crc, region->first_signature_address, 0x10) == 0 &&
                calc_flash_crc(&crc, region->last_signature_address, 0x10) == 0) {
                break;
            }

            if (retry_count == 5) {
                return FLASH_READ_RETRIES_EXHAUSTED;
            }

            k_msleep_ticks32768_b(100);
            retry_count = (uint8_t)(retry_count + 1);
            log_read_retry(retry_count);
        }

        if (crc != region->expected_crc) {
            return FLASH_SIGNATURE_MISMATCH;
        }

        log_region_crc(region_index, crc);
    }

    return FLASH_BURNED;
}
