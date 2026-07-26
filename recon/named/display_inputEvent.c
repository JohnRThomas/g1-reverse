/* readable reconstruction; identity: FUN_00049938 @ 0x00049938
 * public-name: display_inputEvent
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   k_msgq_put                               <= FUN_000720d0 @ 0x000720d0
 *   memset_bytes                             <= FUN_00086c78 @ 0x00086c78
 * address symbols (name @ address):
 *   rodata_ef058                             @ 0x000ef058   [INLINED -- G6 literal batch]
 *   rodata_f00bb                             @ 0x000f00bb   [INLINED -- G6 literal batch]
 *   rodata_f0151                             @ 0x000f0151   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_display_msgq                           @ 0x200038c4
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed display_inputEvent @ 0x49938 */

#include <stdint.h>

extern void memset_bytes(void *destination, int value, uint32_t length);
extern int k_msgq_put(uint32_t queue, const void *record,
                       uint32_t wait, uint32_t flags);
extern void log_message(uint32_t format, uint32_t argument);
extern void debug_print(uint32_t format, uint32_t argument, ...);

uint32_t display_inputEvent(uint8_t input, uint8_t state)
{
    uint8_t command[24];

    memset_bytes(command + 1, 0, 23);
    command[0] = 5;
    *(uint16_t *)(command + 2) = 2;
    command[4] = input;
    command[5] = state;

    if (k_msgq_put(0x200038c4UL, command, 0, 0) != 0) {
        log_message(((unsigned long)"message queue send failed %s\r\n"), 0x000f0151UL);
        return UINT32_MAX;
    }

    if (*(volatile int32_t *)0x2000230cUL > 2) {
        if (*(volatile uint32_t *)0x20007554UL == 0) {
            log_message(0x000f00bbUL, 0x000f0151UL);
        } else {
            debug_print(0x000f00bbUL, 0x000f0151UL);
        }
    }
    return 0;
}
