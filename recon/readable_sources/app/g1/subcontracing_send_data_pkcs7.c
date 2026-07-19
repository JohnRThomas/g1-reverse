#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_00021a40 @ 0x00021a40
 * public-name: subcontracing_send_data_pkcs7
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   subcontracing_send_data_pkcs7            <= FUN_00021a40 @ 0x00021a40
 *   debug_print_hex_dump                     <= FUN_0004a424 @ 0x0004a424
 *   safe_memcpy_checked                      <= FUN_00086c1e @ 0x00086c1e
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_9d6a1                             @ 0x0009d6a1
 *   rodata_9d6d8                             @ 0x0009d6d8
 *   rodata_9d6ee                             @ 0x0009d6ee
 *   rodata_9d6f3                             @ 0x0009d6f3
 *   rodata_9d70f                             @ 0x0009d70f
 *   rodata_9d714                             @ 0x0009d714
 *   rodata_9d734                             @ 0x0009d734
 *   rodata_9e014                             @ 0x0009e014
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_00021a40 @ 0x21a40. */
#include <stdint.h>

extern void log_message(uint32_t format, ...);
extern void debug_print(uint32_t format, ...);
extern void debug_print_hex_dump(uint32_t format, const void *record,
                         unsigned int record_size);
extern void safe_memcpy_checked(void *destination, const void *source,
                         unsigned int count, unsigned int record_size);
extern void memset_bytes(void *destination, int value, unsigned int count);

uint32_t subcontracing_send_data_pkcs7(const uint8_t *source, int byte_count,
                      uint8_t record_type,
                      void (*send_record)(void *, unsigned int))
{
    volatile int *const log_level = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *const alternate_log = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uint8_t record[20];
    int full_records = byte_count / 17;
    int remainder = byte_count - full_records * 17;
    int record_count = full_records + 1;
    int index;
    int level;

    *(uint32_t *)record = 0;
    memset_bytes(record + 4, 0, 16);
    record[0] = record_type;
    record[1] = (uint8_t)record_count;

    if (*log_level > 2) {
        if (*alternate_log == 0)
            log_message(((unsigned long)&rodata_9d6a1) /*=0x9d6a1*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/, record_count,
                        remainder, byte_count);
        else
            debug_print(((unsigned long)&rodata_9d6a1) /*=0x9d6a1*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/, record_count,
                         remainder, byte_count);
    }

    for (index = 0;; ++index) {
        level = *log_level;
        if (index >= full_records)
            break;

        record[2] = (uint8_t)index;
        __builtin_memcpy(record + 3, source + index * 17, 17);
        if (level > 2) {
            if (*alternate_log == 0)
                log_message(((unsigned long)&rodata_9d6d8) /*=0x9d6d8*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/,
                            index + 1, record_count);
            else
                debug_print(((unsigned long)&rodata_9d6d8) /*=0x9d6d8*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/,
                             index + 1, record_count);
        }
        debug_print_hex_dump(((unsigned long)&rodata_9d6ee) /*=0x9d6ee*/, record, sizeof(record));
        send_record(record, sizeof(record));
    }

    index = full_records & ~(full_records >> 31);
    record[2] = (uint8_t)index;
    if (remainder == 0) {
        memset_bytes(record + 3, 17, 17);
        if (level > 2) {
            if (*alternate_log == 0)
                log_message(((unsigned long)&rodata_9d6f3) /*=0x9d6f3*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/,
                            index + 1, record_count);
            else
                debug_print(((unsigned long)&rodata_9d6f3) /*=0x9d6f3*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/,
                             index + 1, record_count);
        }
    } else {
        memset_bytes(record + 3 + remainder, 17 - remainder,
                     17 - remainder);
        safe_memcpy_checked(record + 3, source + full_records * 17,
                     (unsigned int)remainder, 17);
        if (level > 2) {
            if (*alternate_log == 0)
                log_message(((unsigned long)&rodata_9d714) /*=0x9d714*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/,
                            index + 1, record_count);
            else
                debug_print(((unsigned long)&rodata_9d714) /*=0x9d714*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/,
                             index + 1, record_count);
        }
    }

    debug_print_hex_dump(((unsigned long)&rodata_9d70f) /*=0x9d70f*/, record, sizeof(record));
    if (*log_level > 2) {
        if (*alternate_log == 0)
            log_message(((unsigned long)&rodata_9d734) /*=0x9d734*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/, byte_count);
        else
            debug_print(((unsigned long)&rodata_9d734) /*=0x9d734*/, ((unsigned long)&rodata_9e014) /*=0x9e014*/, byte_count);
    }
    send_record(record, sizeof(record));
    return 0;
}
