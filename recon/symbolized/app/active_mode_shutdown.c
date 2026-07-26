#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0002bdf0 @ 0x0002bdf0
 * public-name: active_mode_shutdown
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   debug_print                              <= FUN_00019c70 @ 0x00019c70
 *   active_mode_shutdown                     <= FUN_0002bdf0 @ 0x0002bdf0
 * address symbols (name @ address):
 *   rodata_a24eb                             @ 0x000a24eb   [INLINED -- G6 literal batch]
 *   rodata_a24f9                             @ 0x000a24f9   [INLINED -- G6 literal batch]
 *   g_log_level                              @ 0x2000230c
 *   g_log_use_alt_sink                       @ 0x20007554
 */
/* Reconstructed FUN_0002bdf0 @ 0x0002bdf0, extent 0x00000060.
 * Readable identity: active_mode_shutdown.
 * Raw/address backmap: active_mode_shutdown <= FUN_0002bdf0 @ 0x0002bdf0.
 * CFG_VERIFY_CALL_ARITIES=4,1,4,1
 */
#include <stdint.h>

extern int debug_print(uintptr_t format, ...);
extern int log_message(uintptr_t format, ...);

int active_mode_shutdown(uint8_t *device)
{
    volatile int *const log_level = (volatile int *)((unsigned long)&g_log_level) /*=0x2000230c*/;
    volatile int *const log_backend = (volatile int *)((unsigned long)&g_log_use_alt_sink) /*=0x20007554*/;
    uint8_t phase = device[0xfe6];

    if ((phase & 0xfbU) != 1U)
        return 0;
    device[0xfe6] = 3U;
    if (*log_level > 1) {
        if (*log_backend != 0)
            debug_print(((unsigned long)"%s(): begin.\n") /*=0xa24eb*/, 0x000a2505UL);
        else
            log_message(((unsigned long)"%s(): begin.\n") /*=0xa24eb*/, 0x000a2505UL);
    }
    ((void (*)(void *))(*(uint32_t *)(device + 0xb74)))(device + 0xb6c);
    if (*log_level > 1) {
        if (*log_backend != 0)
            debug_print(((unsigned long)"%s(): end.\n") /*=0xa24f9*/, 0x000a2505UL);
        else
            log_message(((unsigned long)"%s(): end.\n") /*=0xa24f9*/, 0x000a2505UL);
    }
    device[0xfe6] = 0U;
    return 0;
}
