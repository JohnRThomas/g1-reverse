/* readable reconstruction; identity: FUN_000609f4 @ 0x000609f4
 * public-name: FUN_000609f4
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   mutex_lock_syscall_handler               <= FUN_00072908 @ 0x00072908
 */
/* Reconstructed FUN_000609f4 @ 0x609f4  (parity: 300/300 trials, PROVEN) */

extern void mutex_lock_syscall_handler(unsigned int, unsigned int, unsigned int, unsigned int);

void FUN_000609f4(unsigned int param_1, unsigned int param_2)
{
    if (param_2 == 0x0bad0000UL) {
        mutex_lock_syscall_handler(param_1 + 0x30, param_2, 0xffffffffUL, 0xffffffffUL);
        return;
    }
    return;
}
