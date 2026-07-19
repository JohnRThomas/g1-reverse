#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_0004e8c0 @ 0x0004e8c0
 * public-name: settings_invalid_index_log
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   settings_invalid_index_log               <= FUN_0004e8c0 @ 0x0004e8c0
 *   gatt_dm_log_helper                       <= FUN_0007f406 @ 0x0007f406
 * address symbols (name @ address):
 *   rodata_88130                             @ 0x00088130
 *   rodata_f11a5                             @ 0x000f11a5
 */
/* Reconstructed FUN_0004e8c0 @ 0x4e8c0
 * CFG_VERIFY_CALL_ARITIES=3
 * Readable identity: settings_invalid_index_log.
 * Raw/address backmap: FUN_0004e8c0 @ 0x0004e8c0.
 */
#include <stdint.h>
extern void gatt_dm_log_helper(uint32_t, uint32_t, const void *);
int settings_invalid_index_log(void)
{
    const uint32_t package[2] = { 2U, ((unsigned long)&rodata_f11a5) /*=0xf11a5*/ };
    gatt_dm_log_helper(((unsigned long)&rodata_88130) /*=0x88130*/, 0x1040U, package);
    return 0;
}
