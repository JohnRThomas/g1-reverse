/* readable reconstruction; identity: FUN_00080bfe @ 0x00080bfe
 * public-name: smp_reassembly_get_ud
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   smp_reassembly_get_ud                    <= FUN_00080bfe @ 0x00080bfe
 */
/* Reconstructed FUN_00080bfe @ 0x80bfe  (parity: 300/300 trials, PROVEN) */

int smp_reassembly_get_ud(int *param_1)
{
    int iVar1 = *(int*)((char*)param_1 + 0x40);
    if (iVar1 != 0) {
        iVar1 = iVar1 + 0x18;
    }
    return iVar1;
}
