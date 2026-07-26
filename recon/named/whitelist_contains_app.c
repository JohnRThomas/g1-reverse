/* readable reconstruction; identity: FUN_00034ff0 @ 0x00034ff0
 * public-name: whitelist_contains_app
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   whitelist_contains_app                   <= FUN_00034ff0 @ 0x00034ff0
 *   log_message                              <= FUN_0007dda4 @ 0x0007dda4
 *   strncmp                                  <= FUN_00087036 @ 0x00087036
 * address symbols (name @ address):
 *   rodata_a8750                             @ 0x000a8750   [INLINED -- G6 literal batch]
 *   g_log_use_alt_sink                       @ 0x20007554
 *   g_app_whitelist_buffer                   @ 0x2001a22c
 *   g_on_whitelist_by_identifier             @ 0x2001a22d
 */
/* Reconstructed FUN_00034ff0 @ 0x34ff0 (strict CFG parity). */
#include <stdint.h>
#include "../headers/g1_log.h"

extern int strncmp(const void *left, const void *right, uint32_t length);

uint32_t whitelist_contains_app(const void *name, const void *identifier)
{
    uint8_t *row;
    uint8_t *end;

    if (name == 0 || identifier == 0) {
        if (*(volatile uint32_t *)0x20007554U == 0) {
            log_message(0x000a8750U);
        } else {
            debug_print(0x000a8750U);
        }
        return 0;
    }

    row = (uint8_t *)0x2001a22cU;
    end = row + (uint32_t)*(volatile uint8_t *)0x2001a22dU * 0x38U;
    while (row != end) {
        if (strncmp(row + 2, name, 0x28U) == 0 &&
            strncmp(row + 0x2a, identifier, 0x10U) == 0) {
            return 1;
        }
        row += 0x38;
    }
    return 0;
}
