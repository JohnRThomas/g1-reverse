/* readable reconstruction; identity: FUN_000534a8 @ 0x000534a8
 * public-name: hci_cmd_alloc_failure_log
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   hci_cmd_alloc_failure_log                <= FUN_000534a8 @ 0x000534a8
 *   bt_log_forward_3arg                      <= FUN_00080ea2 @ 0x00080ea2
 * address symbols (name @ address):
 *   rodata_88138                             @ 0x00088138
 *   rodata_f2d9d                             @ 0x000f2d9d
 */
/* Reconstructed FUN_000534a8 @ 0x534a8
 * CFG_VERIFY_CALL_ARITIES=3
 * Readable identity: le_conn_param_neg_reply_alloc_failed_log.
 * Raw/address backmap: FUN_000534a8 @ 0x000534a8.
 */
#include <stdint.h>
extern void bt_log_forward_3arg(uint32_t, uint32_t, const void *);
void hci_cmd_alloc_failure_log(void)
{
    const uint32_t package[2] = { 2U, 0x000f2d9dUL };
    bt_log_forward_3arg(0x00088138UL, 0x1040U, package);
}
