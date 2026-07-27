/* readable reconstruction; identity: FUN_000431a8 @ 0x000431a8
 * public-name: atomic_get_3_0
 * durable-map: recon/catalogs/function_names_app.json
 * address symbols (name @ address):
 *   g_gui_canvas_flags                       @ 0x2000a030
 */
/* Reconstructed atomic_get_3_0 @ 0x431a8  (CFG-directed candidate) */
#include <stdint.h>
int atomic_get_3_0(void) {
    return __atomic_load_n((volatile uint32_t *)(uintptr_t)0x2000a030u, __ATOMIC_SEQ_CST);
}
