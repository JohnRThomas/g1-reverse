/* readable reconstruction; identity: FUN_0007c8e8 @ 0x0007c8e8
 * public-name: ipc_ept_op_b_guarded
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   ipc_ept_op_b_locked_retry                <= FUN_000257ec @ 0x000257ec
 *   ipc_ept_op_b_guarded                     <= FUN_0007c8e8 @ 0x0007c8e8
 */
/* Reconstructed FUN_0007c8e8 @ 0x7c8e8  (parity: 300/300 trials, PROVEN) */

/* 0x7c8ec `movs r3,#1` supplies BOTH the register index (via `mov r1,r3`)
 * and the read LENGTH; 0x257ec `cbz r3` rejects a zero one and forwards it
 * as the i2c_msg len.  Fixed in recon/app/src in iteration 32; this mirror
 * was never synced. */
extern unsigned int ipc_ept_op_b_locked_retry(unsigned int a, unsigned int b, unsigned int c, unsigned int d);

unsigned int ipc_ept_op_b_guarded(unsigned int param_1, int param_2)
{
    if (param_2 != 0) {
        return ipc_ept_op_b_locked_retry(param_1, 1, param_2, 1);
    }
    return 0xffffffea;
}
