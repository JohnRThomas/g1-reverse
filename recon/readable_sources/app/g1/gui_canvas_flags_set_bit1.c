#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000432d0 @ 0x000432d0
 * public-name: gui_canvas_flags_set_bit1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gui_canvas_flags_set_bit1                <= FUN_000432d0 @ 0x000432d0
 * address symbols (name @ address):
 *   g_gui_canvas_flags                       @ 0x2000a030
 */
/* Reconstructed FUN_000432d0 @ 0x432d0  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int gui_canvas_flags_set_bit1(void)
{
    uint32_t *p = (uint32_t *)((unsigned long)&g_gui_canvas_flags) /*=0x2000a030*/;
    (void)__atomic_fetch_or(p, 2u, __ATOMIC_SEQ_CST);
    return 0;
}
