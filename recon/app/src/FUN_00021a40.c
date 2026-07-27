/* Reconstructed FUN_00021a40 @ 0x21a40. */
#include <stdint.h>

extern void DEBUG_PRINT(unsigned long, ...);
extern void FUN_00019c70(unsigned long, ...);
extern void FUN_0004a424(uint32_t format, const void *record,
                         unsigned int record_size);
extern void FUN_00086c1e(void *destination, const void *source,
                         unsigned int count, unsigned int record_size);
extern void FUN_00086c78(void *destination, int value, unsigned int count);

uint32_t FUN_00021a40(const uint8_t *source, int byte_count,
                      uint8_t record_type,
                      void (*send_record)(void *, unsigned int))
{
    volatile int *const log_level = (volatile int *)0x2000230cu;
    volatile int *const alternate_log = (volatile int *)0x20007554u;
    uint8_t record[20];
    int full_records = byte_count / 17;
    int remainder = byte_count - full_records * 17;
    int record_count = full_records + 1;
    int index;
    int level;

    *(uint32_t *)record = 0;
    FUN_00086c78(record + 4, 0, 16);
    record[0] = record_type;
    record[1] = (uint8_t)record_count;

    if (*log_level > 2) {
        if (*alternate_log == 0)
            DEBUG_PRINT(0x0009d6a1, 0x0009e014, record_count,
                        remainder, byte_count);
        else
            FUN_00019c70(0x0009d6a1, 0x0009e014, record_count,
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
                DEBUG_PRINT(0x0009d6d8, 0x0009e014,
                            index + 1, record_count);
            else
                FUN_00019c70(0x0009d6d8, 0x0009e014,
                             index + 1, record_count);
        }
        FUN_0004a424(0x0009d6ee, record, sizeof(record));
        send_record(record, sizeof(record));
    }

    index = full_records & ~(full_records >> 31);
    record[2] = (uint8_t)index;
    if (remainder == 0) {
        FUN_00086c78(record + 3, 17, 17);
        if (level > 2) {
            if (*alternate_log == 0)
                DEBUG_PRINT(0x0009d6f3, 0x0009e014,
                            index + 1, record_count);
            else
                FUN_00019c70(0x0009d6f3, 0x0009e014,
                             index + 1, record_count);
        }
    } else {
        FUN_00086c78(record + 3 + remainder, 17 - remainder,
                     17 - remainder);
        FUN_00086c1e(record + 3, source + full_records * 17,
                     (unsigned int)remainder, 17);
        if (level > 2) {
            if (*alternate_log == 0)
                DEBUG_PRINT(0x0009d714, 0x0009e014,
                            index + 1, record_count);
            else
                FUN_00019c70(0x0009d714, 0x0009e014,
                             index + 1, record_count);
        }
    }

    FUN_0004a424(0x0009d70f, record, sizeof(record));
    if (*log_level > 2) {
        if (*alternate_log == 0)
            DEBUG_PRINT(0x0009d734, 0x0009e014, byte_count);
        else
            FUN_00019c70(0x0009d734, 0x0009e014, byte_count);
    }
    send_record(record, sizeof(record));
    return 0;
}
