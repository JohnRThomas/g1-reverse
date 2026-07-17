/* readable reconstruction; identity: FUN_0007f594 @ 0x0007f594
 * public-name: bt_gatt_dm_data_release
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   svc_attr_memory_release                  <= FUN_0007f3c2 @ 0x0007f3c2
 *   atomic_and_0                             <= FUN_0007f3f0 @ 0x0007f3f0
 *   bt_gatt_dm_data_release                  <= FUN_0007f594 @ 0x0007f594
 */
/* Reconstructed FUN_0007f594 @ 0x7f594  (parity: 300/300 trials, PROVEN) */

extern int atomic_and_0(void *a, int b, unsigned int c, unsigned int d);
extern void svc_attr_memory_release(void *a);

unsigned int bt_gatt_dm_data_release(int param_1, unsigned int param_2, unsigned int param_3, unsigned int param_4)
{
    unsigned int uVar2;
    int iVar1 = atomic_and_0((void*)(param_1+0x138), 0xfffffffd, param_3, param_4);
    if ((int)(iVar1 << 0x1e) < 0) {
        svc_attr_memory_release((void*)param_1);
        atomic_and_0((void*)(param_1+0x138), 0xfffffffe, 0, 0);
        uVar2 = 0;
    } else {
        uVar2 = 0xffffff88;
    }
    return uVar2;
}
