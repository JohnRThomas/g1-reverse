#include "g1_app_symbols.h"
/* readable reconstruction; identity: panel_render_screen_dispatch @ 0x00035774
 * public-name: panel_render_screen_dispatch
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   (indirect only -- through the screen table and the context vtable)
 * address symbols (name @ address):
 *   g_screen_render_table                    @ 0x20002430
 */
/* Reconstructed panel_render_screen_dispatch @ 0x35774 (uncatalogued: Ghidra
 * folded it into the tail of dump_whitelist_init; code 0x35774..0x357d4,
 * literal pool 0x357d8..0x357dc).  (parity: cfg_verify PASS, 203/203 trials)
 * Vtable slot +0x14 (device_ctx + 0xb80) written by quicknote_buffer_pool_init;
 * the only user is ui_refalsh_warp+0x284 (0x48de0).
 */
#include <stdint.h>

typedef void (*render_one_t)(uint32_t arg);
typedef void (*render_ctx_t)(uint8_t *context, uint32_t arg);
typedef void (*ctx_hook_t)(uint8_t *context);

int32_t panel_render_screen_dispatch(uint8_t *context, uint32_t screen, uint32_t arg)
{
    uint32_t *entry;
    int use_table;

    if (*(volatile uint8_t *)(context + 0x47b) == 0)
        return -1;
    *(volatile uint32_t *)(context + 0x348) = 0;
    *(volatile uint32_t *)(context + 0x34c) = 0xb0;

    use_table = 1;
    if (screen != 7) {
        ((ctx_hook_t)*(volatile uint32_t *)(context + 0x1c))(context);
        use_table = ((uint32_t)(screen - 1) <= 16u);
    }
    if (use_table) {
        entry = (uint32_t *)((unsigned long)&g_screen_render_table /*=0x20002430*/
                             + (screen - 1) * 16u);
        if (entry[1] != 0) {
            if (entry[3] != 0)
                ((render_one_t)entry[3])(arg);
        }
        ((render_ctx_t)entry[2])(context, arg);
    }
    if (*(volatile uint32_t *)(context + 0x35c) != 0)
        ((ctx_hook_t)*(volatile uint32_t *)(context + 0x18))(context);
    return 0;
}
