/* readable reconstruction; identity: FUN_0007c8b0 @ 0x0007c8b0
 * public-name: lock_device_mutex
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   lock_device_mutex                        <= FUN_0007c8b0 @ 0x0007c8b0
 */
/* Reconstructed FUN_0007c8b0 @ 0x7c8b0  (parity: 300/300 trials, PROVEN) */

extern void thunk_FUN_000723b8(unsigned int a, unsigned int b, unsigned int c, unsigned int d, unsigned int e);

void lock_device_mutex(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    if (param_1 != 0) {
        thunk_FUN_000723b8(*(unsigned int *)(param_1 + 0x10), param_2, 0xffffffffU, 0xffffffffU, param_4);
    }
}
