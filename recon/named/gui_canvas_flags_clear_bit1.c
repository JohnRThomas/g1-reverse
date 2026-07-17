/* readable reconstruction; identity: FUN_000432ec @ 0x000432ec
 * public-name: gui_canvas_flags_clear_bit1
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   gui_canvas_flags_clear_bit1              <= FUN_000432ec @ 0x000432ec
 * address symbols (name @ address):
 *   g_gui_canvas_flags                       @ 0x2000a030
 */
/* Reconstructed FUN_000432ec @ 0x432ec  (parity: 300/300 trials, PROVEN) */

#include <stdint.h>
unsigned int gui_canvas_flags_clear_bit1(void)
{
    uint32_t *p = (uint32_t *)0x2000a030UL;
    (void)__atomic_fetch_and(p, 0xfffffffdU, __ATOMIC_SEQ_CST);
    return 0;
}
