#include "g1_app_symbols.h"
/* readable reconstruction; identity: FUN_000573c8 @ 0x000573c8
 * public-name: log_bt_buf_alloc_failure
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   log_bt_buf_alloc_failure                 <= FUN_000573c8 @ 0x000573c8
 *   log_msg_3arg_thunk                       <= FUN_00081746 @ 0x00081746
 * address symbols (name @ address):
 *   rodata_88160                             @ 0x00088160
 *   rodata_f3ec2                             @ 0x000f3ec2
 */
/* Reconstructed FUN_000573c8 @ 0x573c8
 * CFG_VERIFY_CALL_ARITIES=3
 * Readable identity: Bluetooth buffer-allocation failure logger.
 * Raw/address backmap: FUN_000573c8 @ 0x000573c8.
 */

#include <stdint.h>

extern void log_msg_3arg_thunk(uint32_t source, uint32_t descriptor,
                         const void *package);

int log_bt_buf_alloc_failure(uint32_t buffer_type)
{
    const uint32_t log_package[3] = {
        3U,
        ((unsigned long)&rodata_f3ec2) /*=0xf3ec2*/,
        buffer_type,
    };

    log_msg_3arg_thunk(((unsigned long)&rodata_88160) /*=0x88160*/, 0x1840U, log_package);
    return 0;
}
