/* readable reconstruction; identity: FUN_0007c944 @ 0x0007c944
 * public-name: nfc_ipc_send_op20
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 *   nfc_ipc_send_op20                        <= FUN_0007c944 @ 0x0007c944
 */
/* Reconstructed FUN_0007c944 @ 0x7c944  (parity: 300/300 trials, PROVEN) */

extern unsigned int ipc_ept_op_b_locked_retry(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

unsigned int nfc_ipc_send_op20(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 0x20, param_2, 1);
    }
    return 0xffffffea;
}
