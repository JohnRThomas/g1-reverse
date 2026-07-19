/* readable reconstruction; identity: FUN_00085c26 @ 0x00085c26
 * public-name: cbor_finalize_backup_count
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decoder_at_end                      <= FUN_00085c12 @ 0x00085c12
 *   cbor_finalize_backup_count               <= FUN_00085c26 @ 0x00085c26
 */
/* Reconstructed FUN_00085c26 @ 0x85c26  (parity: 300/300 trials, PROVEN) */

extern unsigned long long cbor_decoder_at_end(int a);

void cbor_finalize_backup_count(int param_1)
{
    int iVar1 = *(int *)(param_1 + 0x14);
    unsigned long long uVar2 = cbor_decoder_at_end(iVar1);
    if ((int)uVar2 != 0 && iVar1 != 0) {
        *(int *)(iVar1 + 0xc) = (int)(uVar2 >> 32);
    }
}
