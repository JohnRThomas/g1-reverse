/* readable reconstruction; identity: FUN_00085c38 @ 0x00085c38
 * public-name: zcbor_entry_backup_and_advance
 * durable-map: recon/catalogs/function_names_app.json
 * callees (readable <= raw @ address):
 *   cbor_decoder_at_end                      <= FUN_00085c12 @ 0x00085c12
 *   cbor_finalize_backup_count               <= FUN_00085c26 @ 0x00085c26
 *   zcbor_entry_backup_and_advance           <= FUN_00085c38 @ 0x00085c38
 */
/* Reconstructed FUN_00085c38 @ 0x85c38  (parity: 300/300 trials, PROVEN) */

extern unsigned long long cbor_decoder_at_end(int iVar2);
extern void cbor_finalize_backup_count(int *param_1, int param_2);

int zcbor_entry_backup_and_advance(int *param_1)
{
    int *puVar1;
    int iVar2;
    int *puVar3;
    unsigned long long uVar5;
    int *puVar4;

    iVar2 = param_1[5];
    uVar5 = cbor_decoder_at_end(iVar2);
    if ((int)uVar5 != 0) {
        if (*(unsigned int *)(iVar2 + 4) < *(unsigned int *)(iVar2 + 8)) {
            *(unsigned char *)((int)param_1 + 0x11) = 0;
            *(int *)(iVar2 + 4) = *(int *)(iVar2 + 4) + 1;
            puVar1 = (int *)((((int *)param_1[5])[1] + -1) * 0x18 + *(int *)param_1[5]);
            puVar3 = param_1;
            do {
                puVar4 = puVar3 + 1;
                *puVar1 = *puVar3;
                puVar1 = puVar1 + 1;
                puVar3 = puVar4;
            } while (puVar4 != param_1 + 6);
            param_1[2] = (int)(uVar5 >> 0x20);
            return (int)uVar5;
        }
        cbor_finalize_backup_count(param_1, 1);
    }
    return 0;
}
