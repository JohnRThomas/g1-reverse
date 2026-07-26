/* readable reconstruction; identity: FUN_00022974 @ 0x00022974
 * public-name: calc_flash_crc
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   get_device_info                          <= FUN_000167a8 @ 0x000167a8
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   calc_flash_crc                           <= FUN_00022974 @ 0x00022974
 *   watchdog_feed_retry                      <= FUN_0002ae84 @ 0x0002ae84
 *   g1_recon_crc16_ansi_seeded               <= FUN_0007da4a @ 0x0007da4a
 *   z_device_is_ready                        <= FUN_0008638c @ 0x0008638c
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_87bf0                             @ 0x00087bf0
 *   rodata_9e484                             @ 0x0009e484   [INLINED -- G6 literal batch]
 *   rodata_9e4a3                             @ 0x0009e4a3   [INLINED -- G6 literal batch]
 *   rodata_9e4c7                             @ 0x0009e4c7   [INLINED -- G6 literal batch]
 *   rodata_9e4e3                             @ 0x0009e4e3   [INLINED -- G6 literal batch]
 *   rodata_9e4f0                             @ 0x0009e4f0   [INLINED -- G6 literal batch]
 *   rodata_9e4f9                             @ 0x0009e4f9   [INLINED -- G6 literal batch]
 *   rodata_a40ec                             @ 0x000a40ec
 *   g_log_level                              @ 0x2000230c
 *   g_flash_crc_active_flag                  @ 0x2000302c
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_flash_crc_skip_watchdog_flag           @ 0x20018d90
 */
/* Reconstructed FUN_00022974 @ 0x22974. */
#include <stdint.h>
#include "../headers/g1_log.h"

typedef int (*flash_read_fn)(int context, int address, void *destination,
                             int count);

extern int get_device_info(void);
extern void watchdog_feed_retry(void);
extern unsigned int g1_recon_crc16_ansi_seeded(unsigned int crc,
        const unsigned char *data, int count);
extern int z_device_is_ready(const void *device);
extern void memset_bytes(void *destination, int value, unsigned int count);

uint32_t calc_flash_crc(uint16_t *crc, int start_address,
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
            log_message(((unsigned long)"%s(): join in calc_flash_crc\n\n"), ((unsigned long)"calc_flash_crc"));
        else
            debug_print(((unsigned long)"%s(): join in calc_flash_crc\n\n"), ((unsigned long)"calc_flash_crc"));
    }

    if (crc == 0 || byte_count == 0) {
        if (*log_level >= 3) {
            if (*alternate_log == 0)
                log_message(((unsigned long)"%s(): calc_flash_crc para is NULL\n\n"), ((unsigned long)"calc_flash_crc"));
            else
                debug_print(((unsigned long)"%s(): calc_flash_crc para is NULL\n\n"), ((unsigned long)"calc_flash_crc"));
        }
        return UINT32_MAX;
    }

    block_count = (byte_count >> 10) & 0xffffu;
    if ((byte_count & 0x3ffu) != 0)
        block_count = (block_count + 1) & 0xffffu;

    *(uint32_t *)buffer = 0xff;
    memset_bytes(buffer + 4, 0, 0x3fc);
    if (z_device_is_ready((const void *)0x00087bf0) == 0) {
        log_message(0x000a40ec, *(volatile uint32_t *)0x00087bf0);
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

        context = get_device_info();
        read = *(flash_read_fn *)(context + 0x1030);
        context = get_device_info();
        status = read(context, cursor, buffer, chunk_size);
        if (status != 0) {
            log_message(((unsigned long)"Flash read 0x%x failed: %d\n"), cursor, status);
            return UINT32_MAX;
        }

        dump_index = 0;
        for (;;) {
            level = *log_level;
            if (chunk_size <= (int)(uint8_t)dump_index)
                break;
            if (level > 2) {
                if (*alternate_log == 0)
                    log_message(((unsigned long)"%s(): 0x%x \n"), ((unsigned long)"calc_flash_crc"),
                                buffer[(uint8_t)dump_index]);
                else
                    debug_print(((unsigned long)"%s(): 0x%x \n"), ((unsigned long)"calc_flash_crc"));
            }
            ++dump_index;
        }

        if (level > 2) {
            if (*alternate_log == 0)
                log_message(((unsigned long)"%s(): \n\n"), ((unsigned long)"calc_flash_crc"));
            else
                debug_print(((unsigned long)"%s(): \n\n"), ((unsigned long)"calc_flash_crc"));
        }
        *crc = g1_recon_crc16_ansi_seeded(*crc, buffer, chunk_size);
        cursor += 0x400;
    }

    if (*(volatile uint8_t *)0x2000302cu != 0 &&
        *(volatile uint8_t *)0x20018d90u == 0)
        watchdog_feed_retry();
    return 0;
}
