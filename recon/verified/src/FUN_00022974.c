/* Reconstructed FUN_00022974 @ 0x22974. */
#include <stdint.h>

typedef int (*flash_read_fn)(int context, int address, void *destination,
                             int count);

extern void DEBUG_PRINT(uint32_t format, ...);
extern int FUN_000167a8(void);
extern void FUN_00019c70(uint32_t format, ...);
extern void FUN_0002ae84(void);
extern uint16_t FUN_0007da4a(uint16_t crc, const void *data, int count);
extern int FUN_0008638c(const void *device);
extern void FUN_00086c78(void *destination, int value, unsigned int count);

uint32_t FUN_00022974(uint16_t *crc, int start_address,
                      uint32_t byte_count)
{
    volatile int *const log_level = (volatile int *)0x2000230cu;
    volatile int *const alternate_log = (volatile int *)0x20007554u;
    uint8_t buffer[1028];
    uint32_t block_count;
    int cursor;
    int end_address;

    if (*log_level >= 3) {
        if (*alternate_log == 0)
            DEBUG_PRINT(0x0009e484, 0x0009e4f9);
        else
            FUN_00019c70(0x0009e484, 0x0009e4f9);
    }

    if (crc == 0 || byte_count == 0) {
        if (*log_level >= 3) {
            if (*alternate_log == 0)
                DEBUG_PRINT(0x0009e4a3, 0x0009e4f9);
            else
                FUN_00019c70(0x0009e4a3, 0x0009e4f9);
        }
        return UINT32_MAX;
    }

    block_count = (byte_count >> 10) & 0xffffu;
    if ((byte_count & 0x3ffu) != 0)
        block_count = (block_count + 1) & 0xffffu;

    *(uint32_t *)buffer = 0xff;
    FUN_00086c78(buffer + 4, 0, 0x3fc);
    if (FUN_0008638c((const void *)0x00087bf0) == 0) {
        DEBUG_PRINT(0x000a40ec, *(volatile uint32_t *)0x00087bf0);
        return UINT32_MAX;
    }

    cursor = start_address;
    end_address = start_address + (int)(block_count * 0x400);
    while (cursor != end_address) {
        int chunk_size = (int)(byte_count + (uint32_t)start_address) - cursor;
        int context;
        int status;
        flash_read_fn read;
        unsigned int dump_index;
        int level;

        if (chunk_size >= 0x400)
            chunk_size = 0x400;

        context = FUN_000167a8();
        read = *(flash_read_fn *)(context + 0x1030);
        context = FUN_000167a8();
        status = read(context, cursor, buffer, chunk_size);
        if (status != 0) {
            DEBUG_PRINT(0x0009e4c7, cursor, status);
            return UINT32_MAX;
        }

        dump_index = 0;
        for (;;) {
            level = *log_level;
            if (chunk_size <= (int)(uint8_t)dump_index)
                break;
            if (level > 2) {
                if (*alternate_log == 0)
                    DEBUG_PRINT(0x0009e4e3, 0x0009e4f9,
                                buffer[(uint8_t)dump_index]);
                else
                    FUN_00019c70(0x0009e4e3, 0x0009e4f9);
            }
            ++dump_index;
        }

        if (level > 2) {
            if (*alternate_log == 0)
                DEBUG_PRINT(0x0009e4f0, 0x0009e4f9);
            else
                FUN_00019c70(0x0009e4f0, 0x0009e4f9);
        }
        *crc = FUN_0007da4a(*crc, buffer, chunk_size);
        cursor += 0x400;
    }

    if (*(volatile uint8_t *)0x2000302cu != 0 &&
        *(volatile uint8_t *)0x20018d90u == 0)
        FUN_0002ae84();
    return 0;
}
