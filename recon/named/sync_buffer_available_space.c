/* readable reconstruction; identity: FUN_00071314 @ 0x00071314
 * public-name: sync_buffer_available_space
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   sync_buffer_available_space              <= FUN_00071314 @ 0x00071314
 *   mutex_lock_wait_forever_dup              <= FUN_000859b6 @ 0x000859b6
 */
/* Reconstructed FUN_00071314 @ 0x71314  (parity: 300/300 trials, PROVEN) */

extern void mutex_lock_wait_forever_dup(int a);
extern unsigned long process_sync_buffer(unsigned int, ...);

int sync_buffer_available_space(int param_1)
{
    int iVar1;

    iVar1 = 0xfffff82d;
    if (param_1 != 0) {
        mutex_lock_wait_forever_dup(param_1 + 0x58);
        iVar1 = 0xfffff82e;
        if (*(volatile int *)(*(volatile int *)(param_1 + 0xa0) + 0x18) == 0) {
            iVar1 = *(volatile int *)(param_1 + 0x94) + -0x10;
            if (iVar1 < 1) {
                iVar1 = -0x7d2;
            }
        }
        process_sync_buffer(param_1 + 0x58);
    }
    return iVar1;
}
