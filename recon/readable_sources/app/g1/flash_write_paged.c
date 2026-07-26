#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000227d0 @ 0x000227d0
 * public-name: flash_write_paged
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   flash_settings_write_and_verify          <= FUN_00022658 @ 0x00022658
 *   flash_write_paged                        <= FUN_000227d0 @ 0x000227d0
 * address symbols (name @ address):
 *   rodata_9e3db                             @ 0x0009e3db   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_000227d0 @ 0x227d0. */
#include <stdint.h>

extern void log_message(uint32_t format, ...);
extern void debug_print(uint32_t format, ...);
extern int flash_settings_write_and_verify(const void *source, void *destination, int count);

int flash_write_paged(const uint8_t *source, uint8_t *destination,
                 uint32_t byte_count)
{
    uint32_t blocks = ((byte_count >> 12) + 1) & 0xff;
    int final_block = (int)blocks - 1;
    int final_count = (int16_t)(byte_count - ((uint32_t)final_block << 12));
    unsigned int block = 0;
    int total = 0;

    if (*(volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/ == 0)
        log_message(((unsigned long)"size is %d\n") /*=0x9e3db*/, byte_count);
    else
        debug_print(((unsigned long)"size is %d\n") /*=0x9e3db*/, byte_count);

    while ((uint8_t)block < blocks) {
        int count = final_block <= (int)block ? final_count : 0x1000;
        total += flash_settings_write_and_verify(source + block * 0x1000,
                             destination + block * 0x1000, count);
        ++block;
    }
    return total;
}
